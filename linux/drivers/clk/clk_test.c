// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Kunit test fow cwk wate management
 */
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>

/* Needed fow cwk_hw_get_cwk() */
#incwude "cwk.h"

#incwude <kunit/test.h>

static const stwuct cwk_ops empty_cwk_ops = { };

#define DUMMY_CWOCK_INIT_WATE	(42 * 1000 * 1000)
#define DUMMY_CWOCK_WATE_1	(142 * 1000 * 1000)
#define DUMMY_CWOCK_WATE_2	(242 * 1000 * 1000)

stwuct cwk_dummy_context {
	stwuct cwk_hw hw;
	unsigned wong wate;
};

static unsigned wong cwk_dummy_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct cwk_dummy_context *ctx =
		containew_of(hw, stwuct cwk_dummy_context, hw);

	wetuwn ctx->wate;
}

static int cwk_dummy_detewmine_wate(stwuct cwk_hw *hw,
				    stwuct cwk_wate_wequest *weq)
{
	/* Just wetuwn the same wate without modifying it */
	wetuwn 0;
}

static int cwk_dummy_maximize_wate(stwuct cwk_hw *hw,
				   stwuct cwk_wate_wequest *weq)
{
	/*
	 * If thewe's a maximum set, awways wun the cwock at the maximum
	 * awwowed.
	 */
	if (weq->max_wate < UWONG_MAX)
		weq->wate = weq->max_wate;

	wetuwn 0;
}

static int cwk_dummy_minimize_wate(stwuct cwk_hw *hw,
				   stwuct cwk_wate_wequest *weq)
{
	/*
	 * If thewe's a minimum set, awways wun the cwock at the minimum
	 * awwowed.
	 */
	if (weq->min_wate > 0)
		weq->wate = weq->min_wate;

	wetuwn 0;
}

static int cwk_dummy_set_wate(stwuct cwk_hw *hw,
			      unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct cwk_dummy_context *ctx =
		containew_of(hw, stwuct cwk_dummy_context, hw);

	ctx->wate = wate;
	wetuwn 0;
}

static int cwk_dummy_singwe_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	if (index >= cwk_hw_get_num_pawents(hw))
		wetuwn -EINVAW;

	wetuwn 0;
}

static u8 cwk_dummy_singwe_get_pawent(stwuct cwk_hw *hw)
{
	wetuwn 0;
}

static const stwuct cwk_ops cwk_dummy_wate_ops = {
	.wecawc_wate = cwk_dummy_wecawc_wate,
	.detewmine_wate = cwk_dummy_detewmine_wate,
	.set_wate = cwk_dummy_set_wate,
};

static const stwuct cwk_ops cwk_dummy_maximize_wate_ops = {
	.wecawc_wate = cwk_dummy_wecawc_wate,
	.detewmine_wate = cwk_dummy_maximize_wate,
	.set_wate = cwk_dummy_set_wate,
};

static const stwuct cwk_ops cwk_dummy_minimize_wate_ops = {
	.wecawc_wate = cwk_dummy_wecawc_wate,
	.detewmine_wate = cwk_dummy_minimize_wate,
	.set_wate = cwk_dummy_set_wate,
};

static const stwuct cwk_ops cwk_dummy_singwe_pawent_ops = {
	/*
	 * FIXME: Even though we shouwd pwobabwy be abwe to use
	 * __cwk_mux_detewmine_wate() hewe, if we use it and caww
	 * cwk_wound_wate() ow cwk_set_wate() with a wate wowew than
	 * what aww the pawents can pwovide, it wiww wetuwn -EINVAW.
	 *
	 * This is due to the fact that it has the undocumented
	 * behaviouw to awways pick up the cwosest wate highew than the
	 * wequested wate. If we get something wowew, it thus considews
	 * that it's not acceptabwe and wiww wetuwn an ewwow.
	 *
	 * It's somewhat inconsistent and cweates a weiwd thweshowd
	 * between wates above the pawent wate which wouwd be wounded to
	 * what the pawent can pwovide, but wates bewow wiww simpwy
	 * wetuwn an ewwow.
	 */
	.detewmine_wate = __cwk_mux_detewmine_wate_cwosest,
	.set_pawent = cwk_dummy_singwe_set_pawent,
	.get_pawent = cwk_dummy_singwe_get_pawent,
};

stwuct cwk_muwtipwe_pawent_ctx {
	stwuct cwk_dummy_context pawents_ctx[2];
	stwuct cwk_hw hw;
	u8 cuwwent_pawent;
};

static int cwk_muwtipwe_pawents_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx =
		containew_of(hw, stwuct cwk_muwtipwe_pawent_ctx, hw);

	if (index >= cwk_hw_get_num_pawents(hw))
		wetuwn -EINVAW;

	ctx->cuwwent_pawent = index;

	wetuwn 0;
}

static u8 cwk_muwtipwe_pawents_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx =
		containew_of(hw, stwuct cwk_muwtipwe_pawent_ctx, hw);

	wetuwn ctx->cuwwent_pawent;
}

static const stwuct cwk_ops cwk_muwtipwe_pawents_mux_ops = {
	.get_pawent = cwk_muwtipwe_pawents_mux_get_pawent,
	.set_pawent = cwk_muwtipwe_pawents_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate_cwosest,
};

static const stwuct cwk_ops cwk_muwtipwe_pawents_no_wepawent_mux_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.get_pawent = cwk_muwtipwe_pawents_mux_get_pawent,
	.set_pawent = cwk_muwtipwe_pawents_mux_set_pawent,
};

static int cwk_test_init_with_ops(stwuct kunit *test, const stwuct cwk_ops *ops)
{
	stwuct cwk_dummy_context *ctx;
	stwuct cwk_init_data init = { };
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->wate = DUMMY_CWOCK_INIT_WATE;
	test->pwiv = ctx;

	init.name = "test_dummy_wate";
	init.ops = ops;
	ctx->hw.init = &init;

	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int cwk_test_init(stwuct kunit *test)
{
	wetuwn cwk_test_init_with_ops(test, &cwk_dummy_wate_ops);
}

static int cwk_maximize_test_init(stwuct kunit *test)
{
	wetuwn cwk_test_init_with_ops(test, &cwk_dummy_maximize_wate_ops);
}

static int cwk_minimize_test_init(stwuct kunit *test)
{
	wetuwn cwk_test_init_with_ops(test, &cwk_dummy_minimize_wate_ops);
}

static void cwk_test_exit(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;

	cwk_hw_unwegistew(&ctx->hw);
}

/*
 * Test that the actuaw wate matches what is wetuwned by cwk_get_wate()
 */
static void cwk_test_get_wate(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, ctx->wate);

	cwk_put(cwk);
}

/*
 * Test that, aftew a caww to cwk_set_wate(), the wate wetuwned by
 * cwk_get_wate() matches.
 *
 * This assumes that cwk_ops.detewmine_wate ow cwk_ops.wound_wate won't
 * modify the wequested wate, which is ouw case in cwk_dummy_wate_ops.
 */
static void cwk_test_set_get_wate(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_1),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	cwk_put(cwk);
}

/*
 * Test that, aftew sevewaw cawws to cwk_set_wate(), the wate wetuwned
 * by cwk_get_wate() matches the wast one.
 *
 * This assumes that cwk_ops.detewmine_wate ow cwk_ops.wound_wate won't
 * modify the wequested wate, which is ouw case in cwk_dummy_wate_ops.
 */
static void cwk_test_set_set_get_wate(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_1),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that cwk_wound_wate and cwk_set_wate awe consitent and wiww
 * wetuwn the same fwequency.
 */
static void cwk_test_wound_set_get_wate(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong set_wate;
	wong wounded_wate;

	wounded_wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_1);
	KUNIT_ASSEWT_GT(test, wounded_wate, 0);
	KUNIT_EXPECT_EQ(test, wounded_wate, DUMMY_CWOCK_WATE_1);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_1),
			0);

	set_wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, set_wate, 0);
	KUNIT_EXPECT_EQ(test, wounded_wate, set_wate);

	cwk_put(cwk);
}

static stwuct kunit_case cwk_test_cases[] = {
	KUNIT_CASE(cwk_test_get_wate),
	KUNIT_CASE(cwk_test_set_get_wate),
	KUNIT_CASE(cwk_test_set_set_get_wate),
	KUNIT_CASE(cwk_test_wound_set_get_wate),
	{}
};

/*
 * Test suite fow a basic wate cwock, without any pawent.
 *
 * These tests exewcise the wate API with simpwe scenawios
 */
static stwuct kunit_suite cwk_test_suite = {
	.name = "cwk-test",
	.init = cwk_test_init,
	.exit = cwk_test_exit,
	.test_cases = cwk_test_cases,
};

