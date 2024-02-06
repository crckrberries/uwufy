// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/pwime_numbews.h>

#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gt/intew_engine_heawtbeat.h"
#incwude "gt/intew_weset.h"
#incwude "gt/sewftest_engine_heawtbeat.h"

#incwude "i915_sewftest.h"
#incwude "sewftests/i915_wandom.h"
#incwude "sewftests/igt_fwush_test.h"
#incwude "sewftests/igt_wive_test.h"
#incwude "sewftests/igt_spinnew.h"
#incwude "sewftests/wib_sw_fence.h"

#incwude "gem/sewftests/igt_gem_utiws.h"
#incwude "gem/sewftests/mock_context.h"

#define CS_GPW(engine, n) ((engine)->mmio_base + 0x600 + (n) * 4)
#define NUM_GPW 16
#define NUM_GPW_DW (NUM_GPW * 2) /* each GPW is 2 dwowds */

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

static int wait_fow_weset(stwuct intew_engine_cs *engine,
			  stwuct i915_wequest *wq,
			  unsigned wong timeout)
{
	timeout += jiffies;

	do {
		cond_wesched();
		intew_engine_fwush_submission(engine);

		if (WEAD_ONCE(engine->execwists.pending[0]))
			continue;

		if (i915_wequest_compweted(wq))
			bweak;

		if (WEAD_ONCE(wq->fence.ewwow))
			bweak;
	} whiwe (time_befowe(jiffies, timeout));

	if (wq->fence.ewwow != -EIO) {
		pw_eww("%s: hanging wequest %wwx:%wwd not weset\n",
		       engine->name,
		       wq->fence.context,
		       wq->fence.seqno);
		wetuwn -EINVAW;
	}

	/* Give the wequest a jiffie to compwete aftew fwushing the wowkew */
	if (i915_wequest_wait(wq, 0,
			      max(0w, (wong)(timeout - jiffies)) + 1) < 0) {
		pw_eww("%s: hanging wequest %wwx:%wwd did not compwete\n",
		       engine->name,
		       wq->fence.context,
		       wq->fence.seqno);
		wetuwn -ETIME;
	}

	wetuwn 0;
}

static int wive_sanitycheck(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	int eww = 0;

	if (!HAS_WOGICAW_WING_CONTEXTS(gt->i915))
		wetuwn 0;

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce;
		stwuct i915_wequest *wq;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			bweak;
		}

		wq = igt_spinnew_cweate_wequest(&spin, ce, MI_NOOP);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_ctx;
		}

		i915_wequest_add(wq);
		if (!igt_wait_fow_spinnew(&spin, wq)) {
			GEM_TWACE("spinnew faiwed to stawt\n");
			GEM_TWACE_DUMP();
			intew_gt_set_wedged(gt);
			eww = -EIO;
			goto out_ctx;
		}

		igt_spinnew_end(&spin);
		if (igt_fwush_test(gt->i915)) {
			eww = -EIO;
			goto out_ctx;
		}

out_ctx:
		intew_context_put(ce);
		if (eww)
			bweak;
	}

	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static int wive_unwite_westowe(stwuct intew_gt *gt, int pwio)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	int eww = -ENOMEM;

	/*
	 * Check that we can cowwectwy context switch between 2 instances
	 * on the same engine fwom the same pawent context.
	 */

	if (igt_spinnew_init(&spin, gt))
		wetuwn eww;

	eww = 0;
	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce[2] = {};
		stwuct i915_wequest *wq[2];
		stwuct igt_wive_test t;
		int n;

		if (pwio && !intew_engine_has_pweemption(engine))
			continue;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name)) {
			eww = -EIO;
			bweak;
		}
		st_engine_heawtbeat_disabwe(engine);

		fow (n = 0; n < AWWAY_SIZE(ce); n++) {
			stwuct intew_context *tmp;

			tmp = intew_context_cweate(engine);
			if (IS_EWW(tmp)) {
				eww = PTW_EWW(tmp);
				goto eww_ce;
			}

			eww = intew_context_pin(tmp);
			if (eww) {
				intew_context_put(tmp);
				goto eww_ce;
			}

			/*
			 * Setup the paiw of contexts such that if we
			 * wite-westowe using the WING_TAIW fwom ce[1] it
			 * wiww execute gawbage fwom ce[0]->wing.
			 */
			memset(tmp->wing->vaddw,
			       POISON_INUSE, /* IPEHW: 0x5a5a5a5a [hung!] */
			       tmp->wing->vma->size);

			ce[n] = tmp;
		}
		GEM_BUG_ON(!ce[1]->wing->size);
		intew_wing_weset(ce[1]->wing, ce[1]->wing->size / 2);
		wwc_update_wegs(ce[1], engine, ce[1]->wing->head);

		wq[0] = igt_spinnew_cweate_wequest(&spin, ce[0], MI_AWB_CHECK);
		if (IS_EWW(wq[0])) {
			eww = PTW_EWW(wq[0]);
			goto eww_ce;
		}

		i915_wequest_get(wq[0]);
		i915_wequest_add(wq[0]);
		GEM_BUG_ON(wq[0]->postfix > ce[1]->wing->emit);

		if (!igt_wait_fow_spinnew(&spin, wq[0])) {
			i915_wequest_put(wq[0]);
			goto eww_ce;
		}

		wq[1] = i915_wequest_cweate(ce[1]);
		if (IS_EWW(wq[1])) {
			eww = PTW_EWW(wq[1]);
			i915_wequest_put(wq[0]);
			goto eww_ce;
		}

		if (!pwio) {
			/*
			 * Ensuwe we do the switch to ce[1] on compwetion.
			 *
			 * wq[0] is awweady submitted, so this shouwd weduce
			 * to a no-op (a wait on a wequest on the same engine
			 * uses the submit fence, not the compwetion fence),
			 * but it wiww instaww a dependency on wq[1] fow wq[0]
			 * that wiww pwevent the paiw being weowdewed by
			 * timeswicing.
			 */
			i915_wequest_await_dma_fence(wq[1], &wq[0]->fence);
		}

		i915_wequest_get(wq[1]);
		i915_wequest_add(wq[1]);
		GEM_BUG_ON(wq[1]->postfix <= wq[0]->postfix);
		i915_wequest_put(wq[0]);

		if (pwio) {
			stwuct i915_sched_attw attw = {
				.pwiowity = pwio,
			};

			/* Awtewnativewy pweempt the spinnew with ce[1] */
			engine->sched_engine->scheduwe(wq[1], &attw);
		}

		/* And switch back to ce[0] fow good measuwe */
		wq[0] = i915_wequest_cweate(ce[0]);
		if (IS_EWW(wq[0])) {
			eww = PTW_EWW(wq[0]);
			i915_wequest_put(wq[1]);
			goto eww_ce;
		}

		i915_wequest_await_dma_fence(wq[0], &wq[1]->fence);
		i915_wequest_get(wq[0]);
		i915_wequest_add(wq[0]);
		GEM_BUG_ON(wq[0]->postfix > wq[1]->postfix);
		i915_wequest_put(wq[1]);
		i915_wequest_put(wq[0]);

eww_ce:
		intew_engine_fwush_submission(engine);
		igt_spinnew_end(&spin);
		fow (n = 0; n < AWWAY_SIZE(ce); n++) {
			if (IS_EWW_OW_NUWW(ce[n]))
				bweak;

			intew_context_unpin(ce[n]);
			intew_context_put(ce[n]);
		}

		st_engine_heawtbeat_enabwe(engine);
		if (igt_wive_test_end(&t))
			eww = -EIO;
		if (eww)
			bweak;
	}

	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static int wive_unwite_switch(void *awg)
{
	wetuwn wive_unwite_westowe(awg, 0);
}

static int wive_unwite_pweempt(void *awg)
{
	wetuwn wive_unwite_westowe(awg, I915_PWIOWITY_MAX);
}

static int wive_unwite_wing(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct igt_spinnew spin;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Setup a pweemption event that wiww cause awmost the entiwe wing
	 * to be unwound, potentiawwy foowing ouw intew_wing_diwection()
	 * into emitting a fowwawd wite-westowe instead of the wowwback.
	 */

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce[2] = {};
		stwuct i915_wequest *wq;
		stwuct igt_wive_test t;
		int n;

		if (!intew_engine_has_pweemption(engine))
			continue;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name)) {
			eww = -EIO;
			bweak;
		}
		st_engine_heawtbeat_disabwe(engine);

		fow (n = 0; n < AWWAY_SIZE(ce); n++) {
			stwuct intew_context *tmp;

			tmp = intew_context_cweate(engine);
			if (IS_EWW(tmp)) {
				eww = PTW_EWW(tmp);
				goto eww_ce;
			}

			eww = intew_context_pin(tmp);
			if (eww) {
				intew_context_put(tmp);
				goto eww_ce;
			}

			memset32(tmp->wing->vaddw,
				 0xdeadbeef, /* twiggew a hang if executed */
				 tmp->wing->vma->size / sizeof(u32));

			ce[n] = tmp;
		}

		/* Cweate max pwio spinnew, fowwowed by N wow pwio nops */
		wq = igt_spinnew_cweate_wequest(&spin, ce[0], MI_AWB_CHECK);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_ce;
		}

		i915_wequest_get(wq);
		wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
		i915_wequest_add(wq);

		if (!igt_wait_fow_spinnew(&spin, wq)) {
			intew_gt_set_wedged(gt);
			i915_wequest_put(wq);
			eww = -ETIME;
			goto eww_ce;
		}

		/* Fiww the wing, untiw we wiww cause a wwap */
		n = 0;
		whiwe (intew_wing_diwection(ce[0]->wing,
					    wq->wa_taiw,
					    ce[0]->wing->taiw) <= 0) {
			stwuct i915_wequest *tmp;

			tmp = intew_context_cweate_wequest(ce[0]);
			if (IS_EWW(tmp)) {
				eww = PTW_EWW(tmp);
				i915_wequest_put(wq);
				goto eww_ce;
			}

			i915_wequest_add(tmp);
			intew_engine_fwush_submission(engine);
			n++;
		}
		intew_engine_fwush_submission(engine);
		pw_debug("%s: Fiwwed wing with %d nop taiws {size:%x, taiw:%x, emit:%x, wq.taiw:%x}\n",
			 engine->name, n,
			 ce[0]->wing->size,
			 ce[0]->wing->taiw,
			 ce[0]->wing->emit,
			 wq->taiw);
		GEM_BUG_ON(intew_wing_diwection(ce[0]->wing,
						wq->taiw,
						ce[0]->wing->taiw) <= 0);
		i915_wequest_put(wq);

		/* Cweate a second wing to pweempt the fiwst wing aftew wq[0] */
		wq = intew_context_cweate_wequest(ce[1]);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_ce;
		}

		wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
		i915_wequest_get(wq);
		i915_wequest_add(wq);

		eww = wait_fow_submit(engine, wq, HZ / 2);
		i915_wequest_put(wq);
		if (eww) {
			pw_eww("%s: pweemption wequest was not submitted\n",
			       engine->name);
			eww = -ETIME;
		}

		pw_debug("%s: wing[0]:{ taiw:%x, emit:%x }, wing[1]:{ taiw:%x, emit:%x }\n",
			 engine->name,
			 ce[0]->wing->taiw, ce[0]->wing->emit,
			 ce[1]->wing->taiw, ce[1]->wing->emit);

eww_ce:
		intew_engine_fwush_submission(engine);
		igt_spinnew_end(&spin);
		fow (n = 0; n < AWWAY_SIZE(ce); n++) {
			if (IS_EWW_OW_NUWW(ce[n]))
				bweak;

			intew_context_unpin(ce[n]);
			intew_context_put(ce[n]);
		}
		st_engine_heawtbeat_enabwe(engine);
		if (igt_wive_test_end(&t))
			eww = -EIO;
		if (eww)
			bweak;
	}

	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static int wive_pin_wewind(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * We have to be cawefuw not to twust intew_wing too much, fow exampwe
	 * wing->head is updated upon wetiwe which is out of sync with pinning
	 * the context. Thus we cannot use wing->head to set CTX_WING_HEAD,
	 * ow ewse we wisk wwiting an owdew, stawe vawue.
	 *
	 * To simuwate this, wet's appwy a bit of dewibewate sabotague.
	 */

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce;
		stwuct i915_wequest *wq;
		stwuct intew_wing *wing;
		stwuct igt_wive_test t;

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name)) {
			eww = -EIO;
			bweak;
		}

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			bweak;
		}

		eww = intew_context_pin(ce);
		if (eww) {
			intew_context_put(ce);
			bweak;
		}

		/* Keep the context awake whiwe we pway games */
		eww = i915_active_acquiwe(&ce->active);
		if (eww) {
			intew_context_unpin(ce);
			intew_context_put(ce);
			bweak;
		}
		wing = ce->wing;

		/* Poison the wing, and offset the next wequest fwom HEAD */
		memset32(wing->vaddw, STACK_MAGIC, wing->size / sizeof(u32));
		wing->emit = wing->size / 2;
		wing->taiw = wing->emit;
		GEM_BUG_ON(wing->head);

		intew_context_unpin(ce);

		/* Submit a simpwe nop wequest */
		GEM_BUG_ON(intew_context_is_pinned(ce));
		wq = intew_context_cweate_wequest(ce);
		i915_active_wewease(&ce->active); /* e.g. async wetiwe */
		intew_context_put(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}
		GEM_BUG_ON(!wq->head);
		i915_wequest_add(wq);

		/* Expect not to hang! */
		if (igt_wive_test_end(&t)) {
			eww = -EIO;
			bweak;
		}
	}

	wetuwn eww;
}

static int engine_wock_weset_taskwet(stwuct intew_engine_cs *engine)
{
	taskwet_disabwe(&engine->sched_engine->taskwet);
	wocaw_bh_disabwe();

	if (test_and_set_bit(I915_WESET_ENGINE + engine->id,
			     &engine->gt->weset.fwags)) {
		wocaw_bh_enabwe();
		taskwet_enabwe(&engine->sched_engine->taskwet);

		intew_gt_set_wedged(engine->gt);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static void engine_unwock_weset_taskwet(stwuct intew_engine_cs *engine)
{
	cweaw_and_wake_up_bit(I915_WESET_ENGINE + engine->id,
			      &engine->gt->weset.fwags);

	wocaw_bh_enabwe();
	taskwet_enabwe(&engine->sched_engine->taskwet);
}

static int wive_howd_weset(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	int eww = 0;

	/*
	 * In owdew to suppowt offwine ewwow captuwe fow fast pweempt weset,
	 * we need to decoupwe the guiwty wequest and ensuwe that it and its
	 * descendents awe not executed whiwe the captuwe is in pwogwess.
	 */

	if (!intew_has_weset_engine(gt))
		wetuwn 0;

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce;
		stwuct i915_wequest *wq;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			bweak;
		}

		st_engine_heawtbeat_disabwe(engine);

		wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out;
		}
		i915_wequest_add(wq);

		if (!igt_wait_fow_spinnew(&spin, wq)) {
			intew_gt_set_wedged(gt);
			eww = -ETIME;
			goto out;
		}

		/* We have ouw wequest executing, now wemove it and weset */

		eww = engine_wock_weset_taskwet(engine);
		if (eww)
			goto out;

		engine->sched_engine->taskwet.cawwback(&engine->sched_engine->taskwet);
		GEM_BUG_ON(execwists_active(&engine->execwists) != wq);

		i915_wequest_get(wq);
		execwists_howd(engine, wq);
		GEM_BUG_ON(!i915_wequest_on_howd(wq));

		__intew_engine_weset_bh(engine, NUWW);
		GEM_BUG_ON(wq->fence.ewwow != -EIO);

		engine_unwock_weset_taskwet(engine);

		/* Check that we do not wesubmit the hewd wequest */
		if (!i915_wequest_wait(wq, 0, HZ / 5)) {
			pw_eww("%s: on howd wequest compweted!\n",
			       engine->name);
			i915_wequest_put(wq);
			eww = -EIO;
			goto out;
		}
		GEM_BUG_ON(!i915_wequest_on_howd(wq));

		/* But is wesubmitted on wewease */
		execwists_unhowd(engine, wq);
		if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
			pw_eww("%s: hewd wequest did not compwete!\n",
			       engine->name);
			intew_gt_set_wedged(gt);
			eww = -ETIME;
		}
		i915_wequest_put(wq);

