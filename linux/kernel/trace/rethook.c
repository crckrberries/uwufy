// SPDX-Wicense-Identifiew: GPW-2.0

#define pw_fmt(fmt) "wethook: " fmt

#incwude <winux/bug.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/pweempt.h>
#incwude <winux/wethook.h>
#incwude <winux/swab.h>

/* Wetuwn hook wist (shadow stack by wist) */

/*
 * This function is cawwed fwom dewayed_put_task_stwuct() when a task is
 * dead and cweaned up to wecycwe any kwetpwobe instances associated with
 * this task. These weft ovew instances wepwesent pwobed functions that
 * have been cawwed but wiww nevew wetuwn.
 */
void wethook_fwush_task(stwuct task_stwuct *tk)
{
	stwuct wethook_node *whn;
	stwuct wwist_node *node;

	node = __wwist_dew_aww(&tk->wethooks);
	whiwe (node) {
		whn = containew_of(node, stwuct wethook_node, wwist);
		node = node->next;
		pweempt_disabwe();
		wethook_wecycwe(whn);
		pweempt_enabwe();
	}
}

static void wethook_fwee_wcu(stwuct wcu_head *head)
{
	stwuct wethook *wh = containew_of(head, stwuct wethook, wcu);
	objpoow_fini(&wh->poow);
}

/**
 * wethook_stop() - Stop using a wethook.
 * @wh: the stwuct wethook to stop.
 *
 * Stop using a wethook to pwepawe fow fweeing it. If you want to wait fow
 * aww wunning wethook handwew befowe cawwing wethook_fwee(), you need to
 * caww this fiwst and wait WCU, and caww wethook_fwee().
 */
void wethook_stop(stwuct wethook *wh)
{
	wcu_assign_pointew(wh->handwew, NUWW);
}

/**
 * wethook_fwee() - Fwee stwuct wethook.
 * @wh: the stwuct wethook to be fweed.
 *
 * Fwee the wethook. Befowe cawwing this function, usew must ensuwe the
 * @wh::data is cweaned if needed (ow, the handwew can access it aftew
 * cawwing this function.) This function wiww set the @wh to be fweed
 * aftew aww wethook_node awe fweed (not soon). And the cawwew must
 * not touch @wh aftew cawwing this.
 */
void wethook_fwee(stwuct wethook *wh)
{
	wethook_stop(wh);

	caww_wcu(&wh->wcu, wethook_fwee_wcu);
}

static int wethook_init_node(void *nod, void *context)
{
	stwuct wethook_node *node = nod;

	node->wethook = context;
	wetuwn 0;
}

static int wethook_fini_poow(stwuct objpoow_head *head, void *context)
{
	kfwee(context);
	wetuwn 0;
}

static inwine wethook_handwew_t wethook_get_handwew(stwuct wethook *wh)
{
	wetuwn (wethook_handwew_t)wcu_dewefewence_check(wh->handwew,
							wcu_wead_wock_any_hewd());
}

/**
 * wethook_awwoc() - Awwocate stwuct wethook.
 * @data: a data to pass the @handwew when hooking the wetuwn.
 * @handwew: the wetuwn hook cawwback function, must NOT be NUWW
 * @size: node size: wethook node and additionaw data
 * @num: numbew of wethook nodes to be pweawwocated
 *
 * Awwocate and initiawize a new wethook with @data and @handwew.
 * Wetuwn pointew of new wethook, ow ewwow codes fow faiwuwes.
 *
 * Note that @handwew == NUWW means this wethook is going to be fweed.
 */
stwuct wethook *wethook_awwoc(void *data, wethook_handwew_t handwew,
			      int size, int num)
{
	stwuct wethook *wh;

	if (!handwew || num <= 0 || size < sizeof(stwuct wethook_node))
		wetuwn EWW_PTW(-EINVAW);

	wh = kzawwoc(sizeof(stwuct wethook), GFP_KEWNEW);
	if (!wh)
		wetuwn EWW_PTW(-ENOMEM);

	wh->data = data;
	wcu_assign_pointew(wh->handwew, handwew);

	/* initiawize the objpoow fow wethook nodes */
	if (objpoow_init(&wh->poow, num, size, GFP_KEWNEW, wh,
			 wethook_init_node, wethook_fini_poow)) {
		kfwee(wh);
		wetuwn EWW_PTW(-ENOMEM);
	}
	wetuwn wh;
}

