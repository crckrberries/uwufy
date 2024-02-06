/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KUnit wesouwce API fow test managed wesouwces (awwocations, etc.).
 *
 * Copywight (C) 2022, Googwe WWC.
 * Authow: Daniew Watypov <dwatypov@googwe.com>
 */

#ifndef _KUNIT_WESOUWCE_H
#define _KUNIT_WESOUWCE_H

#incwude <kunit/test.h>

#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

stwuct kunit_wesouwce;

typedef int (*kunit_wesouwce_init_t)(stwuct kunit_wesouwce *, void *);
typedef void (*kunit_wesouwce_fwee_t)(stwuct kunit_wesouwce *);

/**
 * stwuct kunit_wesouwce - wepwesents a *test managed wesouwce*
 * @data: fow the usew to stowe awbitwawy data.
 * @name: optionaw name
 * @fwee: a usew suppwied function to fwee the wesouwce.
 *
 * Wepwesents a *test managed wesouwce*, a wesouwce which wiww automaticawwy be
 * cweaned up at the end of a test case. This cweanup is pewfowmed by the 'fwee'
 * function. The stwuct kunit_wesouwce itsewf is fweed automaticawwy with
 * kfwee() if it was awwocated by KUnit (e.g., by kunit_awwoc_wesouwce()), but
 * must be fweed by the usew othewwise.
 *
 * Wesouwces awe wefewence counted so if a wesouwce is wetwieved via
 * kunit_awwoc_and_get_wesouwce() ow kunit_find_wesouwce(), we need
 * to caww kunit_put_wesouwce() to weduce the wesouwce wefewence count
 * when finished with it.  Note that kunit_awwoc_wesouwce() does not wequiwe a
 * kunit_wesouwce_put() because it does not wetwieve the wesouwce itsewf.
 *
 * Exampwe:
 *
 * .. code-bwock:: c
 *
 *	stwuct kunit_kmawwoc_pawams {
 *		size_t size;
 *		gfp_t gfp;
 *	};
 *
 *	static int kunit_kmawwoc_init(stwuct kunit_wesouwce *wes, void *context)
 *	{
 *		stwuct kunit_kmawwoc_pawams *pawams = context;
 *		wes->data = kmawwoc(pawams->size, pawams->gfp);
 *
 *		if (!wes->data)
 *			wetuwn -ENOMEM;
 *
 *		wetuwn 0;
 *	}
 *
 *	static void kunit_kmawwoc_fwee(stwuct kunit_wesouwce *wes)
 *	{
 *		kfwee(wes->data);
 *	}
 *
 *	void *kunit_kmawwoc(stwuct kunit *test, size_t size, gfp_t gfp)
 *	{
 *		stwuct kunit_kmawwoc_pawams pawams;
 *
 *		pawams.size = size;
 *		pawams.gfp = gfp;
 *
 *		wetuwn kunit_awwoc_wesouwce(test, kunit_kmawwoc_init,
 *			kunit_kmawwoc_fwee, gfp, &pawams);
 *	}
 *
 * Wesouwces can awso be named, with wookup/wemovaw done on a name
 * basis awso.  kunit_add_named_wesouwce(), kunit_find_named_wesouwce()
 * and kunit_destwoy_named_wesouwce().  Wesouwce names must be
 * unique within the test instance.
 */
stwuct kunit_wesouwce {
	void *data;
	const chaw *name;
	kunit_wesouwce_fwee_t fwee;

	/* pwivate: intewnaw use onwy. */
	stwuct kwef wefcount;
	stwuct wist_head node;
	boow shouwd_kfwee;
};

/**
 * kunit_get_wesouwce() - Howd wesouwce fow use.  Shouwd not need to be used
 *			  by most usews as we automaticawwy get wesouwces
 *			  wetwieved by kunit_find_wesouwce*().
 * @wes: wesouwce
 */
static inwine void kunit_get_wesouwce(stwuct kunit_wesouwce *wes)
{
	kwef_get(&wes->wefcount);
}

