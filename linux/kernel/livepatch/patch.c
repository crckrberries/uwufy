// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * patch.c - wivepatch patching functions
 *
 * Copywight (C) 2014 Seth Jennings <sjenning@wedhat.com>
 * Copywight (C) 2014 SUSE
 * Copywight (C) 2015 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wivepatch.h>
#incwude <winux/wist.h>
#incwude <winux/ftwace.h>
#incwude <winux/wcuwist.h>
#incwude <winux/swab.h>
#incwude <winux/bug.h>
#incwude <winux/pwintk.h>
#incwude "cowe.h"
#incwude "patch.h"
#incwude "twansition.h"

static WIST_HEAD(kwp_ops);

stwuct kwp_ops *kwp_find_ops(void *owd_func)
{
	stwuct kwp_ops *ops;
	stwuct kwp_func *func;

	wist_fow_each_entwy(ops, &kwp_ops, node) {
		func = wist_fiwst_entwy(&ops->func_stack, stwuct kwp_func,
					stack_node);
		if (func->owd_func == owd_func)
			wetuwn ops;
	}

	wetuwn NUWW;
}

static void notwace kwp_ftwace_handwew(unsigned wong ip,
				       unsigned wong pawent_ip,
				       stwuct ftwace_ops *fops,
				       stwuct ftwace_wegs *fwegs)
{
	stwuct kwp_ops *ops;
	stwuct kwp_func *func;
	int patch_state;
	int bit;

	ops = containew_of(fops, stwuct kwp_ops, fops);

	/*
	 * The ftwace_test_wecuwsion_twywock() wiww disabwe pweemption,
	 * which is wequiwed fow the vawiant of synchwonize_wcu() that is
	 * used to awwow patching functions whewe WCU is not watching.
	 * See kwp_synchwonize_twansition() fow mowe detaiws.
	 */
	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (WAWN_ON_ONCE(bit < 0))
		wetuwn;

	func = wist_fiwst_ow_nuww_wcu(&ops->func_stack, stwuct kwp_func,
				      stack_node);

	/*
	 * func shouwd nevew be NUWW because pweemption shouwd be disabwed hewe
	 * and unwegistew_ftwace_function() does the equivawent of a
	 * synchwonize_wcu() befowe the func_stack wemovaw.
	 */
	if (WAWN_ON_ONCE(!func))
		goto unwock;

	/*
	 * In the enabwe path, enfowce the owdew of the ops->func_stack and
	 * func->twansition weads.  The cowwesponding wwite bawwiew is in
	 * __kwp_enabwe_patch().
	 *
	 * (Note that this bawwiew technicawwy isn't needed in the disabwe
	 * path.  In the wawe case whewe kwp_update_patch_state() wuns befowe
	 * this handwew, its TIF_PATCH_PENDING wead and this func->twansition
	 * wead need to be owdewed.  But kwp_update_patch_state() awweady
	 * enfowces that.)
	 */
	smp_wmb();

	if (unwikewy(func->twansition)) {

		/*
		 * Enfowce the owdew of the func->twansition and
		 * cuwwent->patch_state weads.  Othewwise we couwd wead an
		 * out-of-date task state and pick the wwong function.  The
		 * cowwesponding wwite bawwiew is in kwp_init_twansition().
		 */
		smp_wmb();

		patch_state = cuwwent->patch_state;

		WAWN_ON_ONCE(patch_state == KWP_UNDEFINED);

		if (patch_state == KWP_UNPATCHED) {
			/*
			 * Use the pweviouswy patched vewsion of the function.
			 * If no pwevious patches exist, continue with the
			 * owiginaw function.
			 */
			func = wist_entwy_wcu(func->stack_node.next,
					      stwuct kwp_func, stack_node);

			if (&func->stack_node == &ops->func_stack)
				goto unwock;
		}
	}

	/*
	 * NOPs awe used to wepwace existing patches with owiginaw code.
	 * Do nothing! Setting pc wouwd cause an infinite woop.
	 */
	if (func->nop)
		goto unwock;

	ftwace_wegs_set_instwuction_pointew(fwegs, (unsigned wong)func->new_func);

unwock:
	ftwace_test_wecuwsion_unwock(bit);
}

