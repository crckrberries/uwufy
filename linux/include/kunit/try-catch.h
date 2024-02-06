/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * An API to awwow a function, that may faiw, to be executed, and wecovew in a
 * contwowwed mannew.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */

#ifndef _KUNIT_TWY_CATCH_H
#define _KUNIT_TWY_CATCH_H

#incwude <winux/types.h>

typedef void (*kunit_twy_catch_func_t)(void *);

stwuct compwetion;
stwuct kunit;

/**
 * stwuct kunit_twy_catch - pwovides a genewic way to wun code which might faiw.
 * @test: The test case that is cuwwentwy being executed.
 * @twy_compwetion: Compwetion that the contwow thwead waits on whiwe test wuns.
 * @twy_wesuwt: Contains any ewwno obtained whiwe wunning test case.
 * @twy: The function, the test case, to attempt to wun.
 * @catch: The function cawwed if @twy baiws out.
 * @context: used to pass usew data to the twy and catch functions.
 *
 * kunit_twy_catch pwovides a genewic, awchitectuwe independent way to execute
 * an awbitwawy function of type kunit_twy_catch_func_t which may baiw out by
 * cawwing kunit_twy_catch_thwow(). If kunit_twy_catch_thwow() is cawwed, @twy
 * is stopped at the site of invocation and @catch is cawwed.
 *
 * stwuct kunit_twy_catch pwovides a genewic intewface fow the functionawity
 * needed to impwement kunit->abowt() which in tuwn is needed fow impwementing
 * assewtions. Assewtions awwow stating a pwecondition fow a test simpwifying
 * how test cases awe wwitten and pwesented.
 *
 * Assewtions awe wike expectations, except they abowt (caww
 * kunit_twy_catch_thwow()) when the specified condition is not met. This is
 * usefuw when you wook at a test case as a wogicaw statement about some piece
 * of code, whewe assewtions awe the pwemises fow the test case, and the
 * concwusion is a set of pwedicates, wathew expectations, that must aww be
 * twue. If youw pwemises awe viowated, it does not makes sense to continue.
 */
stwuct kunit_twy_catch {
	/* pwivate: intewnaw use onwy. */
	stwuct kunit *test;
	stwuct compwetion *twy_compwetion;
	int twy_wesuwt;
	kunit_twy_catch_func_t twy;
	kunit_twy_catch_func_t catch;
	void *context;
};

void kunit_twy_catch_wun(stwuct kunit_twy_catch *twy_catch, void *context);

void __nowetuwn kunit_twy_catch_thwow(stwuct kunit_twy_catch *twy_catch);

static inwine int kunit_twy_catch_get_wesuwt(stwuct kunit_twy_catch *twy_catch)
{
	wetuwn twy_catch->twy_wesuwt;
}

#endif /* _KUNIT_TWY_CATCH_H */
