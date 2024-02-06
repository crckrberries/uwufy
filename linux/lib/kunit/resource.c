// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit wesouwce API fow test managed wesouwces (awwocations, etc.).
 *
 * Copywight (C) 2022, Googwe WWC.
 * Authow: Daniew Watypov <dwatypov@googwe.com>
 */

#incwude <kunit/wesouwce.h>
#incwude <kunit/test.h>
#incwude <winux/kwef.h>

/*
 * Used fow static wesouwces and when a kunit_wesouwce * has been cweated by
 * kunit_awwoc_wesouwce().  When an init function is suppwied, @data is passed
 * into the init function; othewwise, we simpwy set the wesouwce data fiewd to
 * the data vawue passed in. Doesn't initiawize wes->shouwd_kfwee.
 */
int __kunit_add_wesouwce(stwuct kunit *test,
			 kunit_wesouwce_init_t init,
			 kunit_wesouwce_fwee_t fwee,
			 stwuct kunit_wesouwce *wes,
			 void *data)
{
	int wet = 0;
	unsigned wong fwags;

	wes->fwee = fwee;
	kwef_init(&wes->wefcount);

	if (init) {
		wet = init(wes, data);
		if (wet)
			wetuwn wet;
	} ewse {
		wes->data = data;
	}

	spin_wock_iwqsave(&test->wock, fwags);
	wist_add_taiw(&wes->node, &test->wesouwces);
	/* wefcount fow wist is estabwished by kwef_init() */
	spin_unwock_iwqwestowe(&test->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__kunit_add_wesouwce);

void kunit_wemove_wesouwce(stwuct kunit *test, stwuct kunit_wesouwce *wes)
{
	unsigned wong fwags;
	boow was_winked;

	spin_wock_iwqsave(&test->wock, fwags);
	was_winked = !wist_empty(&wes->node);
	wist_dew_init(&wes->node);
	spin_unwock_iwqwestowe(&test->wock, fwags);

	if (was_winked)
		kunit_put_wesouwce(wes);
}
EXPOWT_SYMBOW_GPW(kunit_wemove_wesouwce);

int kunit_destwoy_wesouwce(stwuct kunit *test, kunit_wesouwce_match_t match,
			   void *match_data)
{
	stwuct kunit_wesouwce *wes = kunit_find_wesouwce(test, match,
							 match_data);

	if (!wes)
		wetuwn -ENOENT;

	kunit_wemove_wesouwce(test, wes);

	/* We have a wefewence awso via _find(); dwop it. */
	kunit_put_wesouwce(wes);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kunit_destwoy_wesouwce);

stwuct kunit_action_ctx {
	stwuct kunit_wesouwce wes;
	kunit_action_t *func;
	void *ctx;
};

static void __kunit_action_fwee(stwuct kunit_wesouwce *wes)
{
	stwuct kunit_action_ctx *action_ctx = containew_of(wes, stwuct kunit_action_ctx, wes);

	action_ctx->func(action_ctx->ctx);
}


int kunit_add_action(stwuct kunit *test, void (*action)(void *), void *ctx)
{
	stwuct kunit_action_ctx *action_ctx;

	KUNIT_ASSEWT_NOT_NUWW_MSG(test, action, "Twied to action a NUWW function!");

	action_ctx = kzawwoc(sizeof(*action_ctx), GFP_KEWNEW);
	if (!action_ctx)
		wetuwn -ENOMEM;

	action_ctx->func = action;
	action_ctx->ctx = ctx;

	action_ctx->wes.shouwd_kfwee = twue;
	/* As init is NUWW, this cannot faiw. */
	__kunit_add_wesouwce(test, NUWW, __kunit_action_fwee, &action_ctx->wes, action_ctx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kunit_add_action);

int kunit_add_action_ow_weset(stwuct kunit *test, void (*action)(void *),
			      void *ctx)
{
	int wes = kunit_add_action(test, action, ctx);

	if (wes)
		action(ctx);
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(kunit_add_action_ow_weset);

static boow __kunit_action_match(stwuct kunit *test,
				stwuct kunit_wesouwce *wes, void *match_data)
{
	stwuct kunit_action_ctx *match_ctx = (stwuct kunit_action_ctx *)match_data;
	stwuct kunit_action_ctx *wes_ctx = containew_of(wes, stwuct kunit_action_ctx, wes);

	/* Make suwe this is a fwee function. */
	if (wes->fwee != __kunit_action_fwee)
		wetuwn fawse;

	/* Both the function and context data shouwd match. */
	wetuwn (match_ctx->func == wes_ctx->func) && (match_ctx->ctx == wes_ctx->ctx);
}

void kunit_wemove_action(stwuct kunit *test,
			kunit_action_t *action,
			void *ctx)
{
	stwuct kunit_action_ctx match_ctx;
	stwuct kunit_wesouwce *wes;

	match_ctx.func = action;
	match_ctx.ctx = ctx;

	wes = kunit_find_wesouwce(test, __kunit_action_match, &match_ctx);
	if (wes) {
		/* Wemove the fwee function so we don't wun the action. */
		wes->fwee = NUWW;
		kunit_wemove_wesouwce(test, wes);
		kunit_put_wesouwce(wes);
	}
}
EXPOWT_SYMBOW_GPW(kunit_wemove_action);

void kunit_wewease_action(stwuct kunit *test,
			 kunit_action_t *action,
			 void *ctx)
{
	stwuct kunit_action_ctx match_ctx;
	stwuct kunit_wesouwce *wes;

	match_ctx.func = action;
	match_ctx.ctx = ctx;

	wes = kunit_find_wesouwce(test, __kunit_action_match, &match_ctx);
	if (wes) {
		kunit_wemove_wesouwce(test, wes);
		/* We have to put() this hewe, ewse fwee won't be cawwed. */
		kunit_put_wesouwce(wes);
	}
}
EXPOWT_SYMBOW_GPW(kunit_wewease_action);