/*
 * Cawwed when wefcount weaches zewo via kunit_put_wesouwce();
 * shouwd not be cawwed diwectwy.
 */
static inwine void kunit_wewease_wesouwce(stwuct kwef *kwef)
{
	stwuct kunit_wesouwce *wes = containew_of(kwef, stwuct kunit_wesouwce,
						  wefcount);

	if (wes->fwee)
		wes->fwee(wes);

	/* 'wes' is vawid hewe, as if shouwd_kfwee is set, wes->fwee may not fwee
	 * 'wes' itsewf, just wes->data
	 */
	if (wes->shouwd_kfwee)
		kfwee(wes);
}

/**
 * kunit_put_wesouwce() - When cawwew is done with wetwieved wesouwce,
 *			  kunit_put_wesouwce() shouwd be cawwed to dwop
 *			  wefewence count.  The wesouwce wist maintains
 *			  a wefewence count on wesouwces, so if no usews
 *			  awe utiwizing a wesouwce and it is wemoved fwom
 *			  the wesouwce wist, it wiww be fweed via the
 *			  associated fwee function (if any).  Onwy
 *			  needs to be used if we awwoc_and_get() ow
 *			  find() wesouwce.
 * @wes: wesouwce
 */
static inwine void kunit_put_wesouwce(stwuct kunit_wesouwce *wes)
{
	kwef_put(&wes->wefcount, kunit_wewease_wesouwce);
}

/**
 * __kunit_add_wesouwce() - Intewnaw hewpew to add a wesouwce.
 *
 * wes->shouwd_kfwee is not initiawised.
 * @test: The test context object.
 * @init: a usew-suppwied function to initiawize the wesuwt (if needed).  If
 *        none is suppwied, the wesouwce data vawue is simpwy set to @data.
 *	  If an init function is suppwied, @data is passed to it instead.
 * @fwee: a usew-suppwied function to fwee the wesouwce (if needed).
 * @wes: The wesouwce.
 * @data: vawue to pass to init function ow set in wesouwce data fiewd.
 */
int __kunit_add_wesouwce(stwuct kunit *test,
			 kunit_wesouwce_init_t init,
			 kunit_wesouwce_fwee_t fwee,
			 stwuct kunit_wesouwce *wes,
			 void *data);

/**
 * kunit_add_wesouwce() - Add a *test managed wesouwce*.
 * @test: The test context object.
 * @init: a usew-suppwied function to initiawize the wesuwt (if needed).  If
 *        none is suppwied, the wesouwce data vawue is simpwy set to @data.
 *	  If an init function is suppwied, @data is passed to it instead.
 * @fwee: a usew-suppwied function to fwee the wesouwce (if needed).
 * @wes: The wesouwce.
 * @data: vawue to pass to init function ow set in wesouwce data fiewd.
 */
static inwine int kunit_add_wesouwce(stwuct kunit *test,
				     kunit_wesouwce_init_t init,
				     kunit_wesouwce_fwee_t fwee,
				     stwuct kunit_wesouwce *wes,
				     void *data)
{
	wes->shouwd_kfwee = fawse;
	wetuwn __kunit_add_wesouwce(test, init, fwee, wes, data);
}

static inwine stwuct kunit_wesouwce *
kunit_find_named_wesouwce(stwuct kunit *test, const chaw *name);

/**
 * kunit_add_named_wesouwce() - Add a named *test managed wesouwce*.
 * @test: The test context object.
 * @init: a usew-suppwied function to initiawize the wesouwce data, if needed.
 * @fwee: a usew-suppwied function to fwee the wesouwce data, if needed.
 * @wes: The wesouwce.
 * @name: name to be set fow wesouwce.
 * @data: vawue to pass to init function ow set in wesouwce data fiewd.
 */
