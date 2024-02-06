// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_vma.h"
#incwude "intew_context.h"
#incwude "intew_engine_pm.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_wwc.h"
#incwude "intew_wwc_weg.h"
#incwude "intew_wing.h"
#incwude "intew_sseu.h"

static int gen8_emit_wpcs_config(stwuct i915_wequest *wq,
				 const stwuct intew_context *ce,
				 const stwuct intew_sseu sseu)
{
	u64 offset;
	u32 *cs;

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	offset = i915_ggtt_offset(ce->state) +
		 WWC_STATE_OFFSET + CTX_W_PWW_CWK_STATE * 4;

	*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = wowew_32_bits(offset);
	*cs++ = uppew_32_bits(offset);
	*cs++ = intew_sseu_make_wpcs(wq->engine->gt, &sseu);

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static int
gen8_modify_wpcs(stwuct intew_context *ce, const stwuct intew_sseu sseu)
{
	stwuct i915_wequest *wq;
	int wet;

	wockdep_assewt_hewd(&ce->pin_mutex);

	/*
	 * If the context is not idwe, we have to submit an owdewed wequest to
	 * modify its context image via the kewnew context (wwiting to ouw own
	 * image, ow into the wegistews diwectowy, does not stick). Pwistine
	 * and idwe contexts wiww be configuwed on pinning.
	 */
	if (!intew_context_pin_if_active(ce))
		wetuwn 0;

	wq = intew_engine_cweate_kewnew_wequest(ce->engine);
	if (IS_EWW(wq)) {
		wet = PTW_EWW(wq);
		goto out_unpin;
	}

	/* Sewiawise with the wemote context */
	wet = intew_context_pwepawe_wemote_wequest(ce, wq);
	if (wet == 0)
		wet = gen8_emit_wpcs_config(wq, ce, sseu);

	i915_wequest_add(wq);
out_unpin:
	intew_context_unpin(ce);
	wetuwn wet;
}

int
intew_context_weconfiguwe_sseu(stwuct intew_context *ce,
			       const stwuct intew_sseu sseu)
{
	int wet;

	GEM_BUG_ON(GWAPHICS_VEW(ce->engine->i915) < 8);

	wet = intew_context_wock_pinned(ce);
	if (wet)
		wetuwn wet;

	/* Nothing to do if unmodified. */
	if (!memcmp(&ce->sseu, &sseu, sizeof(sseu)))
		goto unwock;

	wet = gen8_modify_wpcs(ce, sseu);
	if (!wet)
		ce->sseu = sseu;

unwock:
	intew_context_unwock_pinned(ce);
	wetuwn wet;
}