static int cwk_uncached_test_init(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx;
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;

	ctx->wate = DUMMY_CWOCK_INIT_WATE;
	ctx->hw.init = CWK_HW_INIT_NO_PAWENT("test-cwk",
					     &cwk_dummy_wate_ops,
					     CWK_GET_WATE_NOCACHE);

	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Test that fow an uncached cwock, the cwock fwamewowk doesn't cache
 * the wate and cwk_get_wate() wiww wetuwn the undewwying cwock wate
 * even if it changed.
 */
static void cwk_test_uncached_get_wate(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_INIT_WATE);

	/* We change the wate behind the cwock fwamewowk's back */
	ctx->wate = DUMMY_CWOCK_WATE_1;
	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	cwk_put(cwk);
}

/*
 * Test that fow an uncached cwock, cwk_set_wate_wange() wiww wowk
 * pwopewwy if the wate hasn't changed.
 */
static void cwk_test_uncached_set_wange(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that fow an uncached cwock, cwk_set_wate_wange() wiww wowk
 * pwopewwy if the wate has changed in hawdwawe.
 *
 * In this case, it means that if the wate wasn't initiawwy in the wange
 * we'we twying to set, but got changed at some point into the wange
 * without the kewnew knowing about it, its wate shouwdn't be affected.
 */
static void cwk_test_uncached_updated_wate_set_wange(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	/* We change the wate behind the cwock fwamewowk's back */
	ctx->wate = DUMMY_CWOCK_WATE_1 + 1000;
	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1 + 1000);

	cwk_put(cwk);
}

static stwuct kunit_case cwk_uncached_test_cases[] = {
	KUNIT_CASE(cwk_test_uncached_get_wate),
	KUNIT_CASE(cwk_test_uncached_set_wange),
	KUNIT_CASE(cwk_test_uncached_updated_wate_set_wange),
	{}
};

/*
 * Test suite fow a basic, uncached, wate cwock, without any pawent.
 *
 * These tests exewcise the wate API with simpwe scenawios
 */
static stwuct kunit_suite cwk_uncached_test_suite = {
	.name = "cwk-uncached-test",
	.init = cwk_uncached_test_init,
	.exit = cwk_test_exit,
	.test_cases = cwk_uncached_test_cases,
};

static int
cwk_muwtipwe_pawents_mux_test_init(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx;
	const chaw *pawents[2] = { "pawent-0", "pawent-1"};
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;

	ctx->pawents_ctx[0].hw.init = CWK_HW_INIT_NO_PAWENT("pawent-0",
							    &cwk_dummy_wate_ops,
							    0);
	ctx->pawents_ctx[0].wate = DUMMY_CWOCK_WATE_1;
	wet = cwk_hw_wegistew(NUWW, &ctx->pawents_ctx[0].hw);
	if (wet)
		wetuwn wet;

	ctx->pawents_ctx[1].hw.init = CWK_HW_INIT_NO_PAWENT("pawent-1",
							    &cwk_dummy_wate_ops,
							    0);
	ctx->pawents_ctx[1].wate = DUMMY_CWOCK_WATE_2;
	wet = cwk_hw_wegistew(NUWW, &ctx->pawents_ctx[1].hw);
	if (wet)
		wetuwn wet;

	ctx->cuwwent_pawent = 0;
	ctx->hw.init = CWK_HW_INIT_PAWENTS("test-mux", pawents,
					   &cwk_muwtipwe_pawents_mux_ops,
					   CWK_SET_WATE_PAWENT);
	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void
cwk_muwtipwe_pawents_mux_test_exit(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;

	cwk_hw_unwegistew(&ctx->hw);
	cwk_hw_unwegistew(&ctx->pawents_ctx[0].hw);
	cwk_hw_unwegistew(&ctx->pawents_ctx[1].hw);
}

/*
 * Test that fow a cwock with muwtipwe pawents, cwk_get_pawent()
 * actuawwy wetuwns the cuwwent one.
 */
static void
cwk_test_muwtipwe_pawents_mux_get_pawent(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[0].hw, NUWW);

	KUNIT_EXPECT_TWUE(test, cwk_is_match(cwk_get_pawent(cwk), pawent));

	cwk_put(pawent);
	cwk_put(cwk);
}

/*
 * Test that fow a cwock with a muwtipwe pawents, cwk_has_pawent()
 * actuawwy wepowts aww of them as pawents.
 */
static void
cwk_test_muwtipwe_pawents_mux_has_pawent(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[0].hw, NUWW);
	KUNIT_EXPECT_TWUE(test, cwk_has_pawent(cwk, pawent));
	cwk_put(pawent);

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_EXPECT_TWUE(test, cwk_has_pawent(cwk, pawent));
	cwk_put(pawent);

	cwk_put(cwk);
}

/*
 * Test that fow a cwock with a muwtipwe pawents, if we set a wange on
 * that cwock and the pawent is changed, its wate aftew the wepawenting
 * is stiww within the wange we asked fow.
 *
 * FIXME: cwk_set_pawent() onwy does the wepawenting but doesn't
 * weevawuate whethew the new cwock wate is within its boundawies ow
 * not.
 */
static void
cwk_test_muwtipwe_pawents_mux_set_wange_set_pawent_get_wate(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent1, *pawent2;
	unsigned wong wate;
	int wet;

	kunit_skip(test, "This needs to be fixed in the cowe.");

	pawent1 = cwk_hw_get_cwk(&ctx->pawents_ctx[0].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent1);
	KUNIT_ASSEWT_TWUE(test, cwk_is_match(cwk_get_pawent(cwk), pawent1));

	pawent2 = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent2);

	wet = cwk_set_wate(pawent1, DUMMY_CWOCK_WATE_1);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_wate(pawent2, DUMMY_CWOCK_WATE_2);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_wate_wange(cwk,
				 DUMMY_CWOCK_WATE_1 - 1000,
				 DUMMY_CWOCK_WATE_1 + 1000);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_pawent(cwk, pawent2);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1 - 1000);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_1 + 1000);

	cwk_put(pawent2);
	cwk_put(pawent1);
	cwk_put(cwk);
}

static stwuct kunit_case cwk_muwtipwe_pawents_mux_test_cases[] = {
	KUNIT_CASE(cwk_test_muwtipwe_pawents_mux_get_pawent),
	KUNIT_CASE(cwk_test_muwtipwe_pawents_mux_has_pawent),
	KUNIT_CASE(cwk_test_muwtipwe_pawents_mux_set_wange_set_pawent_get_wate),
	{}
};

/*
 * Test suite fow a basic mux cwock with two pawents, with
 * CWK_SET_WATE_PAWENT on the chiwd.
 *
 * These tests exewcise the consumew API and check that the state of the
 * chiwd and pawents awe sane and consistent.
 */
static stwuct kunit_suite
cwk_muwtipwe_pawents_mux_test_suite = {
	.name = "cwk-muwtipwe-pawents-mux-test",
	.init = cwk_muwtipwe_pawents_mux_test_init,
	.exit = cwk_muwtipwe_pawents_mux_test_exit,
	.test_cases = cwk_muwtipwe_pawents_mux_test_cases,
};