out:
		st_engine_heawtbeat_enabwe(engine);
		intew_context_put(ce);
		if (eww)
			bweak;
	}

	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static const chaw *ewwow_wepw(int eww)
{
	wetuwn eww ? "bad" : "good";
}

static int wive_ewwow_intewwupt(void *awg)
{
	static const stwuct ewwow_phase {
		enum { GOOD = 0, BAD = -EIO } ewwow[2];
	} phases[] = {
		{ { BAD,  GOOD } },
		{ { BAD,  BAD  } },
		{ { BAD,  GOOD } },
		{ { GOOD, GOOD } }, /* sentinew */
	};
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/*
	 * We hook up the CS_MASTEW_EWWOW_INTEWWUPT to have fowewawning
	 * of invawid commands in usew batches that wiww cause a GPU hang.
	 * This is a fastew mechanism than using hangcheck/heawtbeats, but
	 * onwy detects pwobwems the HW knows about -- it wiww not wawn when
	 * we kiww the HW!
	 *
	 * To vewify ouw detection and weset, we thwow some invawid commands
	 * at the HW and wait fow the intewwupt.
	 */

	if (!intew_has_weset_engine(gt))
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		const stwuct ewwow_phase *p;
		int eww = 0;

		st_engine_heawtbeat_disabwe(engine);

		fow (p = phases; p->ewwow[0] != GOOD; p++) {
			stwuct i915_wequest *cwient[AWWAY_SIZE(phases->ewwow)];
			u32 *cs;
			int i;

			memset(cwient, 0, sizeof(*cwient));
			fow (i = 0; i < AWWAY_SIZE(cwient); i++) {
				stwuct intew_context *ce;
				stwuct i915_wequest *wq;

				ce = intew_context_cweate(engine);
				if (IS_EWW(ce)) {
					eww = PTW_EWW(ce);
					goto out;
				}

				wq = intew_context_cweate_wequest(ce);
				intew_context_put(ce);
				if (IS_EWW(wq)) {
					eww = PTW_EWW(wq);
					goto out;
				}

				if (wq->engine->emit_init_bweadcwumb) {
					eww = wq->engine->emit_init_bweadcwumb(wq);
					if (eww) {
						i915_wequest_add(wq);
						goto out;
					}
				}

				cs = intew_wing_begin(wq, 2);
				if (IS_EWW(cs)) {
					i915_wequest_add(wq);
					eww = PTW_EWW(cs);
					goto out;
				}

				if (p->ewwow[i]) {
					*cs++ = 0xdeadbeef;
					*cs++ = 0xdeadbeef;
				} ewse {
					*cs++ = MI_NOOP;
					*cs++ = MI_NOOP;
				}

				cwient[i] = i915_wequest_get(wq);
				i915_wequest_add(wq);
			}

			eww = wait_fow_submit(engine, cwient[0], HZ / 2);
			if (eww) {
				pw_eww("%s: fiwst wequest did not stawt within time!\n",
				       engine->name);
				eww = -ETIME;
				goto out;
			}

			fow (i = 0; i < AWWAY_SIZE(cwient); i++) {
				if (i915_wequest_wait(cwient[i], 0, HZ / 5) < 0)
					pw_debug("%s: %s wequest incompwete!\n",
						 engine->name,
						 ewwow_wepw(p->ewwow[i]));

				if (!i915_wequest_stawted(cwient[i])) {
					pw_eww("%s: %s wequest not stawted!\n",
					       engine->name,
					       ewwow_wepw(p->ewwow[i]));
					eww = -ETIME;
					goto out;
				}

				/* Kick the taskwet to pwocess the ewwow */
				intew_engine_fwush_submission(engine);
				if (cwient[i]->fence.ewwow != p->ewwow[i]) {
					pw_eww("%s: %s wequest (%s) with wwong ewwow code: %d\n",
					       engine->name,
					       ewwow_wepw(p->ewwow[i]),
					       i915_wequest_compweted(cwient[i]) ? "compweted" : "wunning",
					       cwient[i]->fence.ewwow);
					eww = -EINVAW;
					goto out;
				}
			}

out:
			fow (i = 0; i < AWWAY_SIZE(cwient); i++)
				if (cwient[i])
					i915_wequest_put(cwient[i]);
			if (eww) {
				pw_eww("%s: faiwed at phase[%zd] { %d, %d }\n",
				       engine->name, p - phases,
				       p->ewwow[0], p->ewwow[1]);
				bweak;
			}
		}

		st_engine_heawtbeat_enabwe(engine);
		if (eww) {
			intew_gt_set_wedged(gt);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int
emit_semaphowe_chain(stwuct i915_wequest *wq, stwuct i915_vma *vma, int idx)
{
	u32 *cs;

	cs = intew_wing_begin(wq, 10);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = MI_AWB_ON_OFF | MI_AWB_ENABWE;

	*cs++ = MI_SEMAPHOWE_WAIT |
		MI_SEMAPHOWE_GWOBAW_GTT |
		MI_SEMAPHOWE_POWW |
		MI_SEMAPHOWE_SAD_NEQ_SDD;
	*cs++ = 0;
	*cs++ = i915_ggtt_offset(vma) + 4 * idx;
	*cs++ = 0;

	if (idx > 0) {
		*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = i915_ggtt_offset(vma) + 4 * (idx - 1);
		*cs++ = 0;
		*cs++ = 1;
	} ewse {
		*cs++ = MI_NOOP;
		*cs++ = MI_NOOP;
		*cs++ = MI_NOOP;
		*cs++ = MI_NOOP;
	}

	*cs++ = MI_AWB_ON_OFF | MI_AWB_DISABWE;

	intew_wing_advance(wq, cs);
	wetuwn 0;
}

static stwuct i915_wequest *
semaphowe_queue(stwuct intew_engine_cs *engine, stwuct i915_vma *vma, int idx)
{
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	int eww;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn EWW_CAST(ce);

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		goto out_ce;

	eww = 0;
	if (wq->engine->emit_init_bweadcwumb)
		eww = wq->engine->emit_init_bweadcwumb(wq);
	if (eww == 0)
		eww = emit_semaphowe_chain(wq, vma, idx);
	if (eww == 0)
		i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (eww)
		wq = EWW_PTW(eww);

out_ce:
	intew_context_put(ce);
	wetuwn wq;
}

static int
wewease_queue(stwuct intew_engine_cs *engine,
	      stwuct i915_vma *vma,
	      int idx, int pwio)
{
	stwuct i915_sched_attw attw = {
		.pwiowity = pwio,
	};
	stwuct i915_wequest *wq;
	u32 *cs;

	wq = intew_engine_cweate_kewnew_wequest(engine);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = i915_ggtt_offset(vma) + 4 * (idx - 1);
	*cs++ = 0;
	*cs++ = 1;

	intew_wing_advance(wq, cs);

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	wocaw_bh_disabwe();
	engine->sched_engine->scheduwe(wq, &attw);
	wocaw_bh_enabwe(); /* kick taskwet */

	i915_wequest_put(wq);

	wetuwn 0;
}

static int
swice_semaphowe_queue(stwuct intew_engine_cs *outew,
		      stwuct i915_vma *vma,
		      int count)
{
	stwuct intew_engine_cs *engine;
	stwuct i915_wequest *head;
	enum intew_engine_id id;
	int eww, i, n = 0;

	head = semaphowe_queue(outew, vma, n++);
	if (IS_EWW(head))
		wetuwn PTW_EWW(head);

	fow_each_engine(engine, outew->gt, id) {
		if (!intew_engine_has_pweemption(engine))
			continue;

		fow (i = 0; i < count; i++) {
			stwuct i915_wequest *wq;

			wq = semaphowe_queue(engine, vma, n++);
			if (IS_EWW(wq)) {
				eww = PTW_EWW(wq);
				goto out;
			}

			i915_wequest_put(wq);
		}
	}

	eww = wewease_queue(outew, vma, n, I915_PWIOWITY_BAWWIEW);
	if (eww)
		goto out;

	if (i915_wequest_wait(head, 0,
			      2 * outew->gt->info.num_engines * (count + 2) * (count + 3)) < 0) {
		pw_eww("%s: Faiwed to swice awong semaphowe chain of wength (%d, %d)!\n",
		       outew->name, count, n);
		GEM_TWACE_DUMP();
		intew_gt_set_wedged(outew->gt);
		eww = -EIO;
	}

out:
	i915_wequest_put(head);
	wetuwn eww;
}

static int wive_timeswice_pweempt(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct dwm_i915_gem_object *obj;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct i915_vma *vma;
	void *vaddw;
	int eww = 0;

	/*
	 * If a wequest takes too wong, we wouwd wike to give othew usews
	 * a faiw go on the GPU. In pawticuwaw, usews may cweate batches
	 * that wait upon extewnaw input, whewe that input may even be
	 * suppwied by anothew GPU job. To avoid bwocking fowevew, we
	 * need to pweempt the cuwwent task and wepwace it with anothew
	 * weady task.
	 */
	if (!CONFIG_DWM_I915_TIMESWICE_DUWATION)
		wetuwn 0;

	obj = i915_gem_object_cweate_intewnaw(gt->i915, PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_obj;
	}

	vaddw = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(vaddw)) {
		eww = PTW_EWW(vaddw);
		goto eww_obj;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_GWOBAW);
	if (eww)
		goto eww_map;

	eww = i915_vma_sync(vma);
	if (eww)
		goto eww_pin;

	fow_each_engine(engine, gt, id) {
		if (!intew_engine_has_pweemption(engine))
			continue;

		memset(vaddw, 0, PAGE_SIZE);

		st_engine_heawtbeat_disabwe(engine);
		eww = swice_semaphowe_queue(engine, vma, 5);
		st_engine_heawtbeat_enabwe(engine);
		if (eww)
			goto eww_pin;

		if (igt_fwush_test(gt->i915)) {
			eww = -EIO;
			goto eww_pin;
		}
	}

eww_pin:
	i915_vma_unpin(vma);
eww_map:
	i915_gem_object_unpin_map(obj);
eww_obj:
	i915_gem_object_put(obj);
	wetuwn eww;
}

static stwuct i915_wequest *
cweate_wewindew(stwuct intew_context *ce,
		stwuct i915_wequest *wait,
		void *swot, int idx)
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

	if (wait) {
		eww = i915_wequest_await_dma_fence(wq, &wait->fence);
		if (eww)
			goto eww;
	}

	cs = intew_wing_begin(wq, 14);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww;
	}

	*cs++ = MI_AWB_ON_OFF | MI_AWB_ENABWE;
	*cs++ = MI_NOOP;

	*cs++ = MI_SEMAPHOWE_WAIT |
		MI_SEMAPHOWE_GWOBAW_GTT |
		MI_SEMAPHOWE_POWW |
		MI_SEMAPHOWE_SAD_GTE_SDD;
	*cs++ = idx;
	*cs++ = offset;
	*cs++ = 0;

	*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_weg_offset(WING_TIMESTAMP(wq->engine->mmio_base));
	*cs++ = offset + idx * sizeof(u32);
	*cs++ = 0;

	*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = idx + 1;

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

static int wive_timeswice_wewind(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/*
	 * The usuaw pwesumption on timeswice expiwation is that we wepwace
	 * the active context with anothew. Howevew, given a chain of
	 * dependencies we may end up with wepwacing the context with itsewf,
	 * but onwy a few of those wequests, fowcing us to wewind the
	 * WING_TAIW of the owiginaw wequest.
	 */
	if (!CONFIG_DWM_I915_TIMESWICE_DUWATION)
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		enum { A1, A2, B1 };
		enum { X = 1, Z, Y };
		stwuct i915_wequest *wq[3] = {};
		stwuct intew_context *ce;
		unsigned wong timeswice;
		int i, eww = 0;
		u32 *swot;

		if (!intew_engine_has_timeswices(engine))
			continue;

		/*
		 * A:wq1 -- semaphowe wait, timestamp X
		 * A:wq2 -- wwite timestamp Y
		 *
		 * B:wq1 [await A:wq1] -- wwite timestamp Z
		 *
		 * Fowce timeswice, wewease semaphowe.
		 *
		 * Expect execution/evawuation owdew XZY
		 */

		st_engine_heawtbeat_disabwe(engine);
		timeswice = xchg(&engine->pwops.timeswice_duwation_ms, 1);

		swot = memset32(engine->status_page.addw + 1000, 0, 4);

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto eww;
		}

		wq[A1] = cweate_wewindew(ce, NUWW, swot, X);
		if (IS_EWW(wq[A1])) {
			intew_context_put(ce);
			goto eww;
		}

		wq[A2] = cweate_wewindew(ce, NUWW, swot, Y);
		intew_context_put(ce);
		if (IS_EWW(wq[A2]))
			goto eww;

		eww = wait_fow_submit(engine, wq[A2], HZ / 2);
		if (eww) {
			pw_eww("%s: faiwed to submit fiwst context\n",
			       engine->name);
			goto eww;
		}

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto eww;
		}

		wq[B1] = cweate_wewindew(ce, wq[A1], swot, Z);
		intew_context_put(ce);
		if (IS_EWW(wq[2]))
			goto eww;

		eww = wait_fow_submit(engine, wq[B1], HZ / 2);
		if (eww) {
			pw_eww("%s: faiwed to submit second context\n",
			       engine->name);
			goto eww;
		}

		/* EWSP[] = { { A:wq1, A:wq2 }, { B:wq1 } } */
		ENGINE_TWACE(engine, "fowcing taskwet fow wewind\n");
		whiwe (i915_wequest_is_active(wq[A2])) { /* semaphowe yiewd! */
			/* Wait fow the timeswice to kick in */
			dew_timew(&engine->execwists.timew);
			taskwet_hi_scheduwe(&engine->sched_engine->taskwet);
			intew_engine_fwush_submission(engine);
		}
		/* -> EWSP[] = { { A:wq1 }, { B:wq1 } } */
		GEM_BUG_ON(!i915_wequest_is_active(wq[A1]));
		GEM_BUG_ON(!i915_wequest_is_active(wq[B1]));
		GEM_BUG_ON(i915_wequest_is_active(wq[A2]));

		/* Wewease the hounds! */
		swot[0] = 1;
		wmb(); /* "paiws" with GPU; pawanoid kick of intewnaw CPU$ */

		fow (i = 1; i <= 3; i++) {
			unsigned wong timeout = jiffies + HZ / 2;

			whiwe (!WEAD_ONCE(swot[i]) &&
			       time_befowe(jiffies, timeout))
				;

			if (!time_befowe(jiffies, timeout)) {
				pw_eww("%s: wq[%d] timed out\n",
				       engine->name, i - 1);
				eww = -ETIME;
				goto eww;
			}

			pw_debug("%s: swot[%d]:%x\n", engine->name, i, swot[i]);
		}

		/* XZY: XZ < XY */
		if (swot[Z] - swot[X] >= swot[Y] - swot[X]) {
			pw_eww("%s: timeswicing did not wun context B [%u] befowe A [%u]!\n",
			       engine->name,
			       swot[Z] - swot[X],
			       swot[Y] - swot[X]);
			eww = -EINVAW;
		}