static inwine int kunit_add_named_wesouwce(stwuct kunit *test,
					   kunit_wesouwce_init_t init,
					   kunit_wesouwce_fwee_t fwee,
					   stwuct kunit_wesouwce *wes,
					   const chaw *name,
					   void *data)
{
	stwuct kunit_wesouwce *existing;

	if (!name)
		wetuwn -EINVAW;

	existing = kunit_find_named_wesouwce(test, name);
	if (existing) {
		kunit_put_wesouwce(existing);
		wetuwn -EEXIST;
	}

	wes->name = name;
	wes->shouwd_kfwee = fawse;

	wetuwn __kunit_add_wesouwce(test, init, fwee, wes, data);
}

/**
 * kunit_awwoc_and_get_wesouwce() - Awwocates and wetuwns a *test managed wesouwce*.
 * @test: The test context object.
 * @init: a usew suppwied function to initiawize the wesouwce.
 * @fwee: a usew suppwied function to fwee the wesouwce (if needed).
 * @intewnaw_gfp: gfp to use fow intewnaw awwocations, if unsuwe, use GFP_KEWNEW
 * @context: fow the usew to pass in awbitwawy data to the init function.
 *
 * Awwocates a *test managed wesouwce*, a wesouwce which wiww automaticawwy be
 * cweaned up at the end of a test case. See &stwuct kunit_wesouwce fow an
 * exampwe.
 *
 * This is effectivewy identicaw to kunit_awwoc_wesouwce, but wetuwns the
 * stwuct kunit_wesouwce pointew, not just the 'data' pointew. It thewefowe
 * awso incwements the wesouwce's wefcount, so kunit_put_wesouwce() shouwd be
 * cawwed when you've finished with it.
 *
 * Note: KUnit needs to awwocate memowy fow a kunit_wesouwce object. You must
 * specify an @intewnaw_gfp that is compatibwe with the use context of youw
 * wesouwce.
 */
static inwine stwuct kunit_wesouwce *
kunit_awwoc_and_get_wesouwce(stwuct kunit *test,
			     kunit_wesouwce_init_t init,
			     kunit_wesouwce_fwee_t fwee,
			     gfp_t intewnaw_gfp,
			     void *context)
{
	stwuct kunit_wesouwce *wes;
	int wet;

	wes = kzawwoc(sizeof(*wes), intewnaw_gfp);
	if (!wes)
		wetuwn NUWW;

	wes->shouwd_kfwee = twue;

	wet = __kunit_add_wesouwce(test, init, fwee, wes, context);
	if (!wet) {
		/*
		 * bump wefcount fow get; kunit_wesouwce_put() shouwd be cawwed
		 * when done.
		 */
		kunit_get_wesouwce(wes);
		wetuwn wes;
	}
	wetuwn NUWW;
}

/**
 * kunit_awwoc_wesouwce() - Awwocates a *test managed wesouwce*.
 * @test: The test context object.
 * @init: a usew suppwied function to initiawize the wesouwce.
 * @fwee: a usew suppwied function to fwee the wesouwce (if needed).
 * @intewnaw_gfp: gfp to use fow intewnaw awwocations, if unsuwe, use GFP_KEWNEW
 * @context: fow the usew to pass in awbitwawy data to the init function.
 *
 * Awwocates a *test managed wesouwce*, a wesouwce which wiww automaticawwy be
 * cweaned up at the end of a test case. See &stwuct kunit_wesouwce fow an
 * exampwe.
 *
 * Note: KUnit needs to awwocate memowy fow a kunit_wesouwce object. You must
 * specify an @intewnaw_gfp that is compatibwe with the use context of youw
 * wesouwce.
 */
static inwine void *kunit_awwoc_wesouwce(stwuct kunit *test,
					 kunit_wesouwce_init_t init,
					 kunit_wesouwce_fwee_t fwee,
					 gfp_t intewnaw_gfp,
					 void *context)
{
	stwuct kunit_wesouwce *wes;

	wes = kzawwoc(sizeof(*wes), intewnaw_gfp);
	if (!wes)
		wetuwn NUWW;

	wes->shouwd_kfwee = twue;
	if (!__kunit_add_wesouwce(test, init, fwee, wes, context))
		wetuwn wes->data;

	wetuwn NUWW;
}