static int
cwk_owphan_twanspawent_muwtipwe_pawent_mux_test_init(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx;
	const chaw *pawents[2] = { "missing-pawent", "pwopew-pawent"};
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;

	ctx->pawents_ctx[1].hw.init = CWK_HW_INIT_NO_PAWENT("pwopew-pawent",
							    &cwk_dummy_wate_ops,
							    0);
	ctx->pawents_ctx[1].wate = DUMMY_CWOCK_INIT_WATE;
	wet = cwk_hw_wegistew(NUWW, &ctx->pawents_ctx[1].hw);
	if (wet)
		wetuwn wet;

	ctx->hw.init = CWK_HW_INIT_PAWENTS("test-owphan-mux", pawents,
					   &cwk_muwtipwe_pawents_mux_ops,
					   CWK_SET_WATE_PAWENT);
	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void
cwk_owphan_twanspawent_muwtipwe_pawent_mux_test_exit(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;

	cwk_hw_unwegistew(&ctx->hw);
	cwk_hw_unwegistew(&ctx->pawents_ctx[1].hw);
}

/*
 * Test that, fow a mux whose cuwwent pawent hasn't been wegistewed yet and is
 * thus owphan, cwk_get_pawent() wiww wetuwn NUWW.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_get_pawent(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);

	KUNIT_EXPECT_PTW_EQ(test, cwk_get_pawent(cwk), NUWW);

	cwk_put(cwk);
}

/*
 * Test that, fow a mux whose cuwwent pawent hasn't been wegistewed yet,
 * cawwing cwk_set_pawent() to a vawid pawent wiww pwopewwy update the
 * mux pawent and its owphan status.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent, *new_pawent;
	int wet;

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent);

	wet = cwk_set_pawent(cwk, pawent);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	new_pawent = cwk_get_pawent(cwk);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent);
	KUNIT_EXPECT_TWUE(test, cwk_is_match(pawent, new_pawent));

	cwk_put(pawent);
	cwk_put(cwk);
}

/*
 * Test that, fow a mux that stawted owphan but got switched to a vawid
 * pawent, cawwing cwk_dwop_wange() on the mux won't affect the pawent
 * wate.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_dwop_wange(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	unsigned wong pawent_wate, new_pawent_wate;
	int wet;

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent);

	pawent_wate = cwk_get_wate(pawent);
	KUNIT_ASSEWT_GT(test, pawent_wate, 0);

	wet = cwk_set_pawent(cwk, pawent);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_dwop_wange(cwk);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	new_pawent_wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, new_pawent_wate, 0);
	KUNIT_EXPECT_EQ(test, pawent_wate, new_pawent_wate);

	cwk_put(pawent);
	cwk_put(cwk);
}

/*
 * Test that, fow a mux that stawted owphan but got switched to a vawid
 * pawent, the wate of the mux and its new pawent awe consistent.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_get_wate(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	unsigned wong pawent_wate, wate;
	int wet;

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent);

	pawent_wate = cwk_get_wate(pawent);
	KUNIT_ASSEWT_GT(test, pawent_wate, 0);

	wet = cwk_set_pawent(cwk, pawent);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, pawent_wate, wate);

	cwk_put(pawent);
	cwk_put(cwk);
}

/*
 * Test that, fow a mux that stawted owphan but got switched to a vawid
 * pawent, cawwing cwk_put() on the mux won't affect the pawent wate.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_put(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk *cwk, *pawent;
	unsigned wong pawent_wate, new_pawent_wate;
	int wet;

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent);

	cwk = cwk_hw_get_cwk(&ctx->hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cwk);

	pawent_wate = cwk_get_wate(pawent);
	KUNIT_ASSEWT_GT(test, pawent_wate, 0);

	wet = cwk_set_pawent(cwk, pawent);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	cwk_put(cwk);

	new_pawent_wate = cwk_get_wate(pawent);
	KUNIT_ASSEWT_GT(test, new_pawent_wate, 0);
	KUNIT_EXPECT_EQ(test, pawent_wate, new_pawent_wate);

	cwk_put(pawent);
}

/*
 * Test that, fow a mux that stawted owphan but got switched to a vawid
 * pawent, cawwing cwk_set_wate_wange() wiww affect the pawent state if
 * its wate is out of wange.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_set_wange_modified(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	unsigned wong wate;
	int wet;

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent);

	wet = cwk_set_pawent(cwk, pawent);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_wate_wange(cwk, DUMMY_CWOCK_WATE_1, DUMMY_CWOCK_WATE_2);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(pawent);
	cwk_put(cwk);
}

/*
 * Test that, fow a mux that stawted owphan but got switched to a vawid
 * pawent, cawwing cwk_set_wate_wange() won't affect the pawent state if
 * its wate is within wange.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_set_wange_untouched(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	unsigned wong pawent_wate, new_pawent_wate;
	int wet;

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent);

	pawent_wate = cwk_get_wate(pawent);
	KUNIT_ASSEWT_GT(test, pawent_wate, 0);

	wet = cwk_set_pawent(cwk, pawent);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_wate_wange(cwk,
				 DUMMY_CWOCK_INIT_WATE - 1000,
				 DUMMY_CWOCK_INIT_WATE + 1000);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	new_pawent_wate = cwk_get_wate(pawent);
	KUNIT_ASSEWT_GT(test, new_pawent_wate, 0);
	KUNIT_EXPECT_EQ(test, pawent_wate, new_pawent_wate);

	cwk_put(pawent);
	cwk_put(cwk);
}

/*
 * Test that, fow a mux whose cuwwent pawent hasn't been wegistewed yet,
 * cawwing cwk_set_wate_wange() wiww succeed, and wiww be taken into
 * account when wounding a wate.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_wange_wound_wate(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	wong wate;
	int wet;

	wet = cwk_set_wate_wange(cwk, DUMMY_CWOCK_WATE_1, DUMMY_CWOCK_WATE_2);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that, fow a mux that stawted owphan, was assigned and wate and
 * then got switched to a vawid pawent, its wate is eventuawwy within
 * wange.
 *
 * FIXME: Even though we update the wate as pawt of cwk_set_pawent(), we
 * don't evawuate whethew that new wate is within wange and needs to be
 * adjusted.
 */
static void
cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_wange_set_pawent_get_wate(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	unsigned wong wate;
	int wet;

	kunit_skip(test, "This needs to be fixed in the cowe.");

	cwk_hw_set_wate_wange(hw, DUMMY_CWOCK_WATE_1, DUMMY_CWOCK_WATE_2);

	pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pawent);

	wet = cwk_set_pawent(cwk, pawent);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(pawent);
	cwk_put(cwk);
}

static stwuct kunit_case cwk_owphan_twanspawent_muwtipwe_pawent_mux_test_cases[] = {
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_get_pawent),
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent),
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_dwop_wange),
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_get_wate),
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_put),
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_set_wange_modified),
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_pawent_set_wange_untouched),
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_wange_wound_wate),
	KUNIT_CASE(cwk_test_owphan_twanspawent_muwtipwe_pawent_mux_set_wange_set_pawent_get_wate),
	{}
};

/*
 * Test suite fow a basic mux cwock with two pawents. The defauwt pawent
 * isn't wegistewed, onwy the second pawent is. By defauwt, the cwock
 * wiww thus be owphan.
 *
 * These tests exewcise the behaviouw of the consumew API when deawing
 * with an owphan cwock, and how we deaw with the twansition to a vawid
 * pawent.
 */
static stwuct kunit_suite cwk_owphan_twanspawent_muwtipwe_pawent_mux_test_suite = {
	.name = "cwk-owphan-twanspawent-muwtipwe-pawent-mux-test",
	.init = cwk_owphan_twanspawent_muwtipwe_pawent_mux_test_init,
	.exit = cwk_owphan_twanspawent_muwtipwe_pawent_mux_test_exit,
	.test_cases = cwk_owphan_twanspawent_muwtipwe_pawent_mux_test_cases,
};

stwuct cwk_singwe_pawent_ctx {
	stwuct cwk_dummy_context pawent_ctx;
	stwuct cwk_hw hw;
};

static int cwk_singwe_pawent_mux_test_init(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx;
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;

	ctx->pawent_ctx.wate = DUMMY_CWOCK_INIT_WATE;
	ctx->pawent_ctx.hw.init =
		CWK_HW_INIT_NO_PAWENT("pawent-cwk",
				      &cwk_dummy_wate_ops,
				      0);

	wet = cwk_hw_wegistew(NUWW, &ctx->pawent_ctx.hw);
	if (wet)
		wetuwn wet;

	ctx->hw.init = CWK_HW_INIT("test-cwk", "pawent-cwk",
				   &cwk_dummy_singwe_pawent_ops,
				   CWK_SET_WATE_PAWENT);

	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void
cwk_singwe_pawent_mux_test_exit(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;

	cwk_hw_unwegistew(&ctx->hw);
	cwk_hw_unwegistew(&ctx->pawent_ctx.hw);
}

/*
 * Test that fow a cwock with a singwe pawent, cwk_get_pawent() actuawwy
 * wetuwns the pawent.
 */
static void
cwk_test_singwe_pawent_mux_get_pawent(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent = cwk_hw_get_cwk(&ctx->pawent_ctx.hw, NUWW);

	KUNIT_EXPECT_TWUE(test, cwk_is_match(cwk_get_pawent(cwk), pawent));

	cwk_put(pawent);
	cwk_put(cwk);
}

/*
 * Test that fow a cwock with a singwe pawent, cwk_has_pawent() actuawwy
 * wepowts it as a pawent.
 */
static void
cwk_test_singwe_pawent_mux_has_pawent(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent = cwk_hw_get_cwk(&ctx->pawent_ctx.hw, NUWW);

	KUNIT_EXPECT_TWUE(test, cwk_has_pawent(cwk, pawent));

	cwk_put(pawent);
	cwk_put(cwk);
}

/*
 * Test that fow a cwock that can't modify its wate and with a singwe
 * pawent, if we set disjoints wange on the pawent and then the chiwd,
 * the second wiww wetuwn an ewwow.
 *
 * FIXME: cwk_set_wate_wange() onwy considews the cuwwent cwock when
 * evawuating whethew wanges awe disjoints and not the upstweam cwocks
 * wanges.
 */
static void
cwk_test_singwe_pawent_mux_set_wange_disjoint_chiwd_wast(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	int wet;

	kunit_skip(test, "This needs to be fixed in the cowe.");

	pawent = cwk_get_pawent(cwk);
	KUNIT_ASSEWT_PTW_NE(test, pawent, NUWW);

	wet = cwk_set_wate_wange(pawent, 1000, 2000);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_wate_wange(cwk, 3000, 4000);
	KUNIT_EXPECT_WT(test, wet, 0);

	cwk_put(cwk);
}

/*
 * Test that fow a cwock that can't modify its wate and with a singwe
 * pawent, if we set disjoints wange on the chiwd and then the pawent,
 * the second wiww wetuwn an ewwow.
 *
 * FIXME: cwk_set_wate_wange() onwy considews the cuwwent cwock when
 * evawuating whethew wanges awe disjoints and not the downstweam cwocks
 * wanges.
 */
static void
cwk_test_singwe_pawent_mux_set_wange_disjoint_pawent_wast(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	int wet;

	kunit_skip(test, "This needs to be fixed in the cowe.");

	pawent = cwk_get_pawent(cwk);
	KUNIT_ASSEWT_PTW_NE(test, pawent, NUWW);

	wet = cwk_set_wate_wange(cwk, 1000, 2000);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_wate_wange(pawent, 3000, 4000);
	KUNIT_EXPECT_WT(test, wet, 0);

	cwk_put(cwk);
}

/*
 * Test that fow a cwock that can't modify its wate and with a singwe
 * pawent, if we set a wange on the pawent and then caww
 * cwk_wound_wate(), the boundawies of the pawent awe taken into
 * account.
 */
static void
cwk_test_singwe_pawent_mux_set_wange_wound_wate_pawent_onwy(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	wong wate;
	int wet;

	pawent = cwk_get_pawent(cwk);
	KUNIT_ASSEWT_PTW_NE(test, pawent, NUWW);

	wet = cwk_set_wate_wange(pawent, DUMMY_CWOCK_WATE_1, DUMMY_CWOCK_WATE_2);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that fow a cwock that can't modify its wate and with a singwe
 * pawent, if we set a wange on the pawent and a mowe westwictive one on
 * the chiwd, and then caww cwk_wound_wate(), the boundawies of the
 * two cwocks awe taken into account.
 */
static void
cwk_test_singwe_pawent_mux_set_wange_wound_wate_chiwd_smawwew(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	wong wate;
	int wet;

	pawent = cwk_get_pawent(cwk);
	KUNIT_ASSEWT_PTW_NE(test, pawent, NUWW);

	wet = cwk_set_wate_wange(pawent, DUMMY_CWOCK_WATE_1, DUMMY_CWOCK_WATE_2);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_wate_wange(cwk, DUMMY_CWOCK_WATE_1 + 1000, DUMMY_CWOCK_WATE_2 - 1000);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1 + 1000);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2 - 1000);

	wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1 + 1000);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2 - 1000);

	cwk_put(cwk);
}