eww:
		memset32(&swot[0], -1, 4);
		wmb();

		engine->pwops.timeswice_duwation_ms = timeswice;
		st_engine_heawtbeat_enabwe(engine);
		fow (i = 0; i < 3; i++)
			i915_wequest_put(wq[i]);
		if (igt_fwush_test(gt->i915))
			eww = -EIO;
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct i915_wequest *nop_wequest(stwuct intew_engine_cs *engine)
{
	stwuct i915_wequest *wq;

	wq = intew_engine_cweate_kewnew_wequest(engine);
	if (IS_EWW(wq))
		wetuwn wq;

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	wetuwn wq;
}

static wong swice_timeout(stwuct intew_engine_cs *engine)
{
	wong timeout;

	/* Enough time fow a timeswice to kick in, and kick out */
	timeout = 2 * msecs_to_jiffies_timeout(timeswice(engine));

	/* Enough time fow the nop wequest to compwete */
	timeout += HZ / 5;

	wetuwn timeout + 1;
}

static int wive_timeswice_queue(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct dwm_i915_gem_object *obj;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct i915_vma *vma;
	void *vaddw;
	int eww = 0;

	/*
	 * Make suwe that even if EWSP[0] and EWSP[1] awe fiwwed with
	 * timeswicing between them disabwed, we *do* enabwe timeswicing
	 * if the queue demands it. (Nowmawwy, we do not submit if
	 * EWSP[1] is awweady occupied, so must wewy on timeswicing to
	 * eject EWSP[0] in favouw of the queue.)
	 */
	if (!CONFIG_DWM_I915_TIMESWICE_DUWATION)
		wetuwn 0;

	obj = i915_gem_object_cweate_intewnaw(gt->i915, PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_obj;
	}

	vaddw = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(vaddw)) {
		eww = PTW_EWW(vaddw);
		goto eww_obj;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_GWOBAW);
	if (eww)
		goto eww_map;

	eww = i915_vma_sync(vma);
	if (eww)
		goto eww_pin;

	fow_each_engine(engine, gt, id) {
		stwuct i915_sched_attw attw = { .pwiowity = I915_PWIOWITY_MAX };
		stwuct i915_wequest *wq, *nop;

		if (!intew_engine_has_pweemption(engine))
			continue;

		st_engine_heawtbeat_disabwe(engine);
		memset(vaddw, 0, PAGE_SIZE);

		/* EWSP[0]: semaphowe wait */
		wq = semaphowe_queue(engine, vma, 0);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_heawtbeat;
		}
		engine->sched_engine->scheduwe(wq, &attw);
		eww = wait_fow_submit(engine, wq, HZ / 2);
		if (eww) {
			pw_eww("%s: Timed out twying to submit semaphowes\n",
			       engine->name);
			goto eww_wq;
		}

		/* EWSP[1]: nop wequest */
		nop = nop_wequest(engine);
		if (IS_EWW(nop)) {
			eww = PTW_EWW(nop);
			goto eww_wq;
		}
		eww = wait_fow_submit(engine, nop, HZ / 2);
		i915_wequest_put(nop);
		if (eww) {
			pw_eww("%s: Timed out twying to submit nop\n",
			       engine->name);
			goto eww_wq;
		}

		GEM_BUG_ON(i915_wequest_compweted(wq));
		GEM_BUG_ON(execwists_active(&engine->execwists) != wq);

		/* Queue: semaphowe signaw, matching pwiowity as semaphowe */
		eww = wewease_queue(engine, vma, 1, effective_pwio(wq));
		if (eww)
			goto eww_wq;

		/* Wait untiw we ack the wewease_queue and stawt timeswicing */
		do {
			cond_wesched();
			intew_engine_fwush_submission(engine);
		} whiwe (WEAD_ONCE(engine->execwists.pending[0]));

		/* Timeswice evewy jiffy, so within 2 we shouwd signaw */
		if (i915_wequest_wait(wq, 0, swice_timeout(engine)) < 0) {
			stwuct dwm_pwintew p =
				dwm_info_pwintew(gt->i915->dwm.dev);

			pw_eww("%s: Faiwed to timeswice into queue\n",
			       engine->name);
			intew_engine_dump(engine, &p,
					  "%s\n", engine->name);

			memset(vaddw, 0xff, PAGE_SIZE);
			eww = -EIO;
		}
eww_wq:
		i915_wequest_put(wq);
eww_heawtbeat:
		st_engine_heawtbeat_enabwe(engine);
		if (eww)
			bweak;
	}

eww_pin:
	i915_vma_unpin(vma);
eww_map:
	i915_gem_object_unpin_map(obj);
eww_obj:
	i915_gem_object_put(obj);
	wetuwn eww;
}

static int wive_timeswice_nopweempt(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	int eww = 0;

	/*
	 * We shouwd not timeswice into a wequest that is mawked with
	 * I915_WEQUEST_NOPWEEMPT.
	 */
	if (!CONFIG_DWM_I915_TIMESWICE_DUWATION)
		wetuwn 0;

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce;
		stwuct i915_wequest *wq;
		unsigned wong timeswice;

		if (!intew_engine_has_pweemption(engine))
			continue;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			bweak;
		}

		st_engine_heawtbeat_disabwe(engine);
		timeswice = xchg(&engine->pwops.timeswice_duwation_ms, 1);

		/* Cweate an unpweemptibwe spinnew */

		wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
		intew_context_put(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_heawtbeat;
		}

		i915_wequest_get(wq);
		i915_wequest_add(wq);

		if (!igt_wait_fow_spinnew(&spin, wq)) {
			i915_wequest_put(wq);
			eww = -ETIME;
			goto out_spin;
		}

		set_bit(I915_FENCE_FWAG_NOPWEEMPT, &wq->fence.fwags);
		i915_wequest_put(wq);

		/* Fowwowed by a maximum pwiowity bawwiew (heawtbeat) */

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto out_spin;
		}

		wq = intew_context_cweate_wequest(ce);
		intew_context_put(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_spin;
		}

		wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
		i915_wequest_get(wq);
		i915_wequest_add(wq);

		/*
		 * Wait untiw the bawwiew is in EWSP, and we know timeswicing
		 * wiww have been activated.
		 */
		if (wait_fow_submit(engine, wq, HZ / 2)) {
			i915_wequest_put(wq);
			eww = -ETIME;
			goto out_spin;
		}

		/*
		 * Since the EWSP[0] wequest is unpweemptibwe, it shouwd not
		 * awwow the maximum pwiowity bawwiew thwough. Wait wong
		 * enough to see if it is timeswiced in by mistake.
		 */
		if (i915_wequest_wait(wq, 0, swice_timeout(engine)) >= 0) {
			pw_eww("%s: I915_PWIOWITY_BAWWIEW wequest compweted, bypassing no-pweempt wequest\n",
			       engine->name);
			eww = -EINVAW;
		}
		i915_wequest_put(wq);

out_spin:
		igt_spinnew_end(&spin);
out_heawtbeat:
		xchg(&engine->pwops.timeswice_duwation_ms, timeswice);
		st_engine_heawtbeat_enabwe(engine);
		if (eww)
			bweak;

		if (igt_fwush_test(gt->i915)) {
			eww = -EIO;
			bweak;
		}
	}

	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static int wive_busywait_pweempt(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_gem_context *ctx_hi, *ctx_wo;
	stwuct intew_engine_cs *engine;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	enum intew_engine_id id;
	u32 *map;
	int eww;

	/*
	 * Vewify that even without HAS_WOGICAW_WING_PWEEMPTION, we can
	 * pweempt the busywaits used to synchwonise between wings.
	 */

	ctx_hi = kewnew_context(gt->i915, NUWW);
	if (IS_EWW(ctx_hi))
		wetuwn PTW_EWW(ctx_hi);

	ctx_hi->sched.pwiowity = I915_CONTEXT_MAX_USEW_PWIOWITY;

	ctx_wo = kewnew_context(gt->i915, NUWW);
	if (IS_EWW(ctx_wo)) {
		eww = PTW_EWW(ctx_wo);
		goto eww_ctx_hi;
	}

	ctx_wo->sched.pwiowity = I915_CONTEXT_MIN_USEW_PWIOWITY;

	obj = i915_gem_object_cweate_intewnaw(gt->i915, PAGE_SIZE);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto eww_ctx_wo;
	}

	map = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(map)) {
		eww = PTW_EWW(map);
		goto eww_obj;
	}

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_map;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_GWOBAW);
	if (eww)
		goto eww_map;

	eww = i915_vma_sync(vma);
	if (eww)
		goto eww_vma;

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wo, *hi;
		stwuct igt_wive_test t;
		u32 *cs;

		if (!intew_engine_has_pweemption(engine))
			continue;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name)) {
			eww = -EIO;
			goto eww_vma;
		}

		/*
		 * We cweate two wequests. The wow pwiowity wequest
		 * busywaits on a semaphowe (inside the wingbuffew whewe
		 * is shouwd be pweemptibwe) and the high pwiowity wequests
		 * uses a MI_STOWE_DWOWD_IMM to update the semaphowe vawue
		 * awwowing the fiwst wequest to compwete. If pweemption
		 * faiws, we hang instead.
		 */

		wo = igt_wequest_awwoc(ctx_wo, engine);
		if (IS_EWW(wo)) {
			eww = PTW_EWW(wo);
			goto eww_vma;
		}

		cs = intew_wing_begin(wo, 8);
		if (IS_EWW(cs)) {
			eww = PTW_EWW(cs);
			i915_wequest_add(wo);
			goto eww_vma;
		}

		*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = i915_ggtt_offset(vma);
		*cs++ = 0;
		*cs++ = 1;

		/* XXX Do we need a fwush + invawidate hewe? */

		*cs++ = MI_SEMAPHOWE_WAIT |
			MI_SEMAPHOWE_GWOBAW_GTT |
			MI_SEMAPHOWE_POWW |
			MI_SEMAPHOWE_SAD_EQ_SDD;
		*cs++ = 0;
		*cs++ = i915_ggtt_offset(vma);
		*cs++ = 0;

		intew_wing_advance(wo, cs);

		i915_wequest_get(wo);
		i915_wequest_add(wo);

		if (wait_fow(WEAD_ONCE(*map), 10)) {
			i915_wequest_put(wo);
			eww = -ETIMEDOUT;
			goto eww_vma;
		}

		/* Wow pwiowity wequest shouwd be busywaiting now */
		if (i915_wequest_wait(wo, 0, 1) != -ETIME) {
			i915_wequest_put(wo);
			pw_eww("%s: Busywaiting wequest did not!\n",
			       engine->name);
			eww = -EIO;
			goto eww_vma;
		}

		hi = igt_wequest_awwoc(ctx_hi, engine);
		if (IS_EWW(hi)) {
			eww = PTW_EWW(hi);
			i915_wequest_put(wo);
			goto eww_vma;
		}

		cs = intew_wing_begin(hi, 4);
		if (IS_EWW(cs)) {
			eww = PTW_EWW(cs);
			i915_wequest_add(hi);
			i915_wequest_put(wo);
			goto eww_vma;
		}

		*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = i915_ggtt_offset(vma);
		*cs++ = 0;
		*cs++ = 0;

		intew_wing_advance(hi, cs);
		i915_wequest_add(hi);

		if (i915_wequest_wait(wo, 0, HZ / 5) < 0) {
			stwuct dwm_pwintew p = dwm_info_pwintew(gt->i915->dwm.dev);

			pw_eww("%s: Faiwed to pweempt semaphowe busywait!\n",
			       engine->name);

			intew_engine_dump(engine, &p, "%s\n", engine->name);
			GEM_TWACE_DUMP();

			i915_wequest_put(wo);
			intew_gt_set_wedged(gt);
			eww = -EIO;
			goto eww_vma;
		}
		GEM_BUG_ON(WEAD_ONCE(*map));
		i915_wequest_put(wo);

		if (igt_wive_test_end(&t)) {
			eww = -EIO;
			goto eww_vma;
		}
	}

	eww = 0;
eww_vma:
	i915_vma_unpin(vma);
eww_map:
	i915_gem_object_unpin_map(obj);
eww_obj:
	i915_gem_object_put(obj);
eww_ctx_wo:
	kewnew_context_cwose(ctx_wo);
eww_ctx_hi:
	kewnew_context_cwose(ctx_hi);
	wetuwn eww;
}

static stwuct i915_wequest *
spinnew_cweate_wequest(stwuct igt_spinnew *spin,
		       stwuct i915_gem_context *ctx,
		       stwuct intew_engine_cs *engine,
		       u32 awb)
{
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;

	ce = i915_gem_context_get_engine(ctx, engine->wegacy_idx);
	if (IS_EWW(ce))
		wetuwn EWW_CAST(ce);

	wq = igt_spinnew_cweate_wequest(spin, ce, awb);
	intew_context_put(ce);
	wetuwn wq;
}

static int wive_pweempt(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_gem_context *ctx_hi, *ctx_wo;
	stwuct igt_spinnew spin_hi, spin_wo;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = -ENOMEM;

	ctx_hi = kewnew_context(gt->i915, NUWW);
	if (!ctx_hi)
		wetuwn -ENOMEM;
	ctx_hi->sched.pwiowity = I915_CONTEXT_MAX_USEW_PWIOWITY;

	ctx_wo = kewnew_context(gt->i915, NUWW);
	if (!ctx_wo)
		goto eww_ctx_hi;
	ctx_wo->sched.pwiowity = I915_CONTEXT_MIN_USEW_PWIOWITY;

	if (igt_spinnew_init(&spin_hi, gt))
		goto eww_ctx_wo;

	if (igt_spinnew_init(&spin_wo, gt))
		goto eww_spin_hi;

	fow_each_engine(engine, gt, id) {
		stwuct igt_wive_test t;
		stwuct i915_wequest *wq;

		if (!intew_engine_has_pweemption(engine))
			continue;

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name)) {
			eww = -EIO;
			goto eww_spin_wo;
		}

		wq = spinnew_cweate_wequest(&spin_wo, ctx_wo, engine,
					    MI_AWB_CHECK);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_spin_wo;
		}

		i915_wequest_add(wq);
		if (!igt_wait_fow_spinnew(&spin_wo, wq)) {
			GEM_TWACE("wo spinnew faiwed to stawt\n");
			GEM_TWACE_DUMP();
			intew_gt_set_wedged(gt);
			eww = -EIO;
			goto eww_spin_wo;
		}

		wq = spinnew_cweate_wequest(&spin_hi, ctx_hi, engine,
					    MI_AWB_CHECK);
		if (IS_EWW(wq)) {
			igt_spinnew_end(&spin_wo);
			eww = PTW_EWW(wq);
			goto eww_spin_wo;
		}

		i915_wequest_add(wq);
		if (!igt_wait_fow_spinnew(&spin_hi, wq)) {
			GEM_TWACE("hi spinnew faiwed to stawt\n");
			GEM_TWACE_DUMP();
			intew_gt_set_wedged(gt);
			eww = -EIO;
			goto eww_spin_wo;
		}

		igt_spinnew_end(&spin_hi);
		igt_spinnew_end(&spin_wo);

		if (igt_wive_test_end(&t)) {
			eww = -EIO;
			goto eww_spin_wo;
		}
	}

	eww = 0;
eww_spin_wo:
	igt_spinnew_fini(&spin_wo);
eww_spin_hi:
	igt_spinnew_fini(&spin_hi);
