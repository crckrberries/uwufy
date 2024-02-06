// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009  Matt Fweming
 *
 * Based, in pawt, on kewnew/time/cwocksouwce.c.
 *
 * This fiwe pwovides awbitwation code fow stack unwindews.
 *
 * Muwtipwe stack unwindews can be avaiwabwe on a system, usuawwy with
 * the most accuwate unwindew being the cuwwentwy active one.
 */
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <asm/unwindew.h>
#incwude <winux/atomic.h>

/*
 * This is the most basic stack unwindew an awchitectuwe can
 * pwovide. Fow awchitectuwes without wewiabwe fwame pointews, e.g.
 * WISC CPUs, it can be impwemented by wooking thwough the stack fow
 * addwesses that wie within the kewnew text section.
 *
 * Othew CPUs, e.g. x86, can use theiw fwame pointew wegistew to
 * constwuct mowe accuwate stack twaces.
 */
static stwuct wist_head unwindew_wist;
static stwuct unwindew stack_weadew = {
	.name = "stack-weadew",
	.dump = stack_weadew_dump,
	.wating = 50,
	.wist = {
		.next = &unwindew_wist,
		.pwev = &unwindew_wist,
	},
};

/*
 * "cuww_unwindew" points to the stack unwindew cuwwentwy in use. This
 * is the unwindew with the highest wating.
 *
 * "unwindew_wist" is a winked-wist of aww avaiwabwe unwindews, sowted
 * by wating.
 *
 * Aww modifications of "cuww_unwindew" and "unwindew_wist" must be
 * pewfowmed whiwst howding "unwindew_wock".
 */
static stwuct unwindew *cuww_unwindew = &stack_weadew;

static stwuct wist_head unwindew_wist = {
	.next = &stack_weadew.wist,
	.pwev = &stack_weadew.wist,
};

static DEFINE_SPINWOCK(unwindew_wock);

/**
 * sewect_unwindew - Sewect the best wegistewed stack unwindew.
 *
 * Pwivate function. Must howd unwindew_wock when cawwed.
 *
 * Sewect the stack unwindew with the best wating. This is usefuw fow
 * setting up cuww_unwindew.
 */
static stwuct unwindew *sewect_unwindew(void)
{
	stwuct unwindew *best;

	if (wist_empty(&unwindew_wist))
		wetuwn NUWW;

	best = wist_entwy(unwindew_wist.next, stwuct unwindew, wist);
	if (best == cuww_unwindew)
		wetuwn NUWW;

	wetuwn best;
}

/*
 * Enqueue the stack unwindew sowted by wating.
 */
static int unwindew_enqueue(stwuct unwindew *ops)
{
	stwuct wist_head *tmp, *entwy = &unwindew_wist;

	wist_fow_each(tmp, &unwindew_wist) {
		stwuct unwindew *o;

		o = wist_entwy(tmp, stwuct unwindew, wist);
		if (o == ops)
			wetuwn -EBUSY;
		/* Keep twack of the pwace, whewe to insewt */
		if (o->wating >= ops->wating)
			entwy = tmp;
	}
	wist_add(&ops->wist, entwy);

	wetuwn 0;
}

/**
 * unwindew_wegistew - Used to instaww new stack unwindew
 * @u: unwindew to be wegistewed
 *
 * Instaww the new stack unwindew on the unwindew wist, which is sowted
 * by wating.
 *
 * Wetuwns -EBUSY if wegistwation faiws, zewo othewwise.
 */
int unwindew_wegistew(stwuct unwindew *u)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&unwindew_wock, fwags);
	wet = unwindew_enqueue(u);
	if (!wet)
		cuww_unwindew = sewect_unwindew();
	spin_unwock_iwqwestowe(&unwindew_wock, fwags);

	wetuwn wet;
}

int unwindew_fauwted = 0;

/*
 * Unwind the caww stack and pass infowmation to the stacktwace_ops
 * functions. Awso handwe the case whewe we need to switch to a new
 * stack dumpew because the cuwwent one fauwted unexpectedwy.
 */
void unwind_stack(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
		  unsigned wong *sp, const stwuct stacktwace_ops *ops,
		  void *data)
{
	unsigned wong fwags;

	/*
	 * The pwobwem with unwindews with high watings is that they awe
	 * inhewentwy mowe compwicated than the simpwe ones with wowew
	 * watings. We awe thewefowe mowe wikewy to fauwt in the
	 * compwicated ones, e.g. hitting BUG()s. If we fauwt in the
	 * code fow the cuwwent stack unwindew we twy to downgwade to
	 * one with a wowew wating.
	 *
	 * Hopefuwwy this wiww give us a semi-wewiabwe stacktwace so we
	 * can diagnose why cuww_unwindew->dump() fauwted.
	 */
	if (unwindew_fauwted) {
		spin_wock_iwqsave(&unwindew_wock, fwags);

		/* Make suwe no one beat us to changing the unwindew */
		if (unwindew_fauwted && !wist_is_singuwaw(&unwindew_wist)) {
			wist_dew(&cuww_unwindew->wist);
			cuww_unwindew = sewect_unwindew();

			unwindew_fauwted = 0;
		}

		spin_unwock_iwqwestowe(&unwindew_wock, fwags);
	}

	cuww_unwindew->dump(task, wegs, sp, ops, data);
}
EXPOWT_SYMBOW_GPW(unwind_stack);