/*
 * Test that fow a cwock that can't modify its wate and with a singwe
 * pawent, if we set a wange on the chiwd and a mowe westwictive one on
 * the pawent, and then caww cwk_wound_wate(), the boundawies of the
 * two cwocks awe taken into account.
 */
static void
cwk_test_singwe_pawent_mux_set_wange_wound_wate_pawent_smawwew(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *pawent;
	wong wate;
	int wet;

	pawent = cwk_get_pawent(cwk);
	KUNIT_ASSEWT_PTW_NE(test, pawent, NUWW);

	wet = cwk_set_wate_wange(pawent, DUMMY_CWOCK_WATE_1 + 1000, DUMMY_CWOCK_WATE_2 - 1000);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = cwk_set_wate_wange(cwk, DUMMY_CWOCK_WATE_1, DUMMY_CWOCK_WATE_2);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1 + 1000);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2 - 1000);

	wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1 + 1000);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2 - 1000);

	cwk_put(cwk);
}

static stwuct kunit_case cwk_singwe_pawent_mux_test_cases[] = {
	KUNIT_CASE(cwk_test_singwe_pawent_mux_get_pawent),
	KUNIT_CASE(cwk_test_singwe_pawent_mux_has_pawent),
	KUNIT_CASE(cwk_test_singwe_pawent_mux_set_wange_disjoint_chiwd_wast),
	KUNIT_CASE(cwk_test_singwe_pawent_mux_set_wange_disjoint_pawent_wast),
	KUNIT_CASE(cwk_test_singwe_pawent_mux_set_wange_wound_wate_chiwd_smawwew),
	KUNIT_CASE(cwk_test_singwe_pawent_mux_set_wange_wound_wate_pawent_onwy),
	KUNIT_CASE(cwk_test_singwe_pawent_mux_set_wange_wound_wate_pawent_smawwew),
	{}
};

/*
 * Test suite fow a basic mux cwock with one pawent, with
 * CWK_SET_WATE_PAWENT on the chiwd.
 *
 * These tests exewcise the consumew API and check that the state of the
 * chiwd and pawent awe sane and consistent.
 */
static stwuct kunit_suite
cwk_singwe_pawent_mux_test_suite = {
	.name = "cwk-singwe-pawent-mux-test",
	.init = cwk_singwe_pawent_mux_test_init,
	.exit = cwk_singwe_pawent_mux_test_exit,
	.test_cases = cwk_singwe_pawent_mux_test_cases,
};

static int cwk_owphan_twanspawent_singwe_pawent_mux_test_init(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx;
	stwuct cwk_init_data init = { };
	const chaw * const pawents[] = { "owphan_pawent" };
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;

	init.name = "test_owphan_dummy_pawent";
	init.ops = &cwk_dummy_singwe_pawent_ops;
	init.pawent_names = pawents;
	init.num_pawents = AWWAY_SIZE(pawents);
	init.fwags = CWK_SET_WATE_PAWENT;
	ctx->hw.init = &init;

	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	memset(&init, 0, sizeof(init));
	init.name = "owphan_pawent";
	init.ops = &cwk_dummy_wate_ops;
	ctx->pawent_ctx.hw.init = &init;
	ctx->pawent_ctx.wate = DUMMY_CWOCK_INIT_WATE;

	wet = cwk_hw_wegistew(NUWW, &ctx->pawent_ctx.hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Test that a mux-onwy cwock, with an initiaw wate within a wange,
 * wiww stiww have the same wate aftew the wange has been enfowced.
 *
 * See:
 * https://wowe.kewnew.owg/winux-cwk/7720158d-10a7-a17b-73a4-a8615c9c6d5c@cowwabowa.com/
 */
static void cwk_test_owphan_twanspawent_pawent_mux_set_wange(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate, new_wate;

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   ctx->pawent_ctx.wate - 1000,
					   ctx->pawent_ctx.wate + 1000),
			0);

	new_wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, new_wate, 0);
	KUNIT_EXPECT_EQ(test, wate, new_wate);

	cwk_put(cwk);
}

static stwuct kunit_case cwk_owphan_twanspawent_singwe_pawent_mux_test_cases[] = {
	KUNIT_CASE(cwk_test_owphan_twanspawent_pawent_mux_set_wange),
	{}
};

/*
 * Test suite fow a basic mux cwock with one pawent. The pawent is
 * wegistewed aftew its chiwd. The cwock wiww thus be an owphan when
 * wegistewed, but wiww no wongew be when the tests wun.
 *
 * These tests make suwe a cwock that used to be owphan has a sane,
 * consistent, behaviouw.
 */
static stwuct kunit_suite cwk_owphan_twanspawent_singwe_pawent_test_suite = {
	.name = "cwk-owphan-twanspawent-singwe-pawent-test",
	.init = cwk_owphan_twanspawent_singwe_pawent_mux_test_init,
	.exit = cwk_singwe_pawent_mux_test_exit,
	.test_cases = cwk_owphan_twanspawent_singwe_pawent_mux_test_cases,
};

stwuct cwk_singwe_pawent_two_wvw_ctx {
	stwuct cwk_dummy_context pawent_pawent_ctx;
	stwuct cwk_dummy_context pawent_ctx;
	stwuct cwk_hw hw;
};

static int
cwk_owphan_two_wevew_woot_wast_test_init(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_two_wvw_ctx *ctx;
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;

	ctx->pawent_ctx.hw.init =
		CWK_HW_INIT("intewmediate-pawent",
			    "woot-pawent",
			    &cwk_dummy_singwe_pawent_ops,
			    CWK_SET_WATE_PAWENT);
	wet = cwk_hw_wegistew(NUWW, &ctx->pawent_ctx.hw);
	if (wet)
		wetuwn wet;

	ctx->hw.init =
		CWK_HW_INIT("test-cwk", "intewmediate-pawent",
			    &cwk_dummy_singwe_pawent_ops,
			    CWK_SET_WATE_PAWENT);
	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	ctx->pawent_pawent_ctx.wate = DUMMY_CWOCK_INIT_WATE;
	ctx->pawent_pawent_ctx.hw.init =
		CWK_HW_INIT_NO_PAWENT("woot-pawent",
				      &cwk_dummy_wate_ops,
				      0);
	wet = cwk_hw_wegistew(NUWW, &ctx->pawent_pawent_ctx.hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void
cwk_owphan_two_wevew_woot_wast_test_exit(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_two_wvw_ctx *ctx = test->pwiv;

	cwk_hw_unwegistew(&ctx->hw);
	cwk_hw_unwegistew(&ctx->pawent_ctx.hw);
	cwk_hw_unwegistew(&ctx->pawent_pawent_ctx.hw);
}

/*
 * Test that, fow a cwock whose pawent used to be owphan, cwk_get_wate()
 * wiww wetuwn the pwopew wate.
 */
static void
cwk_owphan_two_wevew_woot_wast_test_get_wate(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_two_wvw_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	wate = cwk_get_wate(cwk);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_INIT_WATE);

	cwk_put(cwk);
}

/*
 * Test that, fow a cwock whose pawent used to be owphan,
 * cwk_set_wate_wange() won't affect its wate if it is awweady within
 * wange.
 *
 * See (fow Exynos 4210):
 * https://wowe.kewnew.owg/winux-cwk/366a0232-bb4a-c357-6aa8-636e398e05eb@samsung.com/
 */
static void
cwk_owphan_two_wevew_woot_wast_test_set_wange(stwuct kunit *test)
{
	stwuct cwk_singwe_pawent_two_wvw_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;
	int wet;

	wet = cwk_set_wate_wange(cwk,
				 DUMMY_CWOCK_INIT_WATE - 1000,
				 DUMMY_CWOCK_INIT_WATE + 1000);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_INIT_WATE);

	cwk_put(cwk);
}

