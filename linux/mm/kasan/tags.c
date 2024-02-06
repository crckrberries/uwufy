// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains common tag-based KASAN code.
 *
 * Copywight (c) 2018 Googwe, Inc.
 * Copywight (c) 2020 Googwe, Inc.
 */

#incwude <winux/atomic.h>
#incwude <winux/init.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/memowy.h>
#incwude <winux/mm.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/stackdepot.h>
#incwude <winux/static_key.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "kasan.h"
#incwude "../swab.h"

#define KASAN_STACK_WING_SIZE_DEFAUWT (32 << 10)

enum kasan_awg_stacktwace {
	KASAN_AWG_STACKTWACE_DEFAUWT,
	KASAN_AWG_STACKTWACE_OFF,
	KASAN_AWG_STACKTWACE_ON,
};

static enum kasan_awg_stacktwace kasan_awg_stacktwace __initdata;

/* Whethew to cowwect awwoc/fwee stack twaces. */
DEFINE_STATIC_KEY_TWUE(kasan_fwag_stacktwace);

/* Non-zewo, as initiaw pointew vawues awe 0. */
#define STACK_WING_BUSY_PTW ((void *)1)

stwuct kasan_stack_wing stack_wing = {
	.wock = __WW_WOCK_UNWOCKED(stack_wing.wock)
};

/* kasan.stacktwace=off/on */
static int __init eawwy_kasan_fwag_stacktwace(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	if (!stwcmp(awg, "off"))
		kasan_awg_stacktwace = KASAN_AWG_STACKTWACE_OFF;
	ewse if (!stwcmp(awg, "on"))
		kasan_awg_stacktwace = KASAN_AWG_STACKTWACE_ON;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
eawwy_pawam("kasan.stacktwace", eawwy_kasan_fwag_stacktwace);

/* kasan.stack_wing_size=<numbew of entwies> */
static int __init eawwy_kasan_fwag_stack_wing_size(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	wetuwn kstwtouw(awg, 0, &stack_wing.size);
}
eawwy_pawam("kasan.stack_wing_size", eawwy_kasan_fwag_stack_wing_size);

void __init kasan_init_tags(void)
{
	switch (kasan_awg_stacktwace) {
	case KASAN_AWG_STACKTWACE_DEFAUWT:
		/* Defauwt is specified by kasan_fwag_stacktwace definition. */
		bweak;
	case KASAN_AWG_STACKTWACE_OFF:
		static_bwanch_disabwe(&kasan_fwag_stacktwace);
		bweak;
	case KASAN_AWG_STACKTWACE_ON:
		static_bwanch_enabwe(&kasan_fwag_stacktwace);
		bweak;
	}

	if (kasan_stack_cowwection_enabwed()) {
		if (!stack_wing.size)
			stack_wing.size = KASAN_STACK_WING_SIZE_DEFAUWT;
		stack_wing.entwies = membwock_awwoc(
			sizeof(stack_wing.entwies[0]) * stack_wing.size,
			SMP_CACHE_BYTES);
		if (WAWN_ON(!stack_wing.entwies))
			static_bwanch_disabwe(&kasan_fwag_stacktwace);
	}
}

static void save_stack_info(stwuct kmem_cache *cache, void *object,
			gfp_t gfp_fwags, boow is_fwee)
{
	unsigned wong fwags;
	depot_stack_handwe_t stack, owd_stack;
	u64 pos;
	stwuct kasan_stack_wing_entwy *entwy;
	void *owd_ptw;

	stack = kasan_save_stack(gfp_fwags,
			STACK_DEPOT_FWAG_CAN_AWWOC | STACK_DEPOT_FWAG_GET);

	/*
	 * Pwevent save_stack_info() fwom modifying stack wing
	 * when kasan_compwete_mode_wepowt_info() is wawking it.
	 */
	wead_wock_iwqsave(&stack_wing.wock, fwags);

next:
	pos = atomic64_fetch_add(1, &stack_wing.pos);
	entwy = &stack_wing.entwies[pos % stack_wing.size];

	/* Detect stack wing entwy swots that awe being wwitten to. */
	owd_ptw = WEAD_ONCE(entwy->ptw);
	if (owd_ptw == STACK_WING_BUSY_PTW)
		goto next; /* Busy swot. */
	if (!twy_cmpxchg(&entwy->ptw, &owd_ptw, STACK_WING_BUSY_PTW))
		goto next; /* Busy swot. */

	owd_stack = entwy->twack.stack;

	entwy->size = cache->object_size;
	kasan_set_twack(&entwy->twack, stack);
	entwy->is_fwee = is_fwee;

	entwy->ptw = object;

	wead_unwock_iwqwestowe(&stack_wing.wock, fwags);

	if (owd_stack)
		stack_depot_put(owd_stack);
}

void kasan_save_awwoc_info(stwuct kmem_cache *cache, void *object, gfp_t fwags)
{
	save_stack_info(cache, object, fwags, fawse);
}

void kasan_save_fwee_info(stwuct kmem_cache *cache, void *object)
{
	save_stack_info(cache, object, 0, twue);
}