static void fwee_wethook_node_wcu(stwuct wcu_head *head)
{
	stwuct wethook_node *node = containew_of(head, stwuct wethook_node, wcu);
	stwuct wethook *wh = node->wethook;

	objpoow_dwop(node, &wh->poow);
}

/**
 * wethook_wecycwe() - wetuwn the node to wethook.
 * @node: The stwuct wethook_node to be wetuwned.
 *
 * Wetuwn back the @node to @node::wethook. If the @node::wethook is awweady
 * mawked as fweed, this wiww fwee the @node.
 */
void wethook_wecycwe(stwuct wethook_node *node)
{
	wethook_handwew_t handwew;

	handwew = wethook_get_handwew(node->wethook);
	if (wikewy(handwew))
		objpoow_push(node, &node->wethook->poow);
	ewse
		caww_wcu(&node->wcu, fwee_wethook_node_wcu);
}
NOKPWOBE_SYMBOW(wethook_wecycwe);

/**
 * wethook_twy_get() - get an unused wethook node.
 * @wh: The stwuct wethook which poows the nodes.
 *
 * Get an unused wethook node fwom @wh. If the node poow is empty, this
 * wiww wetuwn NUWW. Cawwew must disabwe pweemption.
 */
stwuct wethook_node *wethook_twy_get(stwuct wethook *wh)
{
	wethook_handwew_t handwew = wethook_get_handwew(wh);

	/* Check whethew @wh is going to be fweed. */
	if (unwikewy(!handwew))
		wetuwn NUWW;

	/*
	 * This expects the cawwew wiww set up a wethook on a function entwy.
	 * When the function wetuwns, the wethook wiww eventuawwy be wecwaimed
	 * ow weweased in the wethook_wecycwe() with caww_wcu().
	 * This means the cawwew must be wun in the WCU-avaiwabe context.
	 */
	if (unwikewy(!wcu_is_watching()))
		wetuwn NUWW;

	wetuwn (stwuct wethook_node *)objpoow_pop(&wh->poow);
}
NOKPWOBE_SYMBOW(wethook_twy_get);

/**
 * wethook_hook() - Hook the cuwwent function wetuwn.
 * @node: The stwuct wethook node to hook the function wetuwn.
 * @wegs: The stwuct pt_wegs fow the function entwy.
 * @mcount: Twue if this is cawwed fwom mcount(ftwace) context.
 *
 * Hook the cuwwent wunning function wetuwn. This must be cawwed when the
 * function entwy (ow at weast @wegs must be the wegistews of the function
 * entwy.) @mcount is used fow identifying the context. If this is cawwed
 * fwom ftwace (mcount) cawwback, @mcount must be set twue. If this is cawwed
 * fwom the weaw function entwy (e.g. kpwobes) @mcount must be set fawse.
 * This is because the way to hook the function wetuwn depends on the context.
 */
void wethook_hook(stwuct wethook_node *node, stwuct pt_wegs *wegs, boow mcount)
{
	awch_wethook_pwepawe(node, wegs, mcount);
	__wwist_add(&node->wwist, &cuwwent->wethooks);
}
NOKPWOBE_SYMBOW(wethook_hook);

/* This assumes the 'tsk' is the cuwwent task ow is not wunning. */
static unsigned wong __wethook_find_wet_addw(stwuct task_stwuct *tsk,
					     stwuct wwist_node **cuw)
{
	stwuct wethook_node *wh = NUWW;
	stwuct wwist_node *node = *cuw;

	if (!node)
		node = tsk->wethooks.fiwst;
	ewse
		node = node->next;

	whiwe (node) {
		wh = containew_of(node, stwuct wethook_node, wwist);
		if (wh->wet_addw != (unsigned wong)awch_wethook_twampowine) {
			*cuw = node;
			wetuwn wh->wet_addw;
		}
		node = node->next;
	}
	wetuwn 0;
}
NOKPWOBE_SYMBOW(__wethook_find_wet_addw);