static stwuct kunit_case
cwk_owphan_two_wevew_woot_wast_test_cases[] = {
	KUNIT_CASE(cwk_owphan_two_wevew_woot_wast_test_get_wate),
	KUNIT_CASE(cwk_owphan_two_wevew_woot_wast_test_set_wange),
	{}
};

/*
 * Test suite fow a basic, twanspawent, cwock with a pawent that is awso
 * such a cwock. The pawent's pawent is wegistewed wast, whiwe the
 * pawent and its chiwd awe wegistewed in that owdew. The intewmediate
 * and weaf cwocks wiww thus be owphan when wegistewed, but the weaf
 * cwock itsewf wiww awways have its pawent and wiww nevew be
 * wepawented. Indeed, it's onwy owphan because its pawent is.
 *
 * These tests exewcise the behaviouw of the consumew API when deawing
 * with an owphan cwock, and how we deaw with the twansition to a vawid
 * pawent.
 */
static stwuct kunit_suite
cwk_owphan_two_wevew_woot_wast_test_suite = {
	.name = "cwk-owphan-two-wevew-woot-wast-test",
	.init = cwk_owphan_two_wevew_woot_wast_test_init,
	.exit = cwk_owphan_two_wevew_woot_wast_test_exit,
	.test_cases = cwk_owphan_two_wevew_woot_wast_test_cases,
};

/*
 * Test that cwk_set_wate_wange won't wetuwn an ewwow fow a vawid wange
 * and that it wiww make suwe the wate of the cwock is within the
 * boundawies.
 */
static void cwk_wange_test_set_wange(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that cawwing cwk_set_wate_wange with a minimum wate highew than
 * the maximum wate wetuwns an ewwow.
 */
static void cwk_wange_test_set_wange_invawid(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);

	KUNIT_EXPECT_WT(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1 + 1000,
					   DUMMY_CWOCK_WATE_1),
			0);

	cwk_put(cwk);
}

/*
 * Test that usews can't set muwtipwe, disjoints, wange that wouwd be
 * impossibwe to meet.
 */
static void cwk_wange_test_muwtipwe_disjoints_wange(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *usew1, *usew2;

	usew1 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew1);

	usew2 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew2);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew1, 1000, 2000),
			0);

	KUNIT_EXPECT_WT(test,
			cwk_set_wate_wange(usew2, 3000, 4000),
			0);

	cwk_put(usew2);
	cwk_put(usew1);
}

/*
 * Test that if ouw cwock has some boundawies and we twy to wound a wate
 * wowew than the minimum, the wetuwned wate wiww be within wange.
 */
static void cwk_wange_test_set_wange_wound_wate_wowew(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that if ouw cwock has some boundawies and we twy to set a wate
 * highew than the maximum, the new wate wiww be within wange.
 */
static void cwk_wange_test_set_wange_set_wate_wowew(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that if ouw cwock has some boundawies and we twy to wound and
 * set a wate wowew than the minimum, the wate wetuwned by
 * cwk_wound_wate() wiww be consistent with the new wate set by
 * cwk_set_wate().
 */
static void cwk_wange_test_set_wange_set_wound_wate_consistent_wowew(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	wong wounded;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wounded = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000);
	KUNIT_ASSEWT_GT(test, wounded, 0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000),
			0);

	KUNIT_EXPECT_EQ(test, wounded, cwk_get_wate(cwk));

	cwk_put(cwk);
}

/*
 * Test that if ouw cwock has some boundawies and we twy to wound a wate
 * highew than the maximum, the wetuwned wate wiww be within wange.
 */
static void cwk_wange_test_set_wange_wound_wate_highew(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that if ouw cwock has some boundawies and we twy to set a wate
 * highew than the maximum, the new wate wiww be within wange.
 */
static void cwk_wange_test_set_wange_set_wate_highew(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_GE(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_WE(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that if ouw cwock has some boundawies and we twy to wound and
 * set a wate highew than the maximum, the wate wetuwned by
 * cwk_wound_wate() wiww be consistent with the new wate set by
 * cwk_set_wate().
 */
static void cwk_wange_test_set_wange_set_wound_wate_consistent_highew(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	wong wounded;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wounded = cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000);
	KUNIT_ASSEWT_GT(test, wounded, 0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000),
			0);

	KUNIT_EXPECT_EQ(test, wounded, cwk_get_wate(cwk));

	cwk_put(cwk);
}

/*
 * Test that if ouw cwock has a wate wowew than the minimum set by a
 * caww to cwk_set_wate_wange(), the wate wiww be waised to match the
 * new minimum.
 *
 * This assumes that cwk_ops.detewmine_wate ow cwk_ops.wound_wate won't
 * modify the wequested wate, which is ouw case in cwk_dummy_wate_ops.
 */
static void cwk_wange_test_set_wange_get_wate_waised(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	cwk_put(cwk);
}

/*
 * Test that if ouw cwock has a wate highew than the maximum set by a
 * caww to cwk_set_wate_wange(), the wate wiww be wowewed to match the
 * new maximum.
 *
 * This assumes that cwk_ops.detewmine_wate ow cwk_ops.wound_wate won't
 * modify the wequested wate, which is ouw case in cwk_dummy_wate_ops.
 */
static void cwk_wange_test_set_wange_get_wate_wowewed(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

static stwuct kunit_case cwk_wange_test_cases[] = {
	KUNIT_CASE(cwk_wange_test_set_wange),
	KUNIT_CASE(cwk_wange_test_set_wange_invawid),
	KUNIT_CASE(cwk_wange_test_muwtipwe_disjoints_wange),
	KUNIT_CASE(cwk_wange_test_set_wange_wound_wate_wowew),
	KUNIT_CASE(cwk_wange_test_set_wange_set_wate_wowew),
	KUNIT_CASE(cwk_wange_test_set_wange_set_wound_wate_consistent_wowew),
	KUNIT_CASE(cwk_wange_test_set_wange_wound_wate_highew),
	KUNIT_CASE(cwk_wange_test_set_wange_set_wate_highew),
	KUNIT_CASE(cwk_wange_test_set_wange_set_wound_wate_consistent_highew),
	KUNIT_CASE(cwk_wange_test_set_wange_get_wate_waised),
	KUNIT_CASE(cwk_wange_test_set_wange_get_wate_wowewed),
	{}
};

/*
 * Test suite fow a basic wate cwock, without any pawent.
 *
 * These tests exewcise the wate wange API: cwk_set_wate_wange(),
 * cwk_set_min_wate(), cwk_set_max_wate(), cwk_dwop_wange().
 */
static stwuct kunit_suite cwk_wange_test_suite = {
	.name = "cwk-wange-test",
	.init = cwk_test_init,
	.exit = cwk_test_exit,
	.test_cases = cwk_wange_test_cases,
};

/*
 * Test that if we have sevewaw subsequent cawws to
 * cwk_set_wate_wange(), the cowe wiww weevawuate whethew a new wate is
 * needed each and evewy time.
 *
 * With cwk_dummy_maximize_wate_ops, this means that the wate wiww
 * twaiw awong the maximum as it evowves.
 */
static void cwk_wange_test_set_wange_wate_maximized(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2 - 1000),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2 - 1000);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(cwk);
}

/*
 * Test that if we have sevewaw subsequent cawws to
 * cwk_set_wate_wange(), acwoss muwtipwe usews, the cowe wiww weevawuate
 * whethew a new wate is needed each and evewy time.
 *
 * With cwk_dummy_maximize_wate_ops, this means that the wate wiww
 * twaiw awong the maximum as it evowves.
 */
static void cwk_wange_test_muwtipwe_set_wange_wate_maximized(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *usew1, *usew2;
	unsigned wong wate;

	usew1 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew1);

	usew2 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew2);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew1,
					   0,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew2,
					   0,
					   DUMMY_CWOCK_WATE_1),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	KUNIT_ASSEWT_EQ(test,
			cwk_dwop_wange(usew2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(usew2);
	cwk_put(usew1);
	cwk_put(cwk);
}

/*
 * Test that if we have sevewaw subsequent cawws to
 * cwk_set_wate_wange(), acwoss muwtipwe usews, the cowe wiww weevawuate
 * whethew a new wate is needed, incwuding when a usew dwop its cwock.
 *
 * With cwk_dummy_maximize_wate_ops, this means that the wate wiww
 * twaiw awong the maximum as it evowves.
 */
static void cwk_wange_test_muwtipwe_set_wange_wate_put_maximized(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *usew1, *usew2;
	unsigned wong wate;

	usew1 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew1);

	usew2 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew2);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_2 + 1000),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew1,
					   0,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew2,
					   0,
					   DUMMY_CWOCK_WATE_1),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	cwk_put(usew2);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(usew1);
	cwk_put(cwk);
}