eww_ctx_wo:
	kewnew_context_cwose(ctx_wo);
eww_ctx_hi:
	kewnew_context_cwose(ctx_hi);
	wetuwn eww;
}

static int wive_wate_pweempt(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_gem_context *ctx_hi, *ctx_wo;
	stwuct igt_spinnew spin_hi, spin_wo;
	stwuct intew_engine_cs *engine;
	stwuct i915_sched_attw attw = {};
	enum intew_engine_id id;
	int eww = -ENOMEM;

	ctx_hi = kewnew_context(gt->i915, NUWW);
	if (!ctx_hi)
		wetuwn -ENOMEM;

	ctx_wo = kewnew_context(gt->i915, NUWW);
	if (!ctx_wo)
		goto eww_ctx_hi;

	if (igt_spinnew_init(&spin_hi, gt))
		goto eww_ctx_wo;

	if (igt_spinnew_init(&spin_wo, gt))
		goto eww_spin_hi;

	/* Make suwe ctx_wo stays befowe ctx_hi untiw we twiggew pweemption. */
	ctx_wo->sched.pwiowity = 1;

	fow_each_engine(engine, gt, id) {
		stwuct igt_wive_test t;
		stwuct i915_wequest *wq;

		if (!intew_engine_has_pweemption(engine))
			continue;

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name)) {
			eww = -EIO;
			goto eww_spin_wo;
		}

		wq = spinnew_cweate_wequest(&spin_wo, ctx_wo, engine,
					    MI_AWB_CHECK);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_spin_wo;
		}

		i915_wequest_add(wq);
		if (!igt_wait_fow_spinnew(&spin_wo, wq)) {
			pw_eww("Fiwst context faiwed to stawt\n");
			goto eww_wedged;
		}

		wq = spinnew_cweate_wequest(&spin_hi, ctx_hi, engine,
					    MI_NOOP);
		if (IS_EWW(wq)) {
			igt_spinnew_end(&spin_wo);
			eww = PTW_EWW(wq);
			goto eww_spin_wo;
		}

		i915_wequest_add(wq);
		if (igt_wait_fow_spinnew(&spin_hi, wq)) {
			pw_eww("Second context ovewtook fiwst?\n");
			goto eww_wedged;
		}

		attw.pwiowity = I915_PWIOWITY_MAX;
		engine->sched_engine->scheduwe(wq, &attw);

		if (!igt_wait_fow_spinnew(&spin_hi, wq)) {
			pw_eww("High pwiowity context faiwed to pweempt the wow pwiowity context\n");
			GEM_TWACE_DUMP();
			goto eww_wedged;
		}

		igt_spinnew_end(&spin_hi);
		igt_spinnew_end(&spin_wo);

		if (igt_wive_test_end(&t)) {
			eww = -EIO;
			goto eww_spin_wo;
		}
	}

	eww = 0;
eww_spin_wo:
	igt_spinnew_fini(&spin_wo);
eww_spin_hi:
	igt_spinnew_fini(&spin_hi);
eww_ctx_wo:
	kewnew_context_cwose(ctx_wo);
eww_ctx_hi:
	kewnew_context_cwose(ctx_hi);
	wetuwn eww;

eww_wedged:
	igt_spinnew_end(&spin_hi);
	igt_spinnew_end(&spin_wo);
	intew_gt_set_wedged(gt);
	eww = -EIO;
	goto eww_spin_wo;
}

stwuct pweempt_cwient {
	stwuct igt_spinnew spin;
	stwuct i915_gem_context *ctx;
};

static int pweempt_cwient_init(stwuct intew_gt *gt, stwuct pweempt_cwient *c)
{
	c->ctx = kewnew_context(gt->i915, NUWW);
	if (!c->ctx)
		wetuwn -ENOMEM;

	if (igt_spinnew_init(&c->spin, gt))
		goto eww_ctx;

	wetuwn 0;

eww_ctx:
	kewnew_context_cwose(c->ctx);
	wetuwn -ENOMEM;
}

static void pweempt_cwient_fini(stwuct pweempt_cwient *c)
{
	igt_spinnew_fini(&c->spin);
	kewnew_context_cwose(c->ctx);
}

static int wive_nopweempt(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct pweempt_cwient a, b;
	enum intew_engine_id id;
	int eww = -ENOMEM;

	/*
	 * Vewify that we can disabwe pweemption fow an individuaw wequest
	 * that may be being obsewved and not want to be intewwupted.
	 */

	if (pweempt_cwient_init(gt, &a))
		wetuwn -ENOMEM;
	if (pweempt_cwient_init(gt, &b))
		goto eww_cwient_a;
	b.ctx->sched.pwiowity = I915_PWIOWITY_MAX;

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq_a, *wq_b;

		if (!intew_engine_has_pweemption(engine))
			continue;

		engine->execwists.pweempt_hang.count = 0;

		wq_a = spinnew_cweate_wequest(&a.spin,
					      a.ctx, engine,
					      MI_AWB_CHECK);
		if (IS_EWW(wq_a)) {
			eww = PTW_EWW(wq_a);
			goto eww_cwient_b;
		}

		/* Wow pwiowity cwient, but unpweemptabwe! */
		__set_bit(I915_FENCE_FWAG_NOPWEEMPT, &wq_a->fence.fwags);

		i915_wequest_add(wq_a);
		if (!igt_wait_fow_spinnew(&a.spin, wq_a)) {
			pw_eww("Fiwst cwient faiwed to stawt\n");
			goto eww_wedged;
		}

		wq_b = spinnew_cweate_wequest(&b.spin,
					      b.ctx, engine,
					      MI_AWB_CHECK);
		if (IS_EWW(wq_b)) {
			eww = PTW_EWW(wq_b);
			goto eww_cwient_b;
		}

		i915_wequest_add(wq_b);

		/* B is much mowe impowtant than A! (But A is unpweemptabwe.) */
		GEM_BUG_ON(wq_pwio(wq_b) <= wq_pwio(wq_a));

		/* Wait wong enough fow pweemption and timeswicing */
		if (igt_wait_fow_spinnew(&b.spin, wq_b)) {
			pw_eww("Second cwient stawted too eawwy!\n");
			goto eww_wedged;
		}

		igt_spinnew_end(&a.spin);

		if (!igt_wait_fow_spinnew(&b.spin, wq_b)) {
			pw_eww("Second cwient faiwed to stawt\n");
			goto eww_wedged;
		}

		igt_spinnew_end(&b.spin);

		if (engine->execwists.pweempt_hang.count) {
			pw_eww("Pweemption wecowded x%d; shouwd have been suppwessed!\n",
			       engine->execwists.pweempt_hang.count);
			eww = -EINVAW;
			goto eww_wedged;
		}

		if (igt_fwush_test(gt->i915))
			goto eww_wedged;
	}

	eww = 0;
eww_cwient_b:
	pweempt_cwient_fini(&b);
eww_cwient_a:
	pweempt_cwient_fini(&a);
	wetuwn eww;

eww_wedged:
	igt_spinnew_end(&b.spin);
	igt_spinnew_end(&a.spin);
	intew_gt_set_wedged(gt);
	eww = -EIO;
	goto eww_cwient_b;
}

stwuct wive_pweempt_cancew {
	stwuct intew_engine_cs *engine;
	stwuct pweempt_cwient a, b;
};

static int __cancew_active0(stwuct wive_pweempt_cancew *awg)
{
	stwuct i915_wequest *wq;
	stwuct igt_wive_test t;
	int eww;

	/* Pweempt cancew of EWSP0 */
	GEM_TWACE("%s(%s)\n", __func__, awg->engine->name);
	if (igt_wive_test_begin(&t, awg->engine->i915,
				__func__, awg->engine->name))
		wetuwn -EIO;

	wq = spinnew_cweate_wequest(&awg->a.spin,
				    awg->a.ctx, awg->engine,
				    MI_AWB_CHECK);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cweaw_bit(CONTEXT_BANNED, &wq->context->fwags);
	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (!igt_wait_fow_spinnew(&awg->a.spin, wq)) {
		eww = -EIO;
		goto out;
	}

	intew_context_ban(wq->context, wq);
	eww = intew_engine_puwse(awg->engine);
	if (eww)
		goto out;

	eww = wait_fow_weset(awg->engine, wq, HZ / 2);
	if (eww) {
		pw_eww("Cancewwed infwight0 wequest did not weset\n");
		goto out;
	}

out:
	i915_wequest_put(wq);
	if (igt_wive_test_end(&t))
		eww = -EIO;
	wetuwn eww;
}

static int __cancew_active1(stwuct wive_pweempt_cancew *awg)
{
	stwuct i915_wequest *wq[2] = {};
	stwuct igt_wive_test t;
	int eww;

	/* Pweempt cancew of EWSP1 */
	GEM_TWACE("%s(%s)\n", __func__, awg->engine->name);
	if (igt_wive_test_begin(&t, awg->engine->i915,
				__func__, awg->engine->name))
		wetuwn -EIO;

	wq[0] = spinnew_cweate_wequest(&awg->a.spin,
				       awg->a.ctx, awg->engine,
				       MI_NOOP); /* no pweemption */
	if (IS_EWW(wq[0]))
		wetuwn PTW_EWW(wq[0]);

	cweaw_bit(CONTEXT_BANNED, &wq[0]->context->fwags);
	i915_wequest_get(wq[0]);
	i915_wequest_add(wq[0]);
	if (!igt_wait_fow_spinnew(&awg->a.spin, wq[0])) {
		eww = -EIO;
		goto out;
	}

	wq[1] = spinnew_cweate_wequest(&awg->b.spin,
				       awg->b.ctx, awg->engine,
				       MI_AWB_CHECK);
	if (IS_EWW(wq[1])) {
		eww = PTW_EWW(wq[1]);
		goto out;
	}

	cweaw_bit(CONTEXT_BANNED, &wq[1]->context->fwags);
	i915_wequest_get(wq[1]);
	eww = i915_wequest_await_dma_fence(wq[1], &wq[0]->fence);
	i915_wequest_add(wq[1]);
	if (eww)
		goto out;

	intew_context_ban(wq[1]->context, wq[1]);
	eww = intew_engine_puwse(awg->engine);
	if (eww)
		goto out;

	igt_spinnew_end(&awg->a.spin);
	eww = wait_fow_weset(awg->engine, wq[1], HZ / 2);
	if (eww)
		goto out;

	if (wq[0]->fence.ewwow != 0) {
		pw_eww("Nowmaw infwight0 wequest did not compwete\n");
		eww = -EINVAW;
		goto out;
	}

	if (wq[1]->fence.ewwow != -EIO) {
		pw_eww("Cancewwed infwight1 wequest did not wepowt -EIO\n");
		eww = -EINVAW;
		goto out;
	}

out:
	i915_wequest_put(wq[1]);
	i915_wequest_put(wq[0]);
	if (igt_wive_test_end(&t))
		eww = -EIO;
	wetuwn eww;
}

static int __cancew_queued(stwuct wive_pweempt_cancew *awg)
{
	stwuct i915_wequest *wq[3] = {};
	stwuct igt_wive_test t;
	int eww;

	/* Fuww EWSP and one in the wings */
	GEM_TWACE("%s(%s)\n", __func__, awg->engine->name);
	if (igt_wive_test_begin(&t, awg->engine->i915,
				__func__, awg->engine->name))
		wetuwn -EIO;

	wq[0] = spinnew_cweate_wequest(&awg->a.spin,
				       awg->a.ctx, awg->engine,
				       MI_AWB_CHECK);
	if (IS_EWW(wq[0]))
		wetuwn PTW_EWW(wq[0]);

	cweaw_bit(CONTEXT_BANNED, &wq[0]->context->fwags);
	i915_wequest_get(wq[0]);
	i915_wequest_add(wq[0]);
	if (!igt_wait_fow_spinnew(&awg->a.spin, wq[0])) {
		eww = -EIO;
		goto out;
	}

	wq[1] = igt_wequest_awwoc(awg->b.ctx, awg->engine);
	if (IS_EWW(wq[1])) {
		eww = PTW_EWW(wq[1]);
		goto out;
	}

	cweaw_bit(CONTEXT_BANNED, &wq[1]->context->fwags);
	i915_wequest_get(wq[1]);
	eww = i915_wequest_await_dma_fence(wq[1], &wq[0]->fence);
	i915_wequest_add(wq[1]);
	if (eww)
		goto out;

	wq[2] = spinnew_cweate_wequest(&awg->b.spin,
				       awg->a.ctx, awg->engine,
				       MI_AWB_CHECK);
	if (IS_EWW(wq[2])) {
		eww = PTW_EWW(wq[2]);
		goto out;
	}

	i915_wequest_get(wq[2]);
	eww = i915_wequest_await_dma_fence(wq[2], &wq[1]->fence);
	i915_wequest_add(wq[2]);
	if (eww)
		goto out;

	intew_context_ban(wq[2]->context, wq[2]);
	eww = intew_engine_puwse(awg->engine);
	if (eww)
		goto out;

	eww = wait_fow_weset(awg->engine, wq[2], HZ / 2);
	if (eww)
		goto out;

	if (wq[0]->fence.ewwow != -EIO) {
		pw_eww("Cancewwed infwight0 wequest did not wepowt -EIO\n");
		eww = -EINVAW;
		goto out;
	}

	/*
	 * The behaviow between having semaphowes and not is diffewent. With
	 * semaphowes the subsequent wequest is on the hawdwawe and not cancewwed
	 * whiwe without the wequest is hewd in the dwivew and cancewwed.
	 */
	if (intew_engine_has_semaphowes(wq[1]->engine) &&
	    wq[1]->fence.ewwow != 0) {
		pw_eww("Nowmaw infwight1 wequest did not compwete\n");
		eww = -EINVAW;
		goto out;
	}

	if (wq[2]->fence.ewwow != -EIO) {
		pw_eww("Cancewwed queued wequest did not wepowt -EIO\n");
		eww = -EINVAW;
		goto out;
	}

out:
	i915_wequest_put(wq[2]);
	i915_wequest_put(wq[1]);
	i915_wequest_put(wq[0]);
	if (igt_wive_test_end(&t))
		eww = -EIO;
	wetuwn eww;
}

static int __cancew_hostiwe(stwuct wive_pweempt_cancew *awg)
{
	stwuct i915_wequest *wq;
	int eww;

	/* Pweempt cancew non-pweemptibwe spinnew in EWSP0 */
	if (!CONFIG_DWM_I915_PWEEMPT_TIMEOUT)
		wetuwn 0;

	if (!intew_has_weset_engine(awg->engine->gt))
		wetuwn 0;

	GEM_TWACE("%s(%s)\n", __func__, awg->engine->name);
	wq = spinnew_cweate_wequest(&awg->a.spin,
				    awg->a.ctx, awg->engine,
				    MI_NOOP); /* pweemption disabwed */
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cweaw_bit(CONTEXT_BANNED, &wq->context->fwags);
	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (!igt_wait_fow_spinnew(&awg->a.spin, wq)) {
		eww = -EIO;
		goto out;
	}

	intew_context_ban(wq->context, wq);
	eww = intew_engine_puwse(awg->engine); /* fowce weset */
	if (eww)
		goto out;

	eww = wait_fow_weset(awg->engine, wq, HZ / 2);
	if (eww) {
		pw_eww("Cancewwed infwight0 wequest did not weset\n");
		goto out;
	}

out:
	i915_wequest_put(wq);
	if (igt_fwush_test(awg->engine->i915))
		eww = -EIO;
	wetuwn eww;
}

static void fowce_weset_timeout(stwuct intew_engine_cs *engine)
{
	engine->weset_timeout.pwobabiwity = 999;
	atomic_set(&engine->weset_timeout.times, -1);
}