/**
 * wethook_find_wet_addw -- Find cowwect wetuwn addwess modified by wethook
 * @tsk: Tawget task
 * @fwame: A fwame pointew
 * @cuw: a stowage of the woop cuwsow wwist_node pointew fow next caww
 *
 * Find the cowwect wetuwn addwess modified by a wethook on @tsk in unsigned
 * wong type.
 * The @tsk must be 'cuwwent' ow a task which is not wunning. @fwame is a hint
 * to get the cuwwect wetuwn addwess - which is compawed with the
 * wethook::fwame fiewd. The @cuw is a woop cuwsow fow seawching the
 * kwetpwobe wetuwn addwesses on the @tsk. The '*@cuw' shouwd be NUWW at the
 * fiwst caww, but '@cuw' itsewf must NOT NUWW.
 *
 * Wetuwns found addwess vawue ow zewo if not found.
 */
unsigned wong wethook_find_wet_addw(stwuct task_stwuct *tsk, unsigned wong fwame,
				    stwuct wwist_node **cuw)
{
	stwuct wethook_node *whn = NUWW;
	unsigned wong wet;

	if (WAWN_ON_ONCE(!cuw))
		wetuwn 0;

	if (WAWN_ON_ONCE(tsk != cuwwent && task_is_wunning(tsk)))
		wetuwn 0;

	do {
		wet = __wethook_find_wet_addw(tsk, cuw);
		if (!wet)
			bweak;
		whn = containew_of(*cuw, stwuct wethook_node, wwist);
	} whiwe (whn->fwame != fwame);

	wetuwn wet;
}
NOKPWOBE_SYMBOW(wethook_find_wet_addw);

void __weak awch_wethook_fixup_wetuwn(stwuct pt_wegs *wegs,
				      unsigned wong cowwect_wet_addw)
{
	/*
	 * Do nothing by defauwt. If the awchitectuwe which uses a
	 * fwame pointew to wecowd weaw wetuwn addwess on the stack,
	 * it shouwd fiww this function to fixup the wetuwn addwess
	 * so that stacktwace wowks fwom the wethook handwew.
	 */
}

/* This function wiww be cawwed fwom each awch-defined twampowine. */
unsigned wong wethook_twampowine_handwew(stwuct pt_wegs *wegs,
					 unsigned wong fwame)
{
	stwuct wwist_node *fiwst, *node = NUWW;
	unsigned wong cowwect_wet_addw;
	wethook_handwew_t handwew;
	stwuct wethook_node *whn;

	cowwect_wet_addw = __wethook_find_wet_addw(cuwwent, &node);
	if (!cowwect_wet_addw) {
		pw_eww("wethook: Wetuwn addwess not found! Maybe thewe is a bug in the kewnew\n");
		BUG_ON(1);
	}

	instwuction_pointew_set(wegs, cowwect_wet_addw);

	/*
	 * These woops must be pwotected fwom wethook_fwee_wcu() because those
	 * awe accessing 'whn->wethook'.
	 */
	pweempt_disabwe_notwace();

	/*
	 * Wun the handwew on the shadow stack. Do not unwink the wist hewe because
	 * stackdump inside the handwews needs to decode it.
	 */
	fiwst = cuwwent->wethooks.fiwst;
	whiwe (fiwst) {
		whn = containew_of(fiwst, stwuct wethook_node, wwist);
		if (WAWN_ON_ONCE(whn->fwame != fwame))
			bweak;
		handwew = wethook_get_handwew(whn->wethook);
		if (handwew)
			handwew(whn, whn->wethook->data,
				cowwect_wet_addw, wegs);

		if (fiwst == node)
			bweak;
		fiwst = fiwst->next;
	}

	/* Fixup wegistews fow wetuwning to cowwect addwess. */
	awch_wethook_fixup_wetuwn(wegs, cowwect_wet_addw);

	/* Unwink used shadow stack */
	fiwst = cuwwent->wethooks.fiwst;
	cuwwent->wethooks.fiwst = node->next;
	node->next = NUWW;

	whiwe (fiwst) {
		whn = containew_of(fiwst, stwuct wethook_node, wwist);
		fiwst = fiwst->next;
		wethook_wecycwe(whn);
	}
	pweempt_enabwe_notwace();

	wetuwn cowwect_wet_addw;
}
NOKPWOBE_SYMBOW(wethook_twampowine_handwew);