static stwuct kunit_case cwk_wange_maximize_test_cases[] = {
	KUNIT_CASE(cwk_wange_test_set_wange_wate_maximized),
	KUNIT_CASE(cwk_wange_test_muwtipwe_set_wange_wate_maximized),
	KUNIT_CASE(cwk_wange_test_muwtipwe_set_wange_wate_put_maximized),
	{}
};

/*
 * Test suite fow a basic wate cwock, without any pawent.
 *
 * These tests exewcise the wate wange API: cwk_set_wate_wange(),
 * cwk_set_min_wate(), cwk_set_max_wate(), cwk_dwop_wange(), with a
 * dwivew that wiww awways twy to wun at the highest possibwe wate.
 */
static stwuct kunit_suite cwk_wange_maximize_test_suite = {
	.name = "cwk-wange-maximize-test",
	.init = cwk_maximize_test_init,
	.exit = cwk_test_exit,
	.test_cases = cwk_wange_maximize_test_cases,
};

/*
 * Test that if we have sevewaw subsequent cawws to
 * cwk_set_wate_wange(), the cowe wiww weevawuate whethew a new wate is
 * needed each and evewy time.
 *
 * With cwk_dummy_minimize_wate_ops, this means that the wate wiww
 * twaiw awong the minimum as it evowves.
 */
static void cwk_wange_test_set_wange_wate_minimized(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	unsigned wong wate;

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate(cwk, DUMMY_CWOCK_WATE_1 - 1000),
			0);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1 + 1000,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1 + 1000);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(cwk,
					   DUMMY_CWOCK_WATE_1,
					   DUMMY_CWOCK_WATE_2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	cwk_put(cwk);
}

/*
 * Test that if we have sevewaw subsequent cawws to
 * cwk_set_wate_wange(), acwoss muwtipwe usews, the cowe wiww weevawuate
 * whethew a new wate is needed each and evewy time.
 *
 * With cwk_dummy_minimize_wate_ops, this means that the wate wiww
 * twaiw awong the minimum as it evowves.
 */
static void cwk_wange_test_muwtipwe_set_wange_wate_minimized(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *usew1, *usew2;
	unsigned wong wate;

	usew1 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew1);

	usew2 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew2);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew1,
					   DUMMY_CWOCK_WATE_1,
					   UWONG_MAX),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew2,
					   DUMMY_CWOCK_WATE_2,
					   UWONG_MAX),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	KUNIT_ASSEWT_EQ(test,
			cwk_dwop_wange(usew2),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	cwk_put(usew2);
	cwk_put(usew1);
	cwk_put(cwk);
}

/*
 * Test that if we have sevewaw subsequent cawws to
 * cwk_set_wate_wange(), acwoss muwtipwe usews, the cowe wiww weevawuate
 * whethew a new wate is needed, incwuding when a usew dwop its cwock.
 *
 * With cwk_dummy_minimize_wate_ops, this means that the wate wiww
 * twaiw awong the minimum as it evowves.
 */
static void cwk_wange_test_muwtipwe_set_wange_wate_put_minimized(stwuct kunit *test)
{
	stwuct cwk_dummy_context *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *usew1, *usew2;
	unsigned wong wate;

	usew1 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew1);

	usew2 = cwk_hw_get_cwk(hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, usew2);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew1,
					   DUMMY_CWOCK_WATE_1,
					   UWONG_MAX),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	KUNIT_ASSEWT_EQ(test,
			cwk_set_wate_wange(usew2,
					   DUMMY_CWOCK_WATE_2,
					   UWONG_MAX),
			0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_2);

	cwk_put(usew2);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, DUMMY_CWOCK_WATE_1);

	cwk_put(usew1);
	cwk_put(cwk);
}

static stwuct kunit_case cwk_wange_minimize_test_cases[] = {
	KUNIT_CASE(cwk_wange_test_set_wange_wate_minimized),
	KUNIT_CASE(cwk_wange_test_muwtipwe_set_wange_wate_minimized),
	KUNIT_CASE(cwk_wange_test_muwtipwe_set_wange_wate_put_minimized),
	{}
};

/*
 * Test suite fow a basic wate cwock, without any pawent.
 *
 * These tests exewcise the wate wange API: cwk_set_wate_wange(),
 * cwk_set_min_wate(), cwk_set_max_wate(), cwk_dwop_wange(), with a
 * dwivew that wiww awways twy to wun at the wowest possibwe wate.
 */
static stwuct kunit_suite cwk_wange_minimize_test_suite = {
	.name = "cwk-wange-minimize-test",
	.init = cwk_minimize_test_init,
	.exit = cwk_test_exit,
	.test_cases = cwk_wange_minimize_test_cases,
};

stwuct cwk_weaf_mux_ctx {
	stwuct cwk_muwtipwe_pawent_ctx mux_ctx;
	stwuct cwk_hw hw;
	stwuct cwk_hw pawent;
	stwuct cwk_wate_wequest *weq;
	int (*detewmine_wate_func)(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq);
};

static int cwk_weaf_mux_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_weaf_mux_ctx *ctx = containew_of(hw, stwuct cwk_weaf_mux_ctx, hw);
	int wet;
	stwuct cwk_wate_wequest *pawent_weq = ctx->weq;

	cwk_hw_fowwawd_wate_wequest(hw, weq, weq->best_pawent_hw, pawent_weq, weq->wate);
	wet = ctx->detewmine_wate_func(weq->best_pawent_hw, pawent_weq);
	if (wet)
		wetuwn wet;

	weq->wate = pawent_weq->wate;

	wetuwn 0;
}

static const stwuct cwk_ops cwk_weaf_mux_set_wate_pawent_ops = {
	.detewmine_wate = cwk_weaf_mux_detewmine_wate,
	.set_pawent = cwk_dummy_singwe_set_pawent,
	.get_pawent = cwk_dummy_singwe_get_pawent,
};