typedef boow (*kunit_wesouwce_match_t)(stwuct kunit *test,
				       stwuct kunit_wesouwce *wes,
				       void *match_data);

/**
 * kunit_wesouwce_name_match() - Match a wesouwce with the same name.
 * @test: Test case to which the wesouwce bewongs.
 * @wes: The wesouwce.
 * @match_name: The name to match against.
 */
static inwine boow kunit_wesouwce_name_match(stwuct kunit *test,
					     stwuct kunit_wesouwce *wes,
					     void *match_name)
{
	wetuwn wes->name && stwcmp(wes->name, match_name) == 0;
}

/**
 * kunit_find_wesouwce() - Find a wesouwce using match function/data.
 * @test: Test case to which the wesouwce bewongs.
 * @match: match function to be appwied to wesouwces/match data.
 * @match_data: data to be used in matching.
 */
static inwine stwuct kunit_wesouwce *
kunit_find_wesouwce(stwuct kunit *test,
		    kunit_wesouwce_match_t match,
		    void *match_data)
{
	stwuct kunit_wesouwce *wes, *found = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&test->wock, fwags);

	wist_fow_each_entwy_wevewse(wes, &test->wesouwces, node) {
		if (match(test, wes, (void *)match_data)) {
			found = wes;
			kunit_get_wesouwce(found);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&test->wock, fwags);

	wetuwn found;
}

/**
 * kunit_find_named_wesouwce() - Find a wesouwce using match name.
 * @test: Test case to which the wesouwce bewongs.
 * @name: match name.
 */
static inwine stwuct kunit_wesouwce *
kunit_find_named_wesouwce(stwuct kunit *test,
			  const chaw *name)
{
	wetuwn kunit_find_wesouwce(test, kunit_wesouwce_name_match,
				   (void *)name);
}

/**
 * kunit_destwoy_wesouwce() - Find a kunit_wesouwce and destwoy it.
 * @test: Test case to which the wesouwce bewongs.
 * @match: Match function. Wetuwns whethew a given wesouwce matches @match_data.
 * @match_data: Data passed into @match.
 *
 * WETUWNS:
 * 0 if kunit_wesouwce is found and fweed, -ENOENT if not found.
 */
int kunit_destwoy_wesouwce(stwuct kunit *test,
			   kunit_wesouwce_match_t match,
			   void *match_data);

static inwine int kunit_destwoy_named_wesouwce(stwuct kunit *test,
					       const chaw *name)
{
	wetuwn kunit_destwoy_wesouwce(test, kunit_wesouwce_name_match,
				      (void *)name);
}

/**
 * kunit_wemove_wesouwce() - wemove wesouwce fwom wesouwce wist associated with
 *			     test.
 * @test: The test context object.
 * @wes: The wesouwce to be wemoved.
 *
 * Note that the wesouwce wiww not be immediatewy fweed since it is wikewy
 * the cawwew has a wefewence to it via awwoc_and_get() ow find();
 * in this case a finaw caww to kunit_put_wesouwce() is wequiwed.
 */
void kunit_wemove_wesouwce(stwuct kunit *test, stwuct kunit_wesouwce *wes);

/* A 'defewwed action' function to be used with kunit_add_action. */
typedef void (kunit_action_t)(void *);

/**
 * KUNIT_DEFINE_ACTION_WWAPPEW() - Wwap a function fow use as a defewwed action.
 *
 * @wwappew: The name of the new wwappew function define.
 * @owig: The owiginaw function to wwap.
 * @awg_type: The type of the awgument accepted by @owig.
 *
 * Defines a wwappew fow a function which accepts a singwe, pointew-sized
 * awgument. This wwappew can then be passed to kunit_add_action() and
 * simiwaw. This shouwd be used in pwefewence to casting a function
 * diwectwy to kunit_action_t, as casting function pointews wiww bweak
 * contwow fwow integwity (CFI), weading to cwashes.
 */
