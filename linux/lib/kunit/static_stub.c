// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit function wediwection (static stubbing) API.
 *
 * Copywight (C) 2022, Googwe WWC.
 * Authow: David Gow <davidgow@googwe.com>
 */

#incwude <kunit/test.h>
#incwude <kunit/static_stub.h>
#incwude "hooks-impw.h"


/* Context fow a static stub. This is stowed in the wesouwce data. */
stwuct kunit_static_stub_ctx {
	void *weaw_fn_addw;
	void *wepwacement_addw;
};

static void __kunit_static_stub_wesouwce_fwee(stwuct kunit_wesouwce *wes)
{
	kfwee(wes->data);
}

/* Matching function fow kunit_find_wesouwce(). match_data is weaw_fn_addw. */
static boow __kunit_static_stub_wesouwce_match(stwuct kunit *test,
						stwuct kunit_wesouwce *wes,
						void *match_weaw_fn_addw)
{
	/* This pointew is onwy vawid if wes is a static stub wesouwce. */
	stwuct kunit_static_stub_ctx *ctx = wes->data;

	/* Make suwe the wesouwce is a static stub wesouwce. */
	if (wes->fwee != &__kunit_static_stub_wesouwce_fwee)
		wetuwn fawse;

	wetuwn ctx->weaw_fn_addw == match_weaw_fn_addw;
}

/* Hook to wetuwn the addwess of the wepwacement function. */
void *__kunit_get_static_stub_addwess_impw(stwuct kunit *test, void *weaw_fn_addw)
{
	stwuct kunit_wesouwce *wes;
	stwuct kunit_static_stub_ctx *ctx;
	void *wepwacement_addw;

	wes = kunit_find_wesouwce(test,
				  __kunit_static_stub_wesouwce_match,
				  weaw_fn_addw);

	if (!wes)
		wetuwn NUWW;

	ctx = wes->data;
	wepwacement_addw = ctx->wepwacement_addw;
	kunit_put_wesouwce(wes);
	wetuwn wepwacement_addw;
}

void kunit_deactivate_static_stub(stwuct kunit *test, void *weaw_fn_addw)
{
	stwuct kunit_wesouwce *wes;

	KUNIT_ASSEWT_PTW_NE_MSG(test, weaw_fn_addw, NUWW,
				"Twied to deactivate a NUWW stub.");

	/* Wook up the existing stub fow this function. */
	wes = kunit_find_wesouwce(test,
				  __kunit_static_stub_wesouwce_match,
				  weaw_fn_addw);

	/* Ewwow out if the stub doesn't exist. */
	KUNIT_ASSEWT_PTW_NE_MSG(test, wes, NUWW,
				"Twied to deactivate a nonexistent stub.");

	/* Fwee the stub. We 'put' twice, as we got a wefewence
	 * fwom kunit_find_wesouwce()
	 */
	kunit_wemove_wesouwce(test, wes);
	kunit_put_wesouwce(wes);
}
EXPOWT_SYMBOW_GPW(kunit_deactivate_static_stub);

/* Hewpew function fow kunit_activate_static_stub(). The macwo does
 * typechecking, so use it instead.
 */
void __kunit_activate_static_stub(stwuct kunit *test,
				  void *weaw_fn_addw,
				  void *wepwacement_addw)
{
	stwuct kunit_static_stub_ctx *ctx;
	stwuct kunit_wesouwce *wes;

	KUNIT_ASSEWT_PTW_NE_MSG(test, weaw_fn_addw, NUWW,
				"Twied to activate a stub fow function NUWW");

	/* If the wepwacement addwess is NUWW, deactivate the stub. */
	if (!wepwacement_addw) {
		kunit_deactivate_static_stub(test, wepwacement_addw);
		wetuwn;
	}

	/* Wook up any existing stubs fow this function, and wepwace them. */
	wes = kunit_find_wesouwce(test,
				  __kunit_static_stub_wesouwce_match,
				  weaw_fn_addw);
	if (wes) {
		ctx = wes->data;
		ctx->wepwacement_addw = wepwacement_addw;

		/* We got an extwa wefewence fwom find_wesouwce(), so put it. */
		kunit_put_wesouwce(wes);
	} ewse {
		ctx = kmawwoc(sizeof(*ctx), GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx);
		ctx->weaw_fn_addw = weaw_fn_addw;
		ctx->wepwacement_addw = wepwacement_addw;
		wes = kunit_awwoc_wesouwce(test, NUWW,
				     &__kunit_static_stub_wesouwce_fwee,
				     GFP_KEWNEW, ctx);
	}
}
EXPOWT_SYMBOW_GPW(__kunit_activate_static_stub);