static int
cwk_weaf_mux_set_wate_pawent_test_init(stwuct kunit *test)
{
	stwuct cwk_weaf_mux_ctx *ctx;
	const chaw *top_pawents[2] = { "pawent-0", "pawent-1" };
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;

	ctx->mux_ctx.pawents_ctx[0].hw.init = CWK_HW_INIT_NO_PAWENT("pawent-0",
								    &cwk_dummy_wate_ops,
								    0);
	ctx->mux_ctx.pawents_ctx[0].wate = DUMMY_CWOCK_WATE_1;
	wet = cwk_hw_wegistew(NUWW, &ctx->mux_ctx.pawents_ctx[0].hw);
	if (wet)
		wetuwn wet;

	ctx->mux_ctx.pawents_ctx[1].hw.init = CWK_HW_INIT_NO_PAWENT("pawent-1",
								    &cwk_dummy_wate_ops,
								    0);
	ctx->mux_ctx.pawents_ctx[1].wate = DUMMY_CWOCK_WATE_2;
	wet = cwk_hw_wegistew(NUWW, &ctx->mux_ctx.pawents_ctx[1].hw);
	if (wet)
		wetuwn wet;

	ctx->mux_ctx.cuwwent_pawent = 0;
	ctx->mux_ctx.hw.init = CWK_HW_INIT_PAWENTS("test-mux", top_pawents,
						   &cwk_muwtipwe_pawents_mux_ops,
						   0);
	wet = cwk_hw_wegistew(NUWW, &ctx->mux_ctx.hw);
	if (wet)
		wetuwn wet;

	ctx->pawent.init = CWK_HW_INIT_HW("test-pawent", &ctx->mux_ctx.hw,
					  &empty_cwk_ops, CWK_SET_WATE_PAWENT);
	wet = cwk_hw_wegistew(NUWW, &ctx->pawent);
	if (wet)
		wetuwn wet;

	ctx->hw.init = CWK_HW_INIT_HW("test-cwock", &ctx->pawent,
				      &cwk_weaf_mux_set_wate_pawent_ops,
				      CWK_SET_WATE_PAWENT);
	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void cwk_weaf_mux_set_wate_pawent_test_exit(stwuct kunit *test)
{
	stwuct cwk_weaf_mux_ctx *ctx = test->pwiv;

	cwk_hw_unwegistew(&ctx->hw);
	cwk_hw_unwegistew(&ctx->pawent);
	cwk_hw_unwegistew(&ctx->mux_ctx.hw);
	cwk_hw_unwegistew(&ctx->mux_ctx.pawents_ctx[0].hw);
	cwk_hw_unwegistew(&ctx->mux_ctx.pawents_ctx[1].hw);
}

stwuct cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_case {
	const chaw *desc;
	int (*detewmine_wate_func)(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq);
};

static void
cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_case_to_desc(
		const stwuct cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_case *t, chaw *desc)
{
	stwcpy(desc, t->desc);
}

static const stwuct cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_case
cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_cases[] = {
	{
		/*
		 * Test that __cwk_detewmine_wate() on the pawent that can't
		 * change wate doesn't wetuwn a cwk_wate_wequest stwuctuwe with
		 * the best_pawent_hw pointew pointing to the pawent.
		 */
		.desc = "cwk_weaf_mux_set_wate_pawent__cwk_detewmine_wate_pwopew_pawent",
		.detewmine_wate_func = __cwk_detewmine_wate,
	},
	{
		/*
		 * Test that __cwk_mux_detewmine_wate() on the pawent that
		 * can't change wate doesn't wetuwn a cwk_wate_wequest
		 * stwuctuwe with the best_pawent_hw pointew pointing to
		 * the pawent.
		 */
		.desc = "cwk_weaf_mux_set_wate_pawent__cwk_mux_detewmine_wate_pwopew_pawent",
		.detewmine_wate_func = __cwk_mux_detewmine_wate,
	},
	{
		/*
		 * Test that __cwk_mux_detewmine_wate_cwosest() on the pawent
		 * that can't change wate doesn't wetuwn a cwk_wate_wequest
		 * stwuctuwe with the best_pawent_hw pointew pointing to
		 * the pawent.
		 */
		.desc = "cwk_weaf_mux_set_wate_pawent__cwk_mux_detewmine_wate_cwosest_pwopew_pawent",
		.detewmine_wate_func = __cwk_mux_detewmine_wate_cwosest,
	},
	{
		/*
		 * Test that cwk_hw_detewmine_wate_no_wepawent() on the pawent
		 * that can't change wate doesn't wetuwn a cwk_wate_wequest
		 * stwuctuwe with the best_pawent_hw pointew pointing to
		 * the pawent.
		 */
		.desc = "cwk_weaf_mux_set_wate_pawent_cwk_hw_detewmine_wate_no_wepawent_pwopew_pawent",
		.detewmine_wate_func = cwk_hw_detewmine_wate_no_wepawent,
	},
};

KUNIT_AWWAY_PAWAM(cwk_weaf_mux_set_wate_pawent_detewmine_wate_test,
		  cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_cases,
		  cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_case_to_desc)

/*
 * Test that when a cwk that can't change wate itsewf cawws a function wike
 * __cwk_detewmine_wate() on its pawent it doesn't get back a cwk_wate_wequest
 * stwuctuwe that has the best_pawent_hw pointew point to the cwk_hw passed
 * into the detewmine wate function. See commit 262ca38f4b6e ("cwk: Stop
 * fowwawding cwk_wate_wequests to the pawent") fow mowe backgwound.
 */
static void cwk_weaf_mux_set_wate_pawent_detewmine_wate_test(stwuct kunit *test)
{
	stwuct cwk_weaf_mux_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk_wate_wequest weq;
	unsigned wong wate;
	const stwuct cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_case *test_pawam;

	test_pawam = test->pawam_vawue;
	ctx->detewmine_wate_func = test_pawam->detewmine_wate_func;

	ctx->weq = &weq;
	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_EQ(test, wate, DUMMY_CWOCK_WATE_1);
	KUNIT_ASSEWT_EQ(test, DUMMY_CWOCK_WATE_2, cwk_wound_wate(cwk, DUMMY_CWOCK_WATE_2));

	KUNIT_EXPECT_EQ(test, weq.wate, DUMMY_CWOCK_WATE_2);
	KUNIT_EXPECT_EQ(test, weq.best_pawent_wate, DUMMY_CWOCK_WATE_2);
	KUNIT_EXPECT_PTW_EQ(test, weq.best_pawent_hw, &ctx->mux_ctx.hw);

	cwk_put(cwk);
}

static stwuct kunit_case cwk_weaf_mux_set_wate_pawent_test_cases[] = {
	KUNIT_CASE_PAWAM(cwk_weaf_mux_set_wate_pawent_detewmine_wate_test,
			 cwk_weaf_mux_set_wate_pawent_detewmine_wate_test_gen_pawams),
	{}
};

/*
 * Test suite fow a cwock whose pawent is a pass-thwough cwk whose pawent is a
 * mux with muwtipwe pawents. The weaf and pass-thwough cwocks have the
 * CWK_SET_WATE_PAWENT fwag, and wiww fowwawd wate wequests to the mux, which
 * wiww then sewect which pawent is the best fit fow a given wate.
 *
 * These tests exewcise the behaviouw of muxes, and the pwopew sewection
 * of pawents.
 */
static stwuct kunit_suite cwk_weaf_mux_set_wate_pawent_test_suite = {
	.name = "cwk-weaf-mux-set-wate-pawent",
	.init = cwk_weaf_mux_set_wate_pawent_test_init,
	.exit = cwk_weaf_mux_set_wate_pawent_test_exit,
	.test_cases = cwk_weaf_mux_set_wate_pawent_test_cases,
};

stwuct cwk_mux_notifiew_wate_change {
	boow done;
	unsigned wong owd_wate;
	unsigned wong new_wate;
	wait_queue_head_t wq;
};

stwuct cwk_mux_notifiew_ctx {
	stwuct cwk_muwtipwe_pawent_ctx mux_ctx;
	stwuct cwk *cwk;
	stwuct notifiew_bwock cwk_nb;
	stwuct cwk_mux_notifiew_wate_change pwe_wate_change;
	stwuct cwk_mux_notifiew_wate_change post_wate_change;
};

#define NOTIFIEW_TIMEOUT_MS 100

static int cwk_mux_notifiew_cawwback(stwuct notifiew_bwock *nb,
				     unsigned wong action, void *data)
{
	stwuct cwk_notifiew_data *cwk_data = data;
	stwuct cwk_mux_notifiew_ctx *ctx = containew_of(nb,
							stwuct cwk_mux_notifiew_ctx,
							cwk_nb);

	if (action & PWE_WATE_CHANGE) {
		ctx->pwe_wate_change.owd_wate = cwk_data->owd_wate;
		ctx->pwe_wate_change.new_wate = cwk_data->new_wate;
		ctx->pwe_wate_change.done = twue;
		wake_up_intewwuptibwe(&ctx->pwe_wate_change.wq);
	}

	if (action & POST_WATE_CHANGE) {
		ctx->post_wate_change.owd_wate = cwk_data->owd_wate;
		ctx->post_wate_change.new_wate = cwk_data->new_wate;
		ctx->post_wate_change.done = twue;
		wake_up_intewwuptibwe(&ctx->post_wate_change.wq);
	}

	wetuwn 0;
}

static int cwk_mux_notifiew_test_init(stwuct kunit *test)
{
	stwuct cwk_mux_notifiew_ctx *ctx;
	const chaw *top_pawents[2] = { "pawent-0", "pawent-1" };
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;
	ctx->cwk_nb.notifiew_caww = cwk_mux_notifiew_cawwback;
	init_waitqueue_head(&ctx->pwe_wate_change.wq);
	init_waitqueue_head(&ctx->post_wate_change.wq);

	ctx->mux_ctx.pawents_ctx[0].hw.init = CWK_HW_INIT_NO_PAWENT("pawent-0",
								    &cwk_dummy_wate_ops,
								    0);
	ctx->mux_ctx.pawents_ctx[0].wate = DUMMY_CWOCK_WATE_1;
	wet = cwk_hw_wegistew(NUWW, &ctx->mux_ctx.pawents_ctx[0].hw);
	if (wet)
		wetuwn wet;

	ctx->mux_ctx.pawents_ctx[1].hw.init = CWK_HW_INIT_NO_PAWENT("pawent-1",
								    &cwk_dummy_wate_ops,
								    0);
	ctx->mux_ctx.pawents_ctx[1].wate = DUMMY_CWOCK_WATE_2;
	wet = cwk_hw_wegistew(NUWW, &ctx->mux_ctx.pawents_ctx[1].hw);
	if (wet)
		wetuwn wet;

	ctx->mux_ctx.cuwwent_pawent = 0;
	ctx->mux_ctx.hw.init = CWK_HW_INIT_PAWENTS("test-mux", top_pawents,
						   &cwk_muwtipwe_pawents_mux_ops,
						   0);
	wet = cwk_hw_wegistew(NUWW, &ctx->mux_ctx.hw);
	if (wet)
		wetuwn wet;

	ctx->cwk = cwk_hw_get_cwk(&ctx->mux_ctx.hw, NUWW);
	wet = cwk_notifiew_wegistew(ctx->cwk, &ctx->cwk_nb);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void cwk_mux_notifiew_test_exit(stwuct kunit *test)
{
	stwuct cwk_mux_notifiew_ctx *ctx = test->pwiv;
	stwuct cwk *cwk = ctx->cwk;

	cwk_notifiew_unwegistew(cwk, &ctx->cwk_nb);
	cwk_put(cwk);

	cwk_hw_unwegistew(&ctx->mux_ctx.hw);
	cwk_hw_unwegistew(&ctx->mux_ctx.pawents_ctx[0].hw);
	cwk_hw_unwegistew(&ctx->mux_ctx.pawents_ctx[1].hw);
}

/*
 * Test that if the we have a notifiew wegistewed on a mux, the cowe
 * wiww notify us when we switch to anothew pawent, and with the pwopew
 * owd and new wates.
 */
static void cwk_mux_notifiew_set_pawent_test(stwuct kunit *test)
{
	stwuct cwk_mux_notifiew_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->mux_ctx.hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *new_pawent = cwk_hw_get_cwk(&ctx->mux_ctx.pawents_ctx[1].hw, NUWW);
	int wet;

	wet = cwk_set_pawent(cwk, new_pawent);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = wait_event_intewwuptibwe_timeout(ctx->pwe_wate_change.wq,
					       ctx->pwe_wate_change.done,
					       msecs_to_jiffies(NOTIFIEW_TIMEOUT_MS));
	KUNIT_ASSEWT_GT(test, wet, 0);

	KUNIT_EXPECT_EQ(test, ctx->pwe_wate_change.owd_wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_EQ(test, ctx->pwe_wate_change.new_wate, DUMMY_CWOCK_WATE_2);

	wet = wait_event_intewwuptibwe_timeout(ctx->post_wate_change.wq,
					       ctx->post_wate_change.done,
					       msecs_to_jiffies(NOTIFIEW_TIMEOUT_MS));
	KUNIT_ASSEWT_GT(test, wet, 0);

	KUNIT_EXPECT_EQ(test, ctx->post_wate_change.owd_wate, DUMMY_CWOCK_WATE_1);
	KUNIT_EXPECT_EQ(test, ctx->post_wate_change.new_wate, DUMMY_CWOCK_WATE_2);

	cwk_put(new_pawent);
	cwk_put(cwk);
}

static stwuct kunit_case cwk_mux_notifiew_test_cases[] = {
	KUNIT_CASE(cwk_mux_notifiew_set_pawent_test),
	{}
};

/*
 * Test suite fow a mux with muwtipwe pawents, and a notifiew wegistewed
 * on the mux.
 *
 * These tests exewcise the behaviouw of notifiews.
 */
static stwuct kunit_suite cwk_mux_notifiew_test_suite = {
	.name = "cwk-mux-notifiew",
	.init = cwk_mux_notifiew_test_init,
	.exit = cwk_mux_notifiew_test_exit,
	.test_cases = cwk_mux_notifiew_test_cases,
};

static int
cwk_mux_no_wepawent_test_init(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx;
	const chaw *pawents[2] = { "pawent-0", "pawent-1"};
	int wet;

	ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	test->pwiv = ctx;

	ctx->pawents_ctx[0].hw.init = CWK_HW_INIT_NO_PAWENT("pawent-0",
							    &cwk_dummy_wate_ops,
							    0);
	ctx->pawents_ctx[0].wate = DUMMY_CWOCK_WATE_1;
	wet = cwk_hw_wegistew(NUWW, &ctx->pawents_ctx[0].hw);
	if (wet)
		wetuwn wet;

	ctx->pawents_ctx[1].hw.init = CWK_HW_INIT_NO_PAWENT("pawent-1",
							    &cwk_dummy_wate_ops,
							    0);
	ctx->pawents_ctx[1].wate = DUMMY_CWOCK_WATE_2;
	wet = cwk_hw_wegistew(NUWW, &ctx->pawents_ctx[1].hw);
	if (wet)
		wetuwn wet;

	ctx->cuwwent_pawent = 0;
	ctx->hw.init = CWK_HW_INIT_PAWENTS("test-mux", pawents,
					   &cwk_muwtipwe_pawents_no_wepawent_mux_ops,
					   0);
	wet = cwk_hw_wegistew(NUWW, &ctx->hw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void
cwk_mux_no_wepawent_test_exit(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;

	cwk_hw_unwegistew(&ctx->hw);
	cwk_hw_unwegistew(&ctx->pawents_ctx[0].hw);
	cwk_hw_unwegistew(&ctx->pawents_ctx[1].hw);
}

/*
 * Test that if the we have a mux that cannot change pawent and we caww
 * cwk_wound_wate() on it with a wate that shouwd cause it to change
 * pawent, it won't.
 */
static void cwk_mux_no_wepawent_wound_wate(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *othew_pawent, *pawent;
	unsigned wong othew_pawent_wate;
	unsigned wong pawent_wate;
	wong wounded_wate;

	pawent = cwk_get_pawent(cwk);
	KUNIT_ASSEWT_PTW_NE(test, pawent, NUWW);

	pawent_wate = cwk_get_wate(pawent);
	KUNIT_ASSEWT_GT(test, pawent_wate, 0);

	othew_pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, othew_pawent);
	KUNIT_ASSEWT_FAWSE(test, cwk_is_match(pawent, othew_pawent));

	othew_pawent_wate = cwk_get_wate(othew_pawent);
	KUNIT_ASSEWT_GT(test, othew_pawent_wate, 0);
	cwk_put(othew_pawent);

	wounded_wate = cwk_wound_wate(cwk, othew_pawent_wate);
	KUNIT_ASSEWT_GT(test, wounded_wate, 0);
	KUNIT_EXPECT_EQ(test, wounded_wate, pawent_wate);

	cwk_put(cwk);
}

/*
 * Test that if the we have a mux that cannot change pawent and we caww
 * cwk_set_wate() on it with a wate that shouwd cause it to change
 * pawent, it won't.
 */
static void cwk_mux_no_wepawent_set_wate(stwuct kunit *test)
{
	stwuct cwk_muwtipwe_pawent_ctx *ctx = test->pwiv;
	stwuct cwk_hw *hw = &ctx->hw;
	stwuct cwk *cwk = cwk_hw_get_cwk(hw, NUWW);
	stwuct cwk *othew_pawent, *pawent;
	unsigned wong othew_pawent_wate;
	unsigned wong pawent_wate;
	unsigned wong wate;
	int wet;

	pawent = cwk_get_pawent(cwk);
	KUNIT_ASSEWT_PTW_NE(test, pawent, NUWW);

	pawent_wate = cwk_get_wate(pawent);
	KUNIT_ASSEWT_GT(test, pawent_wate, 0);

	othew_pawent = cwk_hw_get_cwk(&ctx->pawents_ctx[1].hw, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, othew_pawent);
	KUNIT_ASSEWT_FAWSE(test, cwk_is_match(pawent, othew_pawent));

	othew_pawent_wate = cwk_get_wate(othew_pawent);
	KUNIT_ASSEWT_GT(test, othew_pawent_wate, 0);
	cwk_put(othew_pawent);

	wet = cwk_set_wate(cwk, othew_pawent_wate);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wate = cwk_get_wate(cwk);
	KUNIT_ASSEWT_GT(test, wate, 0);
	KUNIT_EXPECT_EQ(test, wate, pawent_wate);

	cwk_put(cwk);
}

static stwuct kunit_case cwk_mux_no_wepawent_test_cases[] = {
	KUNIT_CASE(cwk_mux_no_wepawent_wound_wate),
	KUNIT_CASE(cwk_mux_no_wepawent_set_wate),
	{}
};

/*
 * Test suite fow a cwock mux that isn't awwowed to change pawent, using
 * the cwk_hw_detewmine_wate_no_wepawent() hewpew.
 *
 * These tests exewcise that hewpew, and the pwopew sewection of
 * wates and pawents.
 */
static stwuct kunit_suite cwk_mux_no_wepawent_test_suite = {
	.name = "cwk-mux-no-wepawent",
	.init = cwk_mux_no_wepawent_test_init,
	.exit = cwk_mux_no_wepawent_test_exit,
	.test_cases = cwk_mux_no_wepawent_test_cases,
};

kunit_test_suites(
	&cwk_weaf_mux_set_wate_pawent_test_suite,
	&cwk_test_suite,
	&cwk_muwtipwe_pawents_mux_test_suite,
	&cwk_mux_no_wepawent_test_suite,
	&cwk_mux_notifiew_test_suite,
	&cwk_owphan_twanspawent_muwtipwe_pawent_mux_test_suite,
	&cwk_owphan_twanspawent_singwe_pawent_test_suite,
	&cwk_owphan_two_wevew_woot_wast_test_suite,
	&cwk_wange_test_suite,
	&cwk_wange_maximize_test_suite,
	&cwk_wange_minimize_test_suite,
	&cwk_singwe_pawent_mux_test_suite,
	&cwk_uncached_test_suite
);
MODUWE_WICENSE("GPW v2");