static void cancew_weset_timeout(stwuct intew_engine_cs *engine)
{
	memset(&engine->weset_timeout, 0, sizeof(engine->weset_timeout));
}

static int __cancew_faiw(stwuct wive_pweempt_cancew *awg)
{
	stwuct intew_engine_cs *engine = awg->engine;
	stwuct i915_wequest *wq;
	int eww;

	if (!CONFIG_DWM_I915_PWEEMPT_TIMEOUT)
		wetuwn 0;

	if (!intew_has_weset_engine(engine->gt))
		wetuwn 0;

	GEM_TWACE("%s(%s)\n", __func__, engine->name);
	wq = spinnew_cweate_wequest(&awg->a.spin,
				    awg->a.ctx, engine,
				    MI_NOOP); /* pweemption disabwed */
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cweaw_bit(CONTEXT_BANNED, &wq->context->fwags);
	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (!igt_wait_fow_spinnew(&awg->a.spin, wq)) {
		eww = -EIO;
		goto out;
	}

	intew_context_set_banned(wq->context);

	eww = intew_engine_puwse(engine);
	if (eww)
		goto out;

	fowce_weset_timeout(engine);

	/* fowce pweempt weset [faiwuwe] */
	whiwe (!engine->execwists.pending[0])
		intew_engine_fwush_submission(engine);
	dew_timew_sync(&engine->execwists.pweempt);
	intew_engine_fwush_submission(engine);

	cancew_weset_timeout(engine);

	/* aftew faiwuwe, wequiwe heawtbeats to weset device */
	intew_engine_set_heawtbeat(engine, 1);
	eww = wait_fow_weset(engine, wq, HZ / 2);
	intew_engine_set_heawtbeat(engine,
				   engine->defauwts.heawtbeat_intewvaw_ms);
	if (eww) {
		pw_eww("Cancewwed infwight0 wequest did not weset\n");
		goto out;
	}

out:
	i915_wequest_put(wq);
	if (igt_fwush_test(engine->i915))
		eww = -EIO;
	wetuwn eww;
}

static int wive_pweempt_cancew(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct wive_pweempt_cancew data;
	enum intew_engine_id id;
	int eww = -ENOMEM;

	/*
	 * To cancew an infwight context, we need to fiwst wemove it fwom the
	 * GPU. That sounds wike pweemption! Pwus a wittwe bit of bookkeeping.
	 */

	if (pweempt_cwient_init(gt, &data.a))
		wetuwn -ENOMEM;
	if (pweempt_cwient_init(gt, &data.b))
		goto eww_cwient_a;

	fow_each_engine(data.engine, gt, id) {
		if (!intew_engine_has_pweemption(data.engine))
			continue;

		eww = __cancew_active0(&data);
		if (eww)
			goto eww_wedged;

		eww = __cancew_active1(&data);
		if (eww)
			goto eww_wedged;

		eww = __cancew_queued(&data);
		if (eww)
			goto eww_wedged;

		eww = __cancew_hostiwe(&data);
		if (eww)
			goto eww_wedged;

		eww = __cancew_faiw(&data);
		if (eww)
			goto eww_wedged;
	}

	eww = 0;
eww_cwient_b:
	pweempt_cwient_fini(&data.b);
eww_cwient_a:
	pweempt_cwient_fini(&data.a);
	wetuwn eww;

eww_wedged:
	GEM_TWACE_DUMP();
	igt_spinnew_end(&data.b.spin);
	igt_spinnew_end(&data.a.spin);
	intew_gt_set_wedged(gt);
	goto eww_cwient_b;
}

static int wive_suppwess_sewf_pweempt(void *awg)
{
	stwuct i915_sched_attw attw = { .pwiowity = I915_PWIOWITY_MAX };
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct pweempt_cwient a, b;
	enum intew_engine_id id;
	int eww = -ENOMEM;

	/*
	 * Vewify that if a pweemption wequest does not cause a change in
	 * the cuwwent execution owdew, the pweempt-to-idwe injection is
	 * skipped and that we do not accidentawwy appwy it aftew the CS
	 * compwetion event.
	 */

	if (intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0; /* pwesume bwack bwox */

	if (intew_vgpu_active(gt->i915))
		wetuwn 0; /* GVT fowces singwe powt & wequest submission */

	if (pweempt_cwient_init(gt, &a))
		wetuwn -ENOMEM;
	if (pweempt_cwient_init(gt, &b))
		goto eww_cwient_a;

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq_a, *wq_b;
		int depth;

		if (!intew_engine_has_pweemption(engine))
			continue;

		if (igt_fwush_test(gt->i915))
			goto eww_wedged;

		st_engine_heawtbeat_disabwe(engine);
		engine->execwists.pweempt_hang.count = 0;

		wq_a = spinnew_cweate_wequest(&a.spin,
					      a.ctx, engine,
					      MI_NOOP);
		if (IS_EWW(wq_a)) {
			eww = PTW_EWW(wq_a);
			st_engine_heawtbeat_enabwe(engine);
			goto eww_cwient_b;
		}

		i915_wequest_add(wq_a);
		if (!igt_wait_fow_spinnew(&a.spin, wq_a)) {
			pw_eww("Fiwst cwient faiwed to stawt\n");
			st_engine_heawtbeat_enabwe(engine);
			goto eww_wedged;
		}

		/* Keep postponing the timew to avoid pwematuwe swicing */
		mod_timew(&engine->execwists.timew, jiffies + HZ);
		fow (depth = 0; depth < 8; depth++) {
			wq_b = spinnew_cweate_wequest(&b.spin,
						      b.ctx, engine,
						      MI_NOOP);
			if (IS_EWW(wq_b)) {
				eww = PTW_EWW(wq_b);
				st_engine_heawtbeat_enabwe(engine);
				goto eww_cwient_b;
			}
			i915_wequest_add(wq_b);

			GEM_BUG_ON(i915_wequest_compweted(wq_a));
			engine->sched_engine->scheduwe(wq_a, &attw);
			igt_spinnew_end(&a.spin);

			if (!igt_wait_fow_spinnew(&b.spin, wq_b)) {
				pw_eww("Second cwient faiwed to stawt\n");
				st_engine_heawtbeat_enabwe(engine);
				goto eww_wedged;
			}

			swap(a, b);
			wq_a = wq_b;
		}
		igt_spinnew_end(&a.spin);

		if (engine->execwists.pweempt_hang.count) {
			pw_eww("Pweemption on %s wecowded x%d, depth %d; shouwd have been suppwessed!\n",
			       engine->name,
			       engine->execwists.pweempt_hang.count,
			       depth);
			st_engine_heawtbeat_enabwe(engine);
			eww = -EINVAW;
			goto eww_cwient_b;
		}

		st_engine_heawtbeat_enabwe(engine);
		if (igt_fwush_test(gt->i915))
			goto eww_wedged;
	}

	eww = 0;
eww_cwient_b:
	pweempt_cwient_fini(&b);
eww_cwient_a:
	pweempt_cwient_fini(&a);
	wetuwn eww;

eww_wedged:
	igt_spinnew_end(&b.spin);
	igt_spinnew_end(&a.spin);
	intew_gt_set_wedged(gt);
	eww = -EIO;
	goto eww_cwient_b;
}

static int wive_chain_pweempt(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct pweempt_cwient hi, wo;
	enum intew_engine_id id;
	int eww = -ENOMEM;

	/*
	 * Buiwd a chain AB...BA between two contexts (A, B) and wequest
	 * pweemption of the wast wequest. It shouwd then compwete befowe
	 * the pweviouswy submitted spinnew in B.
	 */

	if (pweempt_cwient_init(gt, &hi))
		wetuwn -ENOMEM;

	if (pweempt_cwient_init(gt, &wo))
		goto eww_cwient_hi;

	fow_each_engine(engine, gt, id) {
		stwuct i915_sched_attw attw = { .pwiowity = I915_PWIOWITY_MAX };
		stwuct igt_wive_test t;
		stwuct i915_wequest *wq;
		int wing_size, count, i;

		if (!intew_engine_has_pweemption(engine))
			continue;

		wq = spinnew_cweate_wequest(&wo.spin,
					    wo.ctx, engine,
					    MI_AWB_CHECK);
		if (IS_EWW(wq))
			goto eww_wedged;

		i915_wequest_get(wq);
		i915_wequest_add(wq);

		wing_size = wq->wa_taiw - wq->head;
		if (wing_size < 0)
			wing_size += wq->wing->size;
		wing_size = wq->wing->size / wing_size;
		pw_debug("%s(%s): Using maximum of %d wequests\n",
			 __func__, engine->name, wing_size);

		igt_spinnew_end(&wo.spin);
		if (i915_wequest_wait(wq, 0, HZ / 2) < 0) {
			pw_eww("Timed out waiting to fwush %s\n", engine->name);
			i915_wequest_put(wq);
			goto eww_wedged;
		}
		i915_wequest_put(wq);

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name)) {
			eww = -EIO;
			goto eww_wedged;
		}

		fow_each_pwime_numbew_fwom(count, 1, wing_size) {
			wq = spinnew_cweate_wequest(&hi.spin,
						    hi.ctx, engine,
						    MI_AWB_CHECK);
			if (IS_EWW(wq))
				goto eww_wedged;
			i915_wequest_add(wq);
			if (!igt_wait_fow_spinnew(&hi.spin, wq))
				goto eww_wedged;

			wq = spinnew_cweate_wequest(&wo.spin,
						    wo.ctx, engine,
						    MI_AWB_CHECK);
			if (IS_EWW(wq))
				goto eww_wedged;
			i915_wequest_add(wq);

			fow (i = 0; i < count; i++) {
				wq = igt_wequest_awwoc(wo.ctx, engine);
				if (IS_EWW(wq))
					goto eww_wedged;
				i915_wequest_add(wq);
			}

			wq = igt_wequest_awwoc(hi.ctx, engine);
			if (IS_EWW(wq))
				goto eww_wedged;

			i915_wequest_get(wq);
			i915_wequest_add(wq);
			engine->sched_engine->scheduwe(wq, &attw);

			igt_spinnew_end(&hi.spin);
			if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
				stwuct dwm_pwintew p =
					dwm_info_pwintew(gt->i915->dwm.dev);

				pw_eww("Faiwed to pweempt ovew chain of %d\n",
				       count);
				intew_engine_dump(engine, &p,
						  "%s\n", engine->name);
				i915_wequest_put(wq);
				goto eww_wedged;
			}
			igt_spinnew_end(&wo.spin);
			i915_wequest_put(wq);

			wq = igt_wequest_awwoc(wo.ctx, engine);
			if (IS_EWW(wq))
				goto eww_wedged;

			i915_wequest_get(wq);
			i915_wequest_add(wq);

			if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
				stwuct dwm_pwintew p =
					dwm_info_pwintew(gt->i915->dwm.dev);

				pw_eww("Faiwed to fwush wow pwiowity chain of %d wequests\n",
				       count);
				intew_engine_dump(engine, &p,
						  "%s\n", engine->name);

				i915_wequest_put(wq);
				goto eww_wedged;
			}
			i915_wequest_put(wq);
		}

		if (igt_wive_test_end(&t)) {
			eww = -EIO;
			goto eww_wedged;
		}
	}

	eww = 0;
eww_cwient_wo:
	pweempt_cwient_fini(&wo);
eww_cwient_hi:
	pweempt_cwient_fini(&hi);
	wetuwn eww;

eww_wedged:
	igt_spinnew_end(&hi.spin);
	igt_spinnew_end(&wo.spin);
	intew_gt_set_wedged(gt);
	eww = -EIO;
	goto eww_cwient_wo;
}

static int cweate_gang(stwuct intew_engine_cs *engine,
		       stwuct i915_wequest **pwev)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	stwuct i915_vma *vma;
	u32 *cs;
	int eww;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	obj = i915_gem_object_cweate_intewnaw(engine->i915, 4096);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto eww_ce;
	}

	vma = i915_vma_instance(obj, ce->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_obj;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww)
		goto eww_obj;

	cs = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_obj;
	}

	/* Semaphowe tawget: spin untiw zewo */
	*cs++ = MI_AWB_ON_OFF | MI_AWB_ENABWE;

	*cs++ = MI_SEMAPHOWE_WAIT |
		MI_SEMAPHOWE_POWW |
		MI_SEMAPHOWE_SAD_EQ_SDD;
	*cs++ = 0;
	*cs++ = wowew_32_bits(i915_vma_offset(vma));
	*cs++ = uppew_32_bits(i915_vma_offset(vma));

	if (*pwev) {
		u64 offset = i915_vma_offset((*pwev)->batch);

		/* Tewminate the spinnew in the next wowew pwiowity batch. */
		*cs++ = MI_STOWE_DWOWD_IMM_GEN4;
		*cs++ = wowew_32_bits(offset);
		*cs++ = uppew_32_bits(offset);
		*cs++ = 0;
	}

	*cs++ = MI_BATCH_BUFFEW_END;
	i915_gem_object_fwush_map(obj);
	i915_gem_object_unpin_map(obj);

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_obj;
	}

	wq->batch = i915_vma_get(vma);
	i915_wequest_get(wq);

	eww = igt_vma_move_to_active_unwocked(vma, wq, 0);
	if (!eww)
		eww = wq->engine->emit_bb_stawt(wq,
						i915_vma_offset(vma),
						PAGE_SIZE, 0);
	i915_wequest_add(wq);
	if (eww)
		goto eww_wq;

	i915_gem_object_put(obj);
	intew_context_put(ce);

	wq->mock.wink.next = &(*pwev)->mock.wink;
	*pwev = wq;
	wetuwn 0;

eww_wq:
	i915_vma_put(wq->batch);
	i915_wequest_put(wq);
eww_obj:
	i915_gem_object_put(obj);
eww_ce:
	intew_context_put(ce);
	wetuwn eww;
}

static int __wive_pweempt_wing(stwuct intew_engine_cs *engine,
			       stwuct igt_spinnew *spin,
			       int queue_sz, int wing_sz)
{
	stwuct intew_context *ce[2] = {};
	stwuct i915_wequest *wq;
	stwuct igt_wive_test t;
	int eww = 0;
	int n;

	if (igt_wive_test_begin(&t, engine->i915, __func__, engine->name))
		wetuwn -EIO;

	fow (n = 0; n < AWWAY_SIZE(ce); n++) {
		stwuct intew_context *tmp;

		tmp = intew_context_cweate(engine);
		if (IS_EWW(tmp)) {
			eww = PTW_EWW(tmp);
			goto eww_ce;
		}

		tmp->wing_size = wing_sz;

		eww = intew_context_pin(tmp);
		if (eww) {
			intew_context_put(tmp);
			goto eww_ce;
		}

		memset32(tmp->wing->vaddw,
			 0xdeadbeef, /* twiggew a hang if executed */
			 tmp->wing->vma->size / sizeof(u32));

		ce[n] = tmp;
	}

	wq = igt_spinnew_cweate_wequest(spin, ce[0], MI_AWB_CHECK);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_ce;
	}

	i915_wequest_get(wq);
	wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
	i915_wequest_add(wq);

	if (!igt_wait_fow_spinnew(spin, wq)) {
		intew_gt_set_wedged(engine->gt);
		i915_wequest_put(wq);
		eww = -ETIME;
		goto eww_ce;
	}

	/* Fiww the wing, untiw we wiww cause a wwap */
	n = 0;
	whiwe (ce[0]->wing->taiw - wq->wa_taiw <= queue_sz) {
		stwuct i915_wequest *tmp;

		tmp = intew_context_cweate_wequest(ce[0]);
		if (IS_EWW(tmp)) {
			eww = PTW_EWW(tmp);
			i915_wequest_put(wq);
			goto eww_ce;
		}

		i915_wequest_add(tmp);
		intew_engine_fwush_submission(engine);
		n++;
	}
	intew_engine_fwush_submission(engine);
	pw_debug("%s: Fiwwed %d with %d nop taiws {size:%x, taiw:%x, emit:%x, wq.taiw:%x}\n",
		 engine->name, queue_sz, n,
		 ce[0]->wing->size,
		 ce[0]->wing->taiw,
		 ce[0]->wing->emit,
		 wq->taiw);
	i915_wequest_put(wq);

	/* Cweate a second wequest to pweempt the fiwst wing */
	wq = intew_context_cweate_wequest(ce[1]);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_ce;
	}

	wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
	i915_wequest_get(wq);
	i915_wequest_add(wq);

	eww = wait_fow_submit(engine, wq, HZ / 2);
	i915_wequest_put(wq);
	if (eww) {
		pw_eww("%s: pweemption wequest was not submitted\n",
		       engine->name);
		eww = -ETIME;
	}

	pw_debug("%s: wing[0]:{ taiw:%x, emit:%x }, wing[1]:{ taiw:%x, emit:%x }\n",
		 engine->name,
		 ce[0]->wing->taiw, ce[0]->wing->emit,
		 ce[1]->wing->taiw, ce[1]->wing->emit);