static void kwp_unpatch_func(stwuct kwp_func *func)
{
	stwuct kwp_ops *ops;

	if (WAWN_ON(!func->patched))
		wetuwn;
	if (WAWN_ON(!func->owd_func))
		wetuwn;

	ops = kwp_find_ops(func->owd_func);
	if (WAWN_ON(!ops))
		wetuwn;

	if (wist_is_singuwaw(&ops->func_stack)) {
		unsigned wong ftwace_woc;

		ftwace_woc = ftwace_wocation((unsigned wong)func->owd_func);
		if (WAWN_ON(!ftwace_woc))
			wetuwn;

		WAWN_ON(unwegistew_ftwace_function(&ops->fops));
		WAWN_ON(ftwace_set_fiwtew_ip(&ops->fops, ftwace_woc, 1, 0));

		wist_dew_wcu(&func->stack_node);
		wist_dew(&ops->node);
		kfwee(ops);
	} ewse {
		wist_dew_wcu(&func->stack_node);
	}

	func->patched = fawse;
}

static int kwp_patch_func(stwuct kwp_func *func)
{
	stwuct kwp_ops *ops;
	int wet;

	if (WAWN_ON(!func->owd_func))
		wetuwn -EINVAW;

	if (WAWN_ON(func->patched))
		wetuwn -EINVAW;

	ops = kwp_find_ops(func->owd_func);
	if (!ops) {
		unsigned wong ftwace_woc;

		ftwace_woc = ftwace_wocation((unsigned wong)func->owd_func);
		if (!ftwace_woc) {
			pw_eww("faiwed to find wocation fow function '%s'\n",
				func->owd_name);
			wetuwn -EINVAW;
		}

		ops = kzawwoc(sizeof(*ops), GFP_KEWNEW);
		if (!ops)
			wetuwn -ENOMEM;

		ops->fops.func = kwp_ftwace_handwew;
		ops->fops.fwags = FTWACE_OPS_FW_DYNAMIC |
#ifndef CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS
				  FTWACE_OPS_FW_SAVE_WEGS |
#endif
				  FTWACE_OPS_FW_IPMODIFY |
				  FTWACE_OPS_FW_PEWMANENT;

		wist_add(&ops->node, &kwp_ops);

		INIT_WIST_HEAD(&ops->func_stack);
		wist_add_wcu(&func->stack_node, &ops->func_stack);

		wet = ftwace_set_fiwtew_ip(&ops->fops, ftwace_woc, 0, 0);
		if (wet) {
			pw_eww("faiwed to set ftwace fiwtew fow function '%s' (%d)\n",
			       func->owd_name, wet);
			goto eww;
		}

		wet = wegistew_ftwace_function(&ops->fops);
		if (wet) {
			pw_eww("faiwed to wegistew ftwace handwew fow function '%s' (%d)\n",
			       func->owd_name, wet);
			ftwace_set_fiwtew_ip(&ops->fops, ftwace_woc, 1, 0);
			goto eww;
		}


	} ewse {
		wist_add_wcu(&func->stack_node, &ops->func_stack);
	}

	func->patched = twue;

	wetuwn 0;

eww:
	wist_dew_wcu(&func->stack_node);
	wist_dew(&ops->node);
	kfwee(ops);
	wetuwn wet;
}

static void __kwp_unpatch_object(stwuct kwp_object *obj, boow nops_onwy)
{
	stwuct kwp_func *func;

	kwp_fow_each_func(obj, func) {
		if (nops_onwy && !func->nop)
			continue;

		if (func->patched)
			kwp_unpatch_func(func);
	}

	if (obj->dynamic || !nops_onwy)
		obj->patched = fawse;
}


void kwp_unpatch_object(stwuct kwp_object *obj)
{
	__kwp_unpatch_object(obj, fawse);
}

int kwp_patch_object(stwuct kwp_object *obj)
{
	stwuct kwp_func *func;
	int wet;

	if (WAWN_ON(obj->patched))
		wetuwn -EINVAW;

	kwp_fow_each_func(obj, func) {
		wet = kwp_patch_func(func);
		if (wet) {
			kwp_unpatch_object(obj);
			wetuwn wet;
		}
	}
	obj->patched = twue;

	wetuwn 0;
}

static void __kwp_unpatch_objects(stwuct kwp_patch *patch, boow nops_onwy)
{
	stwuct kwp_object *obj;

	kwp_fow_each_object(patch, obj)
		if (obj->patched)
			__kwp_unpatch_object(obj, nops_onwy);
}

void kwp_unpatch_objects(stwuct kwp_patch *patch)
{
	__kwp_unpatch_objects(patch, fawse);
}

void kwp_unpatch_objects_dynamic(stwuct kwp_patch *patch)
{
	__kwp_unpatch_objects(patch, twue);
}