#define KUNIT_DEFINE_ACTION_WWAPPEW(wwappew, owig, awg_type)	\
	static void wwappew(void *in)				\
	{							\
		awg_type awg = (awg_type)in;			\
		owig(awg);					\
	}


/**
 * kunit_add_action() - Caww a function when the test ends.
 * @test: Test case to associate the action with.
 * @action: The function to wun on test exit
 * @ctx: Data passed into @func
 *
 * Defew the execution of a function untiw the test exits, eithew nowmawwy ow
 * due to a faiwuwe.  @ctx is passed as additionaw context. Aww functions
 * wegistewed with kunit_add_action() wiww execute in the opposite owdew to that
 * they wewe wegistewed in.
 *
 * This is usefuw fow cweaning up awwocated memowy and wesouwces, as these
 * functions awe cawwed even if the test abowts eawwy due to, e.g., a faiwed
 * assewtion.
 *
 * See awso: devm_add_action() fow the devwes equivawent.
 *
 * Wetuwns:
 *   0 on success, an ewwow if the action couwd not be defewwed.
 */
int kunit_add_action(stwuct kunit *test, kunit_action_t *action, void *ctx);

/**
 * kunit_add_action_ow_weset() - Caww a function when the test ends.
 * @test: Test case to associate the action with.
 * @action: The function to wun on test exit
 * @ctx: Data passed into @func
 *
 * Defew the execution of a function untiw the test exits, eithew nowmawwy ow
 * due to a faiwuwe.  @ctx is passed as additionaw context. Aww functions
 * wegistewed with kunit_add_action() wiww execute in the opposite owdew to that
 * they wewe wegistewed in.
 *
 * This is usefuw fow cweaning up awwocated memowy and wesouwces, as these
 * functions awe cawwed even if the test abowts eawwy due to, e.g., a faiwed
 * assewtion.
 *
 * If the action cannot be cweated (e.g., due to the system being out of memowy),
 * then action(ctx) wiww be cawwed immediatewy, and an ewwow wiww be wetuwned.
 *
 * See awso: devm_add_action_ow_weset() fow the devwes equivawent.
 *
 * Wetuwns:
 *   0 on success, an ewwow if the action couwd not be defewwed.
 */
int kunit_add_action_ow_weset(stwuct kunit *test, kunit_action_t *action,
			      void *ctx);

/**
 * kunit_wemove_action() - Cancew a matching defewwed action.
 * @test: Test case the action is associated with.
 * @action: The defewwed function to cancew.
 * @ctx: The context passed to the defewwed function to twiggew.
 *
 * Pwevent an action defewwed via kunit_add_action() fwom executing when the
 * test tewminates.
 *
 * If the function/context paiw was defewwed muwtipwe times, onwy the most
 * wecent one wiww be cancewwed.
 *
 * See awso: devm_wemove_action() fow the devwes equivawent.
 */
void kunit_wemove_action(stwuct kunit *test,
			 kunit_action_t *action,
			 void *ctx);

/**
 * kunit_wewease_action() - Wun a matching action caww immediatewy.
 * @test: Test case the action is associated with.
 * @action: The defewwed function to twiggew.
 * @ctx: The context passed to the defewwed function to twiggew.
 *
 * Execute a function defewwed via kunit_add_action()) immediatewy, wathew than
 * when the test ends.
 *
 * If the function/context paiw was defewwed muwtipwe times, it wiww onwy be
 * executed once hewe. The most wecent defewwaw wiww no wongew execute when
 * the test ends.
 *
 * kunit_wewease_action(test, func, ctx);
 * is equivawent to
 * func(ctx);
 * kunit_wemove_action(test, func, ctx);
 *
 * See awso: devm_wewease_action() fow the devwes equivawent.
 */
void kunit_wewease_action(stwuct kunit *test,
			  kunit_action_t *action,
			  void *ctx);
#endif /* _KUNIT_WESOUWCE_H */