eww_ce:
	intew_engine_fwush_submission(engine);
	igt_spinnew_end(spin);
	fow (n = 0; n < AWWAY_SIZE(ce); n++) {
		if (IS_EWW_OW_NUWW(ce[n]))
			bweak;

		intew_context_unpin(ce[n]);
		intew_context_put(ce[n]);
	}
	if (igt_wive_test_end(&t))
		eww = -EIO;
	wetuwn eww;
}

static int wive_pweempt_wing(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct igt_spinnew spin;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Check that we wowwback wawge chunks of a wing in owdew to do a
	 * pweemption event. Simiwaw to wive_unwite_wing, but wooking at
	 * wing size wathew than the impact of intew_wing_diwection().
	 */

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	fow_each_engine(engine, gt, id) {
		int n;

		if (!intew_engine_has_pweemption(engine))
			continue;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		st_engine_heawtbeat_disabwe(engine);

		fow (n = 0; n <= 3; n++) {
			eww = __wive_pweempt_wing(engine, &spin,
						  n * SZ_4K / 4, SZ_4K);
			if (eww)
				bweak;
		}

		st_engine_heawtbeat_enabwe(engine);
		if (eww)
			bweak;
	}

	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static int wive_pweempt_gang(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/*
	 * Buiwd as wong a chain of pweemptews as we can, with each
	 * wequest highew pwiowity than the wast. Once we awe weady, we wewease
	 * the wast batch which then pwecowates down the chain, each weweasing
	 * the next owdest in tuwn. The intent is to simpwy push as hawd as we
	 * can with the numbew of pweemptions, twying to exceed nawwow HW
	 * wimits. At a minimum, we insist that we can sowt aww the usew
	 * high pwiowity wevews into execution owdew.
	 */

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq = NUWW;
		stwuct igt_wive_test t;
		IGT_TIMEOUT(end_time);
		int pwio = 0;
		int eww = 0;
		u32 *cs;

		if (!intew_engine_has_pweemption(engine))
			continue;

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name))
			wetuwn -EIO;

		do {
			stwuct i915_sched_attw attw = { .pwiowity = pwio++ };

			eww = cweate_gang(engine, &wq);
			if (eww)
				bweak;

			/* Submit each spinnew at incweasing pwiowity */
			engine->sched_engine->scheduwe(wq, &attw);
		} whiwe (pwio <= I915_PWIOWITY_MAX &&
			 !__igt_timeout(end_time, NUWW));
		pw_debug("%s: Pweempt chain of %d wequests\n",
			 engine->name, pwio);

		/*
		 * Such that the wast spinnew is the highest pwiowity and
		 * shouwd execute fiwst. When that spinnew compwetes,
		 * it wiww tewminate the next wowest spinnew untiw thewe
		 * awe no mowe spinnews and the gang is compwete.
		 */
		cs = i915_gem_object_pin_map_unwocked(wq->batch->obj, I915_MAP_WC);
		if (!IS_EWW(cs)) {
			*cs = 0;
			i915_gem_object_unpin_map(wq->batch->obj);
		} ewse {
			eww = PTW_EWW(cs);
			intew_gt_set_wedged(gt);
		}

		whiwe (wq) { /* wait fow each wq fwom highest to wowest pwio */
			stwuct i915_wequest *n = wist_next_entwy(wq, mock.wink);

			if (eww == 0 && i915_wequest_wait(wq, 0, HZ / 5) < 0) {
				stwuct dwm_pwintew p =
					dwm_info_pwintew(engine->i915->dwm.dev);

				pw_eww("Faiwed to fwush chain of %d wequests, at %d\n",
				       pwio, wq_pwio(wq));
				intew_engine_dump(engine, &p,
						  "%s\n", engine->name);

				eww = -ETIME;
			}

			i915_vma_put(wq->batch);
			i915_wequest_put(wq);
			wq = n;
		}

		if (igt_wive_test_end(&t))
			eww = -EIO;
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct i915_vma *
cweate_gpw_usew(stwuct intew_engine_cs *engine,
		stwuct i915_vma *wesuwt,
		unsigned int offset)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	u32 *cs;
	int eww;
	int i;

	obj = i915_gem_object_cweate_intewnaw(engine->i915, 4096);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	vma = i915_vma_instance(obj, wesuwt->vm, NUWW);
	if (IS_EWW(vma)) {
		i915_gem_object_put(obj);
		wetuwn vma;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww) {
		i915_vma_put(vma);
		wetuwn EWW_PTW(eww);
	}

	cs = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(cs)) {
		i915_vma_put(vma);
		wetuwn EWW_CAST(cs);
	}

	/* Aww GPW awe cweaw fow new contexts. We use GPW(0) as a constant */
	*cs++ = MI_WOAD_WEGISTEW_IMM(1);
	*cs++ = CS_GPW(engine, 0);
	*cs++ = 1;

	fow (i = 1; i < NUM_GPW; i++) {
		u64 addw;

		/*
		 * Pewfowm: GPW[i]++
		 *
		 * As we wead and wwite into the context saved GPW[i], if
		 * we westawt this batch buffew fwom an eawwiew point, we
		 * wiww wepeat the incwement and stowe a vawue > 1.
		 */
		*cs++ = MI_MATH(4);
		*cs++ = MI_MATH_WOAD(MI_MATH_WEG_SWCA, MI_MATH_WEG(i));
		*cs++ = MI_MATH_WOAD(MI_MATH_WEG_SWCB, MI_MATH_WEG(0));
		*cs++ = MI_MATH_ADD;
		*cs++ = MI_MATH_STOWE(MI_MATH_WEG(i), MI_MATH_WEG_ACCU);

		addw = i915_vma_offset(wesuwt) + offset + i * sizeof(*cs);
		*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8;
		*cs++ = CS_GPW(engine, 2 * i);
		*cs++ = wowew_32_bits(addw);
		*cs++ = uppew_32_bits(addw);

		*cs++ = MI_SEMAPHOWE_WAIT |
			MI_SEMAPHOWE_POWW |
			MI_SEMAPHOWE_SAD_GTE_SDD;
		*cs++ = i;
		*cs++ = wowew_32_bits(i915_vma_offset(wesuwt));
		*cs++ = uppew_32_bits(i915_vma_offset(wesuwt));
	}

	*cs++ = MI_BATCH_BUFFEW_END;
	i915_gem_object_fwush_map(obj);
	i915_gem_object_unpin_map(obj);

	wetuwn vma;
}

static stwuct i915_vma *cweate_gwobaw(stwuct intew_gt *gt, size_t sz)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	int eww;

	obj = i915_gem_object_cweate_intewnaw(gt->i915, sz);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		i915_gem_object_put(obj);
		wetuwn vma;
	}

	eww = i915_ggtt_pin(vma, NUWW, 0, 0);
	if (eww) {
		i915_vma_put(vma);
		wetuwn EWW_PTW(eww);
	}

	wetuwn vma;
}

static stwuct i915_wequest *
cweate_gpw_cwient(stwuct intew_engine_cs *engine,
		  stwuct i915_vma *gwobaw,
		  unsigned int offset)
{
	stwuct i915_vma *batch, *vma;
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	int eww;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn EWW_CAST(ce);

	vma = i915_vma_instance(gwobaw->obj, ce->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto out_ce;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww)
		goto out_ce;

	batch = cweate_gpw_usew(engine, vma, offset);
	if (IS_EWW(batch)) {
		eww = PTW_EWW(batch);
		goto out_vma;
	}

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out_batch;
	}

	eww = igt_vma_move_to_active_unwocked(vma, wq, 0);

	i915_vma_wock(batch);
	if (!eww)
		eww = i915_vma_move_to_active(batch, wq, 0);
	if (!eww)
		eww = wq->engine->emit_bb_stawt(wq,
						i915_vma_offset(batch),
						PAGE_SIZE, 0);
	i915_vma_unwock(batch);
	i915_vma_unpin(batch);

	if (!eww)
		i915_wequest_get(wq);
	i915_wequest_add(wq);

out_batch:
	i915_vma_put(batch);
out_vma:
	i915_vma_unpin(vma);
out_ce:
	intew_context_put(ce);
	wetuwn eww ? EWW_PTW(eww) : wq;
}

static int pweempt_usew(stwuct intew_engine_cs *engine,
			stwuct i915_vma *gwobaw,
			int id)
{
	stwuct i915_sched_attw attw = {
		.pwiowity = I915_PWIOWITY_MAX
	};
	stwuct i915_wequest *wq;
	int eww = 0;
	u32 *cs;

	wq = intew_engine_cweate_kewnew_wequest(engine);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = i915_ggtt_offset(gwobaw);
	*cs++ = 0;
	*cs++ = id;

	intew_wing_advance(wq, cs);

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	engine->sched_engine->scheduwe(wq, &attw);

	if (i915_wequest_wait(wq, 0, HZ / 2) < 0)
		eww = -ETIME;
	i915_wequest_put(wq);

	wetuwn eww;
}

static int wive_pweempt_usew(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct i915_vma *gwobaw;
	enum intew_engine_id id;
	u32 *wesuwt;
	int eww = 0;

	/*
	 * In ouw othew tests, we wook at pweemption in cawefuwwy
	 * contwowwed conditions in the wingbuffew. Since most of the
	 * time is spent in usew batches, most of ouw pweemptions natuwawwy
	 * occuw thewe. We want to vewify that when we pweempt inside a batch
	 * we continue on fwom the cuwwent instwuction and do not woww back
	 * to the stawt, ow anothew eawwiew awbitwation point.
	 *
	 * To vewify this, we cweate a batch which is a mixtuwe of
	 * MI_MATH (gpw++) MI_SWM (gpw) and pweemption points. Then with
	 * a few pweempting contexts thwown into the mix, we wook fow any
	 * wepeated instwuctions (which show up as incowwect vawues).
	 */

	gwobaw = cweate_gwobaw(gt, 4096);
	if (IS_EWW(gwobaw))
		wetuwn PTW_EWW(gwobaw);

	wesuwt = i915_gem_object_pin_map_unwocked(gwobaw->obj, I915_MAP_WC);
	if (IS_EWW(wesuwt)) {
		i915_vma_unpin_and_wewease(&gwobaw, 0);
		wetuwn PTW_EWW(wesuwt);
	}

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *cwient[3] = {};
		stwuct igt_wive_test t;
		int i;

		if (!intew_engine_has_pweemption(engine))
			continue;

		if (GWAPHICS_VEW(gt->i915) == 8 && engine->cwass != WENDEW_CWASS)
			continue; /* we need pew-context GPW */

		if (igt_wive_test_begin(&t, gt->i915, __func__, engine->name)) {
			eww = -EIO;
			bweak;
		}

		memset(wesuwt, 0, 4096);

		fow (i = 0; i < AWWAY_SIZE(cwient); i++) {
			stwuct i915_wequest *wq;

			wq = cweate_gpw_cwient(engine, gwobaw,
					       NUM_GPW * i * sizeof(u32));
			if (IS_EWW(wq)) {
				eww = PTW_EWW(wq);
				goto end_test;
			}

			cwient[i] = wq;
		}

		/* Continuouswy pweempt the set of 3 wunning contexts */
		fow (i = 1; i <= NUM_GPW; i++) {
			eww = pweempt_usew(engine, gwobaw, i);
			if (eww)
				goto end_test;
		}

		if (WEAD_ONCE(wesuwt[0]) != NUM_GPW) {
			pw_eww("%s: Faiwed to wewease semaphowe\n",
			       engine->name);
			eww = -EIO;
			goto end_test;
		}

		fow (i = 0; i < AWWAY_SIZE(cwient); i++) {
			int gpw;

			if (i915_wequest_wait(cwient[i], 0, HZ / 2) < 0) {
				eww = -ETIME;
				goto end_test;
			}

			fow (gpw = 1; gpw < NUM_GPW; gpw++) {
				if (wesuwt[NUM_GPW * i + gpw] != 1) {
					pw_eww("%s: Invawid wesuwt, cwient %d, gpw %d, wesuwt: %d\n",
					       engine->name,
					       i, gpw, wesuwt[NUM_GPW * i + gpw]);
					eww = -EINVAW;
					goto end_test;
				}
			}
		}

end_test:
		fow (i = 0; i < AWWAY_SIZE(cwient); i++) {
			if (!cwient[i])
				bweak;

			i915_wequest_put(cwient[i]);
		}

		/* Fwush the semaphowes on ewwow */
		smp_stowe_mb(wesuwt[0], -1);
		if (igt_wive_test_end(&t))
			eww = -EIO;
		if (eww)
			bweak;
	}

	i915_vma_unpin_and_wewease(&gwobaw, I915_VMA_WEWEASE_MAP);
	wetuwn eww;
}

static int wive_pweempt_timeout(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_gem_context *ctx_hi, *ctx_wo;
	stwuct igt_spinnew spin_wo;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = -ENOMEM;

	/*
	 * Check that we fowce pweemption to occuw by cancewwing the pwevious
	 * context if it wefuses to yiewd the GPU.
	 */
	if (!CONFIG_DWM_I915_PWEEMPT_TIMEOUT)
		wetuwn 0;

	if (!intew_has_weset_engine(gt))
		wetuwn 0;

	ctx_hi = kewnew_context(gt->i915, NUWW);
	if (!ctx_hi)
		wetuwn -ENOMEM;
	ctx_hi->sched.pwiowity = I915_CONTEXT_MAX_USEW_PWIOWITY;

	ctx_wo = kewnew_context(gt->i915, NUWW);
	if (!ctx_wo)
		goto eww_ctx_hi;
	ctx_wo->sched.pwiowity = I915_CONTEXT_MIN_USEW_PWIOWITY;

	if (igt_spinnew_init(&spin_wo, gt))
		goto eww_ctx_wo;

	fow_each_engine(engine, gt, id) {
		unsigned wong saved_timeout;
		stwuct i915_wequest *wq;

		if (!intew_engine_has_pweemption(engine))
			continue;

		wq = spinnew_cweate_wequest(&spin_wo, ctx_wo, engine,
					    MI_NOOP); /* pweemption disabwed */
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_spin_wo;
		}

		i915_wequest_add(wq);
		if (!igt_wait_fow_spinnew(&spin_wo, wq)) {
			intew_gt_set_wedged(gt);
			eww = -EIO;
			goto eww_spin_wo;
		}

		wq = igt_wequest_awwoc(ctx_hi, engine);
		if (IS_EWW(wq)) {
			igt_spinnew_end(&spin_wo);
			eww = PTW_EWW(wq);
			goto eww_spin_wo;
		}

		/* Fwush the pwevious CS ack befowe changing timeouts */
		whiwe (WEAD_ONCE(engine->execwists.pending[0]))
			cpu_wewax();

		saved_timeout = engine->pwops.pweempt_timeout_ms;
		engine->pwops.pweempt_timeout_ms = 1; /* in ms, -> 1 jiffie */

		i915_wequest_get(wq);
		i915_wequest_add(wq);

		intew_engine_fwush_submission(engine);
		engine->pwops.pweempt_timeout_ms = saved_timeout;

		if (i915_wequest_wait(wq, 0, HZ / 10) < 0) {
			intew_gt_set_wedged(gt);
			i915_wequest_put(wq);
			eww = -ETIME;
			goto eww_spin_wo;
		}

		igt_spinnew_end(&spin_wo);
		i915_wequest_put(wq);
	}

	eww = 0;
eww_spin_wo:
	igt_spinnew_fini(&spin_wo);
eww_ctx_wo:
	kewnew_context_cwose(ctx_wo);
eww_ctx_hi:
	kewnew_context_cwose(ctx_hi);
	wetuwn eww;
}

static int wandom_wange(stwuct wnd_state *wnd, int min, int max)
{
	wetuwn i915_pwandom_u32_max_state(max - min, wnd) + min;
}

static int wandom_pwiowity(stwuct wnd_state *wnd)
{
	wetuwn wandom_wange(wnd, I915_PWIOWITY_MIN, I915_PWIOWITY_MAX);
}

stwuct pweempt_smoke {
	stwuct intew_gt *gt;
	stwuct kthwead_wowk wowk;
	stwuct i915_gem_context **contexts;
	stwuct intew_engine_cs *engine;
	stwuct dwm_i915_gem_object *batch;
	unsigned int ncontext;
	stwuct wnd_state pwng;
	unsigned wong count;
	int wesuwt;
};

static stwuct i915_gem_context *smoke_context(stwuct pweempt_smoke *smoke)
{
	wetuwn smoke->contexts[i915_pwandom_u32_max_state(smoke->ncontext,
							  &smoke->pwng)];
}

static int smoke_submit(stwuct pweempt_smoke *smoke,
			stwuct i915_gem_context *ctx, int pwio,
			stwuct dwm_i915_gem_object *batch)
{
	stwuct i915_wequest *wq;
	stwuct i915_vma *vma = NUWW;
	int eww = 0;

	if (batch) {
		stwuct i915_addwess_space *vm;

		vm = i915_gem_context_get_eb_vm(ctx);
		vma = i915_vma_instance(batch, vm, NUWW);
		i915_vm_put(vm);
		if (IS_EWW(vma))
			wetuwn PTW_EWW(vma);

		eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
		if (eww)
			wetuwn eww;
	}

	ctx->sched.pwiowity = pwio;

	wq = igt_wequest_awwoc(ctx, smoke->engine);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto unpin;
	}

	if (vma) {
		eww = igt_vma_move_to_active_unwocked(vma, wq, 0);
		if (!eww)
			eww = wq->engine->emit_bb_stawt(wq,
							i915_vma_offset(vma),
							PAGE_SIZE, 0);
	}

	i915_wequest_add(wq);

unpin:
	if (vma)
		i915_vma_unpin(vma);

	wetuwn eww;
}

static void smoke_cwescendo_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct pweempt_smoke *smoke = containew_of(wowk, typeof(*smoke), wowk);
	IGT_TIMEOUT(end_time);
	unsigned wong count;

	count = 0;
	do {
		stwuct i915_gem_context *ctx = smoke_context(smoke);

		smoke->wesuwt = smoke_submit(smoke, ctx,
					     count % I915_PWIOWITY_MAX,
					     smoke->batch);

		count++;
	} whiwe (!smoke->wesuwt && count < smoke->ncontext &&
		 !__igt_timeout(end_time, NUWW));

	smoke->count = count;
}

static int smoke_cwescendo(stwuct pweempt_smoke *smoke, unsigned int fwags)
#define BATCH BIT(0)
{
	stwuct kthwead_wowkew *wowkew[I915_NUM_ENGINES] = {};
	stwuct pweempt_smoke *awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	unsigned wong count;
	int eww = 0;

	awg = kmawwoc_awway(I915_NUM_ENGINES, sizeof(*awg), GFP_KEWNEW);
	if (!awg)
		wetuwn -ENOMEM;

	memset(awg, 0, I915_NUM_ENGINES * sizeof(*awg));

	fow_each_engine(engine, smoke->gt, id) {
		awg[id] = *smoke;
		awg[id].engine = engine;
		if (!(fwags & BATCH))
			awg[id].batch = NUWW;
		awg[id].count = 0;

		wowkew[id] = kthwead_cweate_wowkew(0, "igt/smoke:%d", id);
		if (IS_EWW(wowkew[id])) {
			eww = PTW_EWW(wowkew[id]);
			bweak;
		}

		kthwead_init_wowk(&awg[id].wowk, smoke_cwescendo_wowk);
		kthwead_queue_wowk(wowkew[id], &awg[id].wowk);
	}

	count = 0;
	fow_each_engine(engine, smoke->gt, id) {
		if (IS_EWW_OW_NUWW(wowkew[id]))
			continue;

		kthwead_fwush_wowk(&awg[id].wowk);
		if (awg[id].wesuwt && !eww)
			eww = awg[id].wesuwt;

		count += awg[id].count;

		kthwead_destwoy_wowkew(wowkew[id]);
	}

	pw_info("Submitted %wu cwescendo:%x wequests acwoss %d engines and %d contexts\n",
		count, fwags, smoke->gt->info.num_engines, smoke->ncontext);

	kfwee(awg);
	wetuwn 0;
}

static int smoke_wandom(stwuct pweempt_smoke *smoke, unsigned int fwags)
{
	enum intew_engine_id id;
	IGT_TIMEOUT(end_time);
	unsigned wong count;

	count = 0;
	do {
		fow_each_engine(smoke->engine, smoke->gt, id) {
			stwuct i915_gem_context *ctx = smoke_context(smoke);
			int eww;

			eww = smoke_submit(smoke,
					   ctx, wandom_pwiowity(&smoke->pwng),
					   fwags & BATCH ? smoke->batch : NUWW);
			if (eww)
				wetuwn eww;

			count++;
		}
	} whiwe (count < smoke->ncontext && !__igt_timeout(end_time, NUWW));

	pw_info("Submitted %wu wandom:%x wequests acwoss %d engines and %d contexts\n",
		count, fwags, smoke->gt->info.num_engines, smoke->ncontext);
	wetuwn 0;
}

static int wive_pweempt_smoke(void *awg)
{
	stwuct pweempt_smoke smoke = {
		.gt = awg,
		.pwng = I915_WND_STATE_INITIAWIZEW(i915_sewftest.wandom_seed),
		.ncontext = 256,
	};
	const unsigned int phase[] = { 0, BATCH };
	stwuct igt_wive_test t;
	int eww = -ENOMEM;
	u32 *cs;
	int n;

	smoke.contexts = kmawwoc_awway(smoke.ncontext,
				       sizeof(*smoke.contexts),
				       GFP_KEWNEW);
	if (!smoke.contexts)
		wetuwn -ENOMEM;

	smoke.batch =
		i915_gem_object_cweate_intewnaw(smoke.gt->i915, PAGE_SIZE);
	if (IS_EWW(smoke.batch)) {
		eww = PTW_EWW(smoke.batch);
		goto eww_fwee;
	}

	cs = i915_gem_object_pin_map_unwocked(smoke.batch, I915_MAP_WB);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_batch;
	}
	fow (n = 0; n < PAGE_SIZE / sizeof(*cs) - 1; n++)
		cs[n] = MI_AWB_CHECK;
	cs[n] = MI_BATCH_BUFFEW_END;
	i915_gem_object_fwush_map(smoke.batch);
	i915_gem_object_unpin_map(smoke.batch);

	if (igt_wive_test_begin(&t, smoke.gt->i915, __func__, "aww")) {
		eww = -EIO;
		goto eww_batch;
	}

	fow (n = 0; n < smoke.ncontext; n++) {
		smoke.contexts[n] = kewnew_context(smoke.gt->i915, NUWW);
		if (!smoke.contexts[n])
			goto eww_ctx;
	}

	fow (n = 0; n < AWWAY_SIZE(phase); n++) {
		eww = smoke_cwescendo(&smoke, phase[n]);
		if (eww)
			goto eww_ctx;

		eww = smoke_wandom(&smoke, phase[n]);
		if (eww)
			goto eww_ctx;
	}

eww_ctx:
	if (igt_wive_test_end(&t))
		eww = -EIO;

	fow (n = 0; n < smoke.ncontext; n++) {
		if (!smoke.contexts[n])
			bweak;
		kewnew_context_cwose(smoke.contexts[n]);
	}

eww_batch:
	i915_gem_object_put(smoke.batch);
eww_fwee:
	kfwee(smoke.contexts);

	wetuwn eww;
}

static int nop_viwtuaw_engine(stwuct intew_gt *gt,
			      stwuct intew_engine_cs **sibwings,
			      unsigned int nsibwing,
			      unsigned int nctx,
			      unsigned int fwags)
#define CHAIN BIT(0)
{
	IGT_TIMEOUT(end_time);
	stwuct i915_wequest *wequest[16] = {};
	stwuct intew_context *ve[16];
	unsigned wong n, pwime, nc;
	stwuct igt_wive_test t;
	ktime_t times[2] = {};
	int eww;

	GEM_BUG_ON(!nctx || nctx > AWWAY_SIZE(ve));

	fow (n = 0; n < nctx; n++) {
		ve[n] = intew_engine_cweate_viwtuaw(sibwings, nsibwing, 0);
		if (IS_EWW(ve[n])) {
			eww = PTW_EWW(ve[n]);
			nctx = n;
			goto out;
		}

		eww = intew_context_pin(ve[n]);
		if (eww) {
			intew_context_put(ve[n]);
			nctx = n;
			goto out;
		}
	}

	eww = igt_wive_test_begin(&t, gt->i915, __func__, ve[0]->engine->name);
	if (eww)
		goto out;

	fow_each_pwime_numbew_fwom(pwime, 1, 8192) {
		times[1] = ktime_get_waw();

		if (fwags & CHAIN) {
			fow (nc = 0; nc < nctx; nc++) {
				fow (n = 0; n < pwime; n++) {
					stwuct i915_wequest *wq;

					wq = i915_wequest_cweate(ve[nc]);
					if (IS_EWW(wq)) {
						eww = PTW_EWW(wq);
						goto out;
					}

					if (wequest[nc])
						i915_wequest_put(wequest[nc]);
					wequest[nc] = i915_wequest_get(wq);
					i915_wequest_add(wq);
				}
			}
		} ewse {
			fow (n = 0; n < pwime; n++) {
				fow (nc = 0; nc < nctx; nc++) {
					stwuct i915_wequest *wq;

					wq = i915_wequest_cweate(ve[nc]);
					if (IS_EWW(wq)) {
						eww = PTW_EWW(wq);
						goto out;
					}

					if (wequest[nc])
						i915_wequest_put(wequest[nc]);
					wequest[nc] = i915_wequest_get(wq);
					i915_wequest_add(wq);
				}
			}
		}

		fow (nc = 0; nc < nctx; nc++) {
			if (i915_wequest_wait(wequest[nc], 0, HZ / 10) < 0) {
				pw_eww("%s(%s): wait fow %wwx:%wwd timed out\n",
				       __func__, ve[0]->engine->name,
				       wequest[nc]->fence.context,
				       wequest[nc]->fence.seqno);

				GEM_TWACE("%s(%s) faiwed at wequest %wwx:%wwd\n",
					  __func__, ve[0]->engine->name,
					  wequest[nc]->fence.context,
					  wequest[nc]->fence.seqno);
				GEM_TWACE_DUMP();
				intew_gt_set_wedged(gt);
				bweak;
			}
		}

		times[1] = ktime_sub(ktime_get_waw(), times[1]);
		if (pwime == 1)
			times[0] = times[1];

		fow (nc = 0; nc < nctx; nc++) {
			i915_wequest_put(wequest[nc]);
			wequest[nc] = NUWW;
		}

		if (__igt_timeout(end_time, NUWW))
			bweak;
	}

	eww = igt_wive_test_end(&t);
	if (eww)
		goto out;

	pw_info("Wequestx%d watencies on %s: 1 = %wwuns, %wu = %wwuns\n",
		nctx, ve[0]->engine->name, ktime_to_ns(times[0]),
		pwime, div64_u64(ktime_to_ns(times[1]), pwime));

out:
	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	fow (nc = 0; nc < nctx; nc++) {
		i915_wequest_put(wequest[nc]);
		intew_context_unpin(ve[nc]);
		intew_context_put(ve[nc]);
	}
	wetuwn eww;
}

static unsigned int
__sewect_sibwings(stwuct intew_gt *gt,
		  unsigned int cwass,
		  stwuct intew_engine_cs **sibwings,
		  boow (*fiwtew)(const stwuct intew_engine_cs *))
{
	unsigned int n = 0;
	unsigned int inst;

	fow (inst = 0; inst <= MAX_ENGINE_INSTANCE; inst++) {
		if (!gt->engine_cwass[cwass][inst])
			continue;

		if (fiwtew && !fiwtew(gt->engine_cwass[cwass][inst]))
			continue;

		sibwings[n++] = gt->engine_cwass[cwass][inst];
	}

	wetuwn n;
}

static unsigned int
sewect_sibwings(stwuct intew_gt *gt,
		unsigned int cwass,
		stwuct intew_engine_cs **sibwings)
{
	wetuwn __sewect_sibwings(gt, cwass, sibwings, NUWW);
}

static int wive_viwtuaw_engine(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *sibwings[MAX_ENGINE_INSTANCE + 1];
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	unsigned int cwass;
	int eww;

	if (intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		eww = nop_viwtuaw_engine(gt, &engine, 1, 1, 0);
		if (eww) {
			pw_eww("Faiwed to wwap engine %s: eww=%d\n",
			       engine->name, eww);
			wetuwn eww;
		}
	}

	fow (cwass = 0; cwass <= MAX_ENGINE_CWASS; cwass++) {
		int nsibwing, n;

		nsibwing = sewect_sibwings(gt, cwass, sibwings);
		if (nsibwing < 2)
			continue;

		fow (n = 1; n <= nsibwing + 1; n++) {
			eww = nop_viwtuaw_engine(gt, sibwings, nsibwing,
						 n, 0);
			if (eww)
				wetuwn eww;
		}

		eww = nop_viwtuaw_engine(gt, sibwings, nsibwing, n, CHAIN);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mask_viwtuaw_engine(stwuct intew_gt *gt,
			       stwuct intew_engine_cs **sibwings,
			       unsigned int nsibwing)
{
	stwuct i915_wequest *wequest[MAX_ENGINE_INSTANCE + 1];
	stwuct intew_context *ve;
	stwuct igt_wive_test t;
	unsigned int n;
	int eww;

	/*
	 * Check that by setting the execution mask on a wequest, we can
	 * westwict it to ouw desiwed engine within the viwtuaw engine.
	 */

	ve = intew_engine_cweate_viwtuaw(sibwings, nsibwing, 0);
	if (IS_EWW(ve)) {
		eww = PTW_EWW(ve);
		goto out_cwose;
	}

	eww = intew_context_pin(ve);
	if (eww)
		goto out_put;

	eww = igt_wive_test_begin(&t, gt->i915, __func__, ve->engine->name);
	if (eww)
		goto out_unpin;

	fow (n = 0; n < nsibwing; n++) {
		wequest[n] = i915_wequest_cweate(ve);
		if (IS_EWW(wequest[n])) {
			eww = PTW_EWW(wequest[n]);
			nsibwing = n;
			goto out;
		}

		/* Wevewse owdew as it's mowe wikewy to be unnatuwaw */
		wequest[n]->execution_mask = sibwings[nsibwing - n - 1]->mask;

		i915_wequest_get(wequest[n]);
		i915_wequest_add(wequest[n]);
	}

	fow (n = 0; n < nsibwing; n++) {
		if (i915_wequest_wait(wequest[n], 0, HZ / 10) < 0) {
			pw_eww("%s(%s): wait fow %wwx:%wwd timed out\n",
			       __func__, ve->engine->name,
			       wequest[n]->fence.context,
			       wequest[n]->fence.seqno);

			GEM_TWACE("%s(%s) faiwed at wequest %wwx:%wwd\n",
				  __func__, ve->engine->name,
				  wequest[n]->fence.context,
				  wequest[n]->fence.seqno);
			GEM_TWACE_DUMP();
			intew_gt_set_wedged(gt);
			eww = -EIO;
			goto out;
		}

		if (wequest[n]->engine != sibwings[nsibwing - n - 1]) {
			pw_eww("Executed on wwong sibwing '%s', expected '%s'\n",
			       wequest[n]->engine->name,
			       sibwings[nsibwing - n - 1]->name);
			eww = -EINVAW;
			goto out;
		}
	}

	eww = igt_wive_test_end(&t);
out:
	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	fow (n = 0; n < nsibwing; n++)
		i915_wequest_put(wequest[n]);

out_unpin:
	intew_context_unpin(ve);
out_put:
	intew_context_put(ve);
out_cwose:
	wetuwn eww;
}

static int wive_viwtuaw_mask(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *sibwings[MAX_ENGINE_INSTANCE + 1];
	unsigned int cwass;
	int eww;

	if (intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0;

	fow (cwass = 0; cwass <= MAX_ENGINE_CWASS; cwass++) {
		unsigned int nsibwing;

		nsibwing = sewect_sibwings(gt, cwass, sibwings);
		if (nsibwing < 2)
			continue;

		eww = mask_viwtuaw_engine(gt, sibwings, nsibwing);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int swicein_viwtuaw_engine(stwuct intew_gt *gt,
				  stwuct intew_engine_cs **sibwings,
				  unsigned int nsibwing)
{
	const wong timeout = swice_timeout(sibwings[0]);
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	stwuct igt_spinnew spin;
	unsigned int n;
	int eww = 0;

	/*
	 * Viwtuaw wequests must take pawt in timeswicing on the tawget engines.
	 */

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	fow (n = 0; n < nsibwing; n++) {
		ce = intew_context_cweate(sibwings[n]);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto out;
		}

		wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
		intew_context_put(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out;
		}

		i915_wequest_add(wq);
	}

	ce = intew_engine_cweate_viwtuaw(sibwings, nsibwing, 0);
	if (IS_EWW(ce)) {
		eww = PTW_EWW(ce);
		goto out;
	}

	wq = intew_context_cweate_wequest(ce);
	intew_context_put(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out;
	}

	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (i915_wequest_wait(wq, 0, timeout) < 0) {
		GEM_TWACE_EWW("%s(%s) faiwed to swice in viwtuaw wequest\n",
			      __func__, wq->engine->name);
		GEM_TWACE_DUMP();
		intew_gt_set_wedged(gt);
		eww = -EIO;
	}
	i915_wequest_put(wq);

out:
	igt_spinnew_end(&spin);
	if (igt_fwush_test(gt->i915))
		eww = -EIO;
	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static int swiceout_viwtuaw_engine(stwuct intew_gt *gt,
				   stwuct intew_engine_cs **sibwings,
				   unsigned int nsibwing)
{
	const wong timeout = swice_timeout(sibwings[0]);
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	stwuct igt_spinnew spin;
	unsigned int n;
	int eww = 0;

	/*
	 * Viwtuaw wequests must awwow othews a faiw timeswice.
	 */

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	/* XXX We do not handwe ovewsubscwiption and faiwness with nowmaw wq */
	fow (n = 0; n < nsibwing; n++) {
		ce = intew_engine_cweate_viwtuaw(sibwings, nsibwing, 0);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto out;
		}

		wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
		intew_context_put(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out;
		}

		i915_wequest_add(wq);
	}

	fow (n = 0; !eww && n < nsibwing; n++) {
		ce = intew_context_cweate(sibwings[n]);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto out;
		}

		wq = intew_context_cweate_wequest(ce);
		intew_context_put(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out;
		}

		i915_wequest_get(wq);
		i915_wequest_add(wq);
		if (i915_wequest_wait(wq, 0, timeout) < 0) {
			GEM_TWACE_EWW("%s(%s) faiwed to swice out viwtuaw wequest\n",
				      __func__, sibwings[n]->name);
			GEM_TWACE_DUMP();
			intew_gt_set_wedged(gt);
			eww = -EIO;
		}
		i915_wequest_put(wq);
	}

out:
	igt_spinnew_end(&spin);
	if (igt_fwush_test(gt->i915))
		eww = -EIO;
	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static int wive_viwtuaw_swice(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *sibwings[MAX_ENGINE_INSTANCE + 1];
	unsigned int cwass;
	int eww;

	if (intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0;

	fow (cwass = 0; cwass <= MAX_ENGINE_CWASS; cwass++) {
		unsigned int nsibwing;

		nsibwing = __sewect_sibwings(gt, cwass, sibwings,
					     intew_engine_has_timeswices);
		if (nsibwing < 2)
			continue;

		eww = swicein_viwtuaw_engine(gt, sibwings, nsibwing);
		if (eww)
			wetuwn eww;

		eww = swiceout_viwtuaw_engine(gt, sibwings, nsibwing);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int pwesewved_viwtuaw_engine(stwuct intew_gt *gt,
				    stwuct intew_engine_cs **sibwings,
				    unsigned int nsibwing)
{
	stwuct i915_wequest *wast = NUWW;
	stwuct intew_context *ve;
	stwuct i915_vma *scwatch;
	stwuct igt_wive_test t;
	unsigned int n;
	int eww = 0;
	u32 *cs;

	scwatch =
		__vm_cweate_scwatch_fow_wead_pinned(&sibwings[0]->gt->ggtt->vm,
						    PAGE_SIZE);
	if (IS_EWW(scwatch))
		wetuwn PTW_EWW(scwatch);

	eww = i915_vma_sync(scwatch);
	if (eww)
		goto out_scwatch;

	ve = intew_engine_cweate_viwtuaw(sibwings, nsibwing, 0);
	if (IS_EWW(ve)) {
		eww = PTW_EWW(ve);
		goto out_scwatch;
	}

	eww = intew_context_pin(ve);
	if (eww)
		goto out_put;

	eww = igt_wive_test_begin(&t, gt->i915, __func__, ve->engine->name);
	if (eww)
		goto out_unpin;

	fow (n = 0; n < NUM_GPW_DW; n++) {
		stwuct intew_engine_cs *engine = sibwings[n % nsibwing];
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ve);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_end;
		}

		i915_wequest_put(wast);
		wast = i915_wequest_get(wq);

		cs = intew_wing_begin(wq, 8);
		if (IS_EWW(cs)) {
			i915_wequest_add(wq);
			eww = PTW_EWW(cs);
			goto out_end;
		}

		*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
		*cs++ = CS_GPW(engine, n);
		*cs++ = i915_ggtt_offset(scwatch) + n * sizeof(u32);
		*cs++ = 0;

		*cs++ = MI_WOAD_WEGISTEW_IMM(1);
		*cs++ = CS_GPW(engine, (n + 1) % NUM_GPW_DW);
		*cs++ = n + 1;

		*cs++ = MI_NOOP;
		intew_wing_advance(wq, cs);

		/* Westwict this wequest to wun on a pawticuwaw engine */
		wq->execution_mask = engine->mask;
		i915_wequest_add(wq);
	}

	if (i915_wequest_wait(wast, 0, HZ / 5) < 0) {
		eww = -ETIME;
		goto out_end;
	}

	cs = i915_gem_object_pin_map_unwocked(scwatch->obj, I915_MAP_WB);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto out_end;
	}

	fow (n = 0; n < NUM_GPW_DW; n++) {
		if (cs[n] != n) {
			pw_eww("Incowwect vawue[%d] found fow GPW[%d]\n",
			       cs[n], n);
			eww = -EINVAW;
			bweak;
		}
	}

	i915_gem_object_unpin_map(scwatch->obj);

out_end:
	if (igt_wive_test_end(&t))
		eww = -EIO;
	i915_wequest_put(wast);
out_unpin:
	intew_context_unpin(ve);
out_put:
	intew_context_put(ve);
out_scwatch:
	i915_vma_unpin_and_wewease(&scwatch, 0);
	wetuwn eww;
}

static int wive_viwtuaw_pwesewved(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *sibwings[MAX_ENGINE_INSTANCE + 1];
	unsigned int cwass;

	/*
	 * Check that the context image wetains non-pwiviweged (usew) wegistews
	 * fwom one engine to the next. Fow this we check that the CS_GPW
	 * awe pwesewved.
	 */

	if (intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0;

	/* As we use CS_GPW we cannot wun befowe they existed on aww engines. */
	if (GWAPHICS_VEW(gt->i915) < 9)
		wetuwn 0;

	fow (cwass = 0; cwass <= MAX_ENGINE_CWASS; cwass++) {
		int nsibwing, eww;

		nsibwing = sewect_sibwings(gt, cwass, sibwings);
		if (nsibwing < 2)
			continue;

		eww = pwesewved_viwtuaw_engine(gt, sibwings, nsibwing);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int weset_viwtuaw_engine(stwuct intew_gt *gt,
				stwuct intew_engine_cs **sibwings,
				unsigned int nsibwing)
{
	stwuct intew_engine_cs *engine;
	stwuct intew_context *ve;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq;
	unsigned int n;
	int eww = 0;

	/*
	 * In owdew to suppowt offwine ewwow captuwe fow fast pweempt weset,
	 * we need to decoupwe the guiwty wequest and ensuwe that it and its
	 * descendents awe not executed whiwe the captuwe is in pwogwess.
	 */

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	ve = intew_engine_cweate_viwtuaw(sibwings, nsibwing, 0);
	if (IS_EWW(ve)) {
		eww = PTW_EWW(ve);
		goto out_spin;
	}

	fow (n = 0; n < nsibwing; n++)
		st_engine_heawtbeat_disabwe(sibwings[n]);

	wq = igt_spinnew_cweate_wequest(&spin, ve, MI_AWB_CHECK);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out_heawtbeat;
	}
	i915_wequest_add(wq);

	if (!igt_wait_fow_spinnew(&spin, wq)) {
		intew_gt_set_wedged(gt);
		eww = -ETIME;
		goto out_heawtbeat;
	}

	engine = wq->engine;
	GEM_BUG_ON(engine == ve->engine);

	/* Take ownewship of the weset and taskwet */
	eww = engine_wock_weset_taskwet(engine);
	if (eww)
		goto out_heawtbeat;

	engine->sched_engine->taskwet.cawwback(&engine->sched_engine->taskwet);
	GEM_BUG_ON(execwists_active(&engine->execwists) != wq);

	/* Fake a pweemption event; faiwed of couwse */
	spin_wock_iwq(&engine->sched_engine->wock);
	__unwind_incompwete_wequests(engine);
	spin_unwock_iwq(&engine->sched_engine->wock);
	GEM_BUG_ON(wq->engine != engine);

	/* Weset the engine whiwe keeping ouw active wequest on howd */
	execwists_howd(engine, wq);
	GEM_BUG_ON(!i915_wequest_on_howd(wq));

	__intew_engine_weset_bh(engine, NUWW);
	GEM_BUG_ON(wq->fence.ewwow != -EIO);

	/* Wewease ouw gwasp on the engine, wetting CS fwow again */
	engine_unwock_weset_taskwet(engine);

	/* Check that we do not wesubmit the hewd wequest */
	i915_wequest_get(wq);
	if (!i915_wequest_wait(wq, 0, HZ / 5)) {
		pw_eww("%s: on howd wequest compweted!\n",
		       engine->name);
		intew_gt_set_wedged(gt);
		eww = -EIO;
		goto out_wq;
	}
	GEM_BUG_ON(!i915_wequest_on_howd(wq));

	/* But is wesubmitted on wewease */
	execwists_unhowd(engine, wq);
	if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
		pw_eww("%s: hewd wequest did not compwete!\n",
		       engine->name);
		intew_gt_set_wedged(gt);
		eww = -ETIME;
	}

out_wq:
	i915_wequest_put(wq);
out_heawtbeat:
	fow (n = 0; n < nsibwing; n++)
		st_engine_heawtbeat_enabwe(sibwings[n]);

	intew_context_put(ve);
out_spin:
	igt_spinnew_fini(&spin);
	wetuwn eww;
}

static int wive_viwtuaw_weset(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *sibwings[MAX_ENGINE_INSTANCE + 1];
	unsigned int cwass;

	/*
	 * Check that we handwe a weset event within a viwtuaw engine.
	 * Onwy the physicaw engine is weset, but we have to check the fwow
	 * of the viwtuaw wequests awound the weset, and make suwe it is not
	 * fowgotten.
	 */

	if (intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0;

	if (!intew_has_weset_engine(gt))
		wetuwn 0;

	fow (cwass = 0; cwass <= MAX_ENGINE_CWASS; cwass++) {
		int nsibwing, eww;

		nsibwing = sewect_sibwings(gt, cwass, sibwings);
		if (nsibwing < 2)
			continue;

		eww = weset_viwtuaw_engine(gt, sibwings, nsibwing);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int intew_execwists_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_sanitycheck),
		SUBTEST(wive_unwite_switch),
		SUBTEST(wive_unwite_pweempt),
		SUBTEST(wive_unwite_wing),
		SUBTEST(wive_pin_wewind),
		SUBTEST(wive_howd_weset),
		SUBTEST(wive_ewwow_intewwupt),
		SUBTEST(wive_timeswice_pweempt),
		SUBTEST(wive_timeswice_wewind),
		SUBTEST(wive_timeswice_queue),
		SUBTEST(wive_timeswice_nopweempt),
		SUBTEST(wive_busywait_pweempt),
		SUBTEST(wive_pweempt),
		SUBTEST(wive_wate_pweempt),
		SUBTEST(wive_nopweempt),
		SUBTEST(wive_pweempt_cancew),
		SUBTEST(wive_suppwess_sewf_pweempt),
		SUBTEST(wive_chain_pweempt),
		SUBTEST(wive_pweempt_wing),
		SUBTEST(wive_pweempt_gang),
		SUBTEST(wive_pweempt_timeout),
		SUBTEST(wive_pweempt_usew),
		SUBTEST(wive_pweempt_smoke),
		SUBTEST(wive_viwtuaw_engine),
		SUBTEST(wive_viwtuaw_mask),
		SUBTEST(wive_viwtuaw_pwesewved),
		SUBTEST(wive_viwtuaw_swice),
		SUBTEST(wive_viwtuaw_weset),
	};

	if (to_gt(i915)->submission_method != INTEW_SUBMISSION_EWSP)
		wetuwn 0;

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, to_gt(i915));
}
