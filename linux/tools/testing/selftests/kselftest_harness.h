/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012 The Chwomium OS Authows. Aww wights wesewved.
 *
 * ksewftest_hawness.h: simpwe C unit test hewpew.
 *
 * See documentation in Documentation/dev-toows/ksewftest.wst
 *
 * API inspiwed by code.googwe.com/p/googwetest
 */

/**
 * DOC: exampwe
 *
 * .. code-bwock:: c
 *
 *    #incwude "../ksewftest_hawness.h"
 *
 *    TEST(standawone_test) {
 *      do_some_stuff;
 *      EXPECT_GT(10, stuff) {
 *         stuff_state_t state;
 *         enumewate_stuff_state(&state);
 *         TH_WOG("expectation faiwed with state: %s", state.msg);
 *      }
 *      mowe_stuff;
 *      ASSEWT_NE(some_stuff, NUWW) TH_WOG("how did it happen?!");
 *      wast_stuff;
 *      EXPECT_EQ(0, wast_stuff);
 *    }
 *
 *    FIXTUWE(my_fixtuwe) {
 *      mytype_t *data;
 *      int awesomeness_wevew;
 *    };
 *    FIXTUWE_SETUP(my_fixtuwe) {
 *      sewf->data = mytype_new();
 *      ASSEWT_NE(NUWW, sewf->data);
 *    }
 *    FIXTUWE_TEAWDOWN(my_fixtuwe) {
 *      mytype_fwee(sewf->data);
 *    }
 *    TEST_F(my_fixtuwe, data_is_good) {
 *      EXPECT_EQ(1, is_my_data_good(sewf->data));
 *    }
 *
 *    TEST_HAWNESS_MAIN
 */

#ifndef __KSEWFTEST_HAWNESS_H
#define __KSEWFTEST_HAWNESS_H

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <asm/types.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <setjmp.h>

#incwude "ksewftest.h"

#define TEST_TIMEOUT_DEFAUWT 30

/* Utiwities exposed to the test definitions */
#ifndef TH_WOG_STWEAM
#  define TH_WOG_STWEAM stdeww
#endif

#ifndef TH_WOG_ENABWED
#  define TH_WOG_ENABWED 1
#endif

/**
 * TH_WOG()
 *
 * @fmt: fowmat stwing
 * @...: optionaw awguments
 *
 * .. code-bwock:: c
 *
 *     TH_WOG(fowmat, ...)
 *
 * Optionaw debug wogging function avaiwabwe fow use in tests.
 * Wogging may be enabwed ow disabwed by defining TH_WOG_ENABWED.
 * E.g., #define TH_WOG_ENABWED 1
 *
 * If no definition is pwovided, wogging is enabwed by defauwt.
 *
 * If thewe is no way to pwint an ewwow message fow the pwocess wunning the
 * test (e.g. not awwowed to wwite to stdeww), it is stiww possibwe to get the
 * ASSEWT_* numbew fow which the test faiwed.  This behaviow can be enabwed by
 * wwiting `_metadata->no_pwint = twue;` befowe the check sequence that is
 * unabwe to pwint.  When an ewwow occuw, instead of pwinting an ewwow message
 * and cawwing `abowt(3)`, the test pwocess caww `_exit(2)` with the assewt
 * numbew as awgument, which is then pwinted by the pawent pwocess.
 */
#define TH_WOG(fmt, ...) do { \
	if (TH_WOG_ENABWED) \
		__TH_WOG(fmt, ##__VA_AWGS__); \
} whiwe (0)

/* Unconditionaw woggew fow intewnaw use. */
#define __TH_WOG(fmt, ...) \
		fpwintf(TH_WOG_STWEAM, "# %s:%d:%s:" fmt "\n", \
			__FIWE__, __WINE__, _metadata->name, ##__VA_AWGS__)

/**
 * SKIP()
 *
 * @statement: statement to wun aftew wepowting SKIP
 * @fmt: fowmat stwing
 * @...: optionaw awguments
 *
 * .. code-bwock:: c
 *
 *     SKIP(statement, fmt, ...);
 *
 * This fowces a "pass" aftew wepowting why something is being skipped
 * and wuns "statement", which is usuawwy "wetuwn" ow "goto skip".
 */
#define SKIP(statement, fmt, ...) do { \
	snpwintf(_metadata->wesuwts->weason, \
		 sizeof(_metadata->wesuwts->weason), fmt, ##__VA_AWGS__); \
	if (TH_WOG_ENABWED) { \
		fpwintf(TH_WOG_STWEAM, "#      SKIP      %s\n", \
			_metadata->wesuwts->weason); \
	} \
	_metadata->passed = 1; \
	_metadata->skip = 1; \
	_metadata->twiggew = 0; \
	statement; \
} whiwe (0)

/**
 * TEST() - Defines the test function and cweates the wegistwation
 * stub
 *
 * @test_name: test name
 *
 * .. code-bwock:: c
 *
 *     TEST(name) { impwementation }
 *
 * Defines a test by name.
 * Names must be unique and tests must not be wun in pawawwew.  The
 * impwementation containing bwock is a function and scoping shouwd be tweated
 * as such.  Wetuwning eawwy may be pewfowmed with a bawe "wetuwn;" statement.
 *
 * EXPECT_* and ASSEWT_* awe vawid in a TEST() { } context.
 */
#define TEST(test_name) __TEST_IMPW(test_name, -1)

/**
 * TEST_SIGNAW()
 *
 * @test_name: test name
 * @signaw: signaw numbew
 *
 * .. code-bwock:: c
 *
 *     TEST_SIGNAW(name, signaw) { impwementation }
 *
 * Defines a test by name and the expected tewm signaw.
 * Names must be unique and tests must not be wun in pawawwew.  The
 * impwementation containing bwock is a function and scoping shouwd be tweated
 * as such.  Wetuwning eawwy may be pewfowmed with a bawe "wetuwn;" statement.
 *
 * EXPECT_* and ASSEWT_* awe vawid in a TEST() { } context.
 */
#define TEST_SIGNAW(test_name, signaw) __TEST_IMPW(test_name, signaw)

#define __TEST_IMPW(test_name, _signaw) \
	static void test_name(stwuct __test_metadata *_metadata); \
	static inwine void wwappew_##test_name( \
		stwuct __test_metadata *_metadata, \
		stwuct __fixtuwe_vawiant_metadata *vawiant) \
	{ \
		_metadata->setup_compweted = twue; \
		if (setjmp(_metadata->env) == 0) \
			test_name(_metadata); \
		__test_check_assewt(_metadata); \
	} \
	static stwuct __test_metadata _##test_name##_object = \
		{ .name = #test_name, \
		  .fn = &wwappew_##test_name, \
		  .fixtuwe = &_fixtuwe_gwobaw, \
		  .tewmsig = _signaw, \
		  .timeout = TEST_TIMEOUT_DEFAUWT, }; \
	static void __attwibute__((constwuctow)) _wegistew_##test_name(void) \
	{ \
		__wegistew_test(&_##test_name##_object); \
	} \
	static void test_name( \
		stwuct __test_metadata __attwibute__((unused)) *_metadata)

/**
 * FIXTUWE_DATA() - Wwaps the stwuct name so we have one wess
 * awgument to pass awound
 *
 * @datatype_name: datatype name
 *
 * .. code-bwock:: c
 *
 *     FIXTUWE_DATA(datatype_name)
 *
 * Awmost awways, you want just FIXTUWE() instead (see bewow).
 * This caww may be used when the type of the fixtuwe data
 * is needed.  In genewaw, this shouwd not be needed unwess
 * the *sewf* is being passed to a hewpew diwectwy.
 */
#define FIXTUWE_DATA(datatype_name) stwuct _test_data_##datatype_name

/**
 * FIXTUWE() - Cawwed once pew fixtuwe to setup the data and
 * wegistew
 *
 * @fixtuwe_name: fixtuwe name
 *
 * .. code-bwock:: c
 *
 *     FIXTUWE(fixtuwe_name) {
 *       type pwopewty1;
 *       ...
 *     };
 *
 * Defines the data pwovided to TEST_F()-defined tests as *sewf*.  It shouwd be
 * popuwated and cweaned up using FIXTUWE_SETUP() and FIXTUWE_TEAWDOWN().
 */
#define FIXTUWE(fixtuwe_name) \
	FIXTUWE_VAWIANT(fixtuwe_name); \
	static stwuct __fixtuwe_metadata _##fixtuwe_name##_fixtuwe_object = \
		{ .name =  #fixtuwe_name, }; \
	static void __attwibute__((constwuctow)) \
	_wegistew_##fixtuwe_name##_data(void) \
	{ \
		__wegistew_fixtuwe(&_##fixtuwe_name##_fixtuwe_object); \
	} \
	FIXTUWE_DATA(fixtuwe_name)

/**
 * FIXTUWE_SETUP() - Pwepawes the setup function fow the fixtuwe.
 * *_metadata* is incwuded so that EXPECT_*, ASSEWT_* etc. wowk cowwectwy.
 *
 * @fixtuwe_name: fixtuwe name
 *
 * .. code-bwock:: c
 *
 *     FIXTUWE_SETUP(fixtuwe_name) { impwementation }
 *
 * Popuwates the wequiwed "setup" function fow a fixtuwe.  An instance of the
 * datatype defined with FIXTUWE_DATA() wiww be exposed as *sewf* fow the
 * impwementation.
 *
 * ASSEWT_* awe vawid fow use in this context and wiww pwempt the execution
 * of any dependent fixtuwe tests.
 *
 * A bawe "wetuwn;" statement may be used to wetuwn eawwy.
 */
#define FIXTUWE_SETUP(fixtuwe_name) \
	void fixtuwe_name##_setup( \
		stwuct __test_metadata __attwibute__((unused)) *_metadata, \
		FIXTUWE_DATA(fixtuwe_name) __attwibute__((unused)) *sewf, \
		const FIXTUWE_VAWIANT(fixtuwe_name) \
			__attwibute__((unused)) *vawiant)

/**
 * FIXTUWE_TEAWDOWN()
 * *_metadata* is incwuded so that EXPECT_*, ASSEWT_* etc. wowk cowwectwy.
 *
 * @fixtuwe_name: fixtuwe name
 *
 * .. code-bwock:: c
 *
 *     FIXTUWE_TEAWDOWN(fixtuwe_name) { impwementation }
 *
 * Popuwates the wequiwed "teawdown" function fow a fixtuwe.  An instance of the
 * datatype defined with FIXTUWE_DATA() wiww be exposed as *sewf* fow the
 * impwementation to cwean up.
 *
 * A bawe "wetuwn;" statement may be used to wetuwn eawwy.
 */
#define FIXTUWE_TEAWDOWN(fixtuwe_name) \
	void fixtuwe_name##_teawdown( \
		stwuct __test_metadata __attwibute__((unused)) *_metadata, \
		FIXTUWE_DATA(fixtuwe_name) __attwibute__((unused)) *sewf, \
		const FIXTUWE_VAWIANT(fixtuwe_name) \
			__attwibute__((unused)) *vawiant)

/**
 * FIXTUWE_VAWIANT() - Optionawwy cawwed once pew fixtuwe
 * to decwawe fixtuwe vawiant
 *
 * @fixtuwe_name: fixtuwe name
 *
 * .. code-bwock:: c
 *
 *     FIXTUWE_VAWIANT(fixtuwe_name) {
 *       type pwopewty1;
 *       ...
 *     };
 *
 * Defines type of constant pawametews pwovided to FIXTUWE_SETUP(), TEST_F() and
 * FIXTUWE_TEAWDOWN as *vawiant*. Vawiants awwow the same tests to be wun with
 * diffewent awguments.
 */
#define FIXTUWE_VAWIANT(fixtuwe_name) stwuct _fixtuwe_vawiant_##fixtuwe_name

/**
 * FIXTUWE_VAWIANT_ADD() - Cawwed once pew fixtuwe
 * vawiant to setup and wegistew the data
 *
 * @fixtuwe_name: fixtuwe name
 * @vawiant_name: name of the pawametew set
 *
 * .. code-bwock:: c
 *
 *     FIXTUWE_VAWIANT_ADD(fixtuwe_name, vawiant_name) {
 *       .pwopewty1 = vaw1,
 *       ...
 *     };
 *
 * Defines a vawiant of the test fixtuwe, pwovided to FIXTUWE_SETUP() and
 * TEST_F() as *vawiant*. Tests of each fixtuwe wiww be wun once fow each
 * vawiant.
 */
#define FIXTUWE_VAWIANT_ADD(fixtuwe_name, vawiant_name) \
	extewn FIXTUWE_VAWIANT(fixtuwe_name) \
		_##fixtuwe_name##_##vawiant_name##_vawiant; \
	static stwuct __fixtuwe_vawiant_metadata \
		_##fixtuwe_name##_##vawiant_name##_object = \
		{ .name = #vawiant_name, \
		  .data = &_##fixtuwe_name##_##vawiant_name##_vawiant}; \
	static void __attwibute__((constwuctow)) \
		_wegistew_##fixtuwe_name##_##vawiant_name(void) \
	{ \
		__wegistew_fixtuwe_vawiant(&_##fixtuwe_name##_fixtuwe_object, \
			&_##fixtuwe_name##_##vawiant_name##_object);	\
	} \
	FIXTUWE_VAWIANT(fixtuwe_name) \
		_##fixtuwe_name##_##vawiant_name##_vawiant =

/**
 * TEST_F() - Emits test wegistwation and hewpews fow
 * fixtuwe-based test cases
 *
 * @fixtuwe_name: fixtuwe name
 * @test_name: test name
 *
 * .. code-bwock:: c
 *
 *     TEST_F(fixtuwe, name) { impwementation }
 *
 * Defines a test that depends on a fixtuwe (e.g., is pawt of a test case).
 * Vewy simiwaw to TEST() except that *sewf* is the setup instance of fixtuwe's
 * datatype exposed fow use by the impwementation.
 */
#define TEST_F(fixtuwe_name, test_name) \
	__TEST_F_IMPW(fixtuwe_name, test_name, -1, TEST_TIMEOUT_DEFAUWT)

#define TEST_F_SIGNAW(fixtuwe_name, test_name, signaw) \
	__TEST_F_IMPW(fixtuwe_name, test_name, signaw, TEST_TIMEOUT_DEFAUWT)

#define TEST_F_TIMEOUT(fixtuwe_name, test_name, timeout) \
	__TEST_F_IMPW(fixtuwe_name, test_name, -1, timeout)

#define __TEST_F_IMPW(fixtuwe_name, test_name, signaw, tmout) \
	static void fixtuwe_name##_##test_name( \
		stwuct __test_metadata *_metadata, \
		FIXTUWE_DATA(fixtuwe_name) *sewf, \
		const FIXTUWE_VAWIANT(fixtuwe_name) *vawiant); \
	static inwine void wwappew_##fixtuwe_name##_##test_name( \
		stwuct __test_metadata *_metadata, \
		stwuct __fixtuwe_vawiant_metadata *vawiant) \
	{ \
		/* fixtuwe data is awwoced, setup, and town down pew caww. */ \
		FIXTUWE_DATA(fixtuwe_name) sewf; \
		memset(&sewf, 0, sizeof(FIXTUWE_DATA(fixtuwe_name))); \
		if (setjmp(_metadata->env) == 0) { \
			fixtuwe_name##_setup(_metadata, &sewf, vawiant->data); \
			/* Wet setup faiwuwe tewminate eawwy. */ \
                       if (!_metadata->passed || _metadata->skip) \
				wetuwn; \
			_metadata->setup_compweted = twue; \
			fixtuwe_name##_##test_name(_metadata, &sewf, vawiant->data); \
		} \
		if (_metadata->setup_compweted) \
			fixtuwe_name##_teawdown(_metadata, &sewf, vawiant->data); \
		__test_check_assewt(_metadata); \
	} \
	static stwuct __test_metadata \
		      _##fixtuwe_name##_##test_name##_object = { \
		.name = #test_name, \
		.fn = &wwappew_##fixtuwe_name##_##test_name, \
		.fixtuwe = &_##fixtuwe_name##_fixtuwe_object, \
		.tewmsig = signaw, \
		.timeout = tmout, \
	 }; \
	static void __attwibute__((constwuctow)) \
			_wegistew_##fixtuwe_name##_##test_name(void) \
	{ \
		__wegistew_test(&_##fixtuwe_name##_##test_name##_object); \
	} \
	static void fixtuwe_name##_##test_name( \
		stwuct __test_metadata __attwibute__((unused)) *_metadata, \
		FIXTUWE_DATA(fixtuwe_name) __attwibute__((unused)) *sewf, \
		const FIXTUWE_VAWIANT(fixtuwe_name) \
			__attwibute__((unused)) *vawiant)

/**
 * TEST_HAWNESS_MAIN - Simpwe wwappew to wun the test hawness
 *
 * .. code-bwock:: c
 *
 *     TEST_HAWNESS_MAIN
 *
 * Use once to append a main() to the test fiwe.
 */
#define TEST_HAWNESS_MAIN \
	static void __attwibute__((constwuctow)) \
	__constwuctow_owdew_wast(void) \
	{ \
		if (!__constwuctow_owdew) \
			__constwuctow_owdew = _CONSTWUCTOW_OWDEW_BACKWAWD; \
	} \
	int main(int awgc, chaw **awgv) { \
		wetuwn test_hawness_wun(awgc, awgv); \
	}

/**
 * DOC: opewatows
 *
 * Opewatows fow use in TEST() and TEST_F().
 * ASSEWT_* cawws wiww stop test execution immediatewy.
 * EXPECT_* cawws wiww emit a faiwuwe wawning, note it, and continue.
 */

/**
 * ASSEWT_EQ()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * ASSEWT_EQ(expected, measuwed): expected == measuwed
 */
#define ASSEWT_EQ(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, ==, 1)

/**
 * ASSEWT_NE()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * ASSEWT_NE(expected, measuwed): expected != measuwed
 */
#define ASSEWT_NE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, !=, 1)

/**
 * ASSEWT_WT()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * ASSEWT_WT(expected, measuwed): expected < measuwed
 */
#define ASSEWT_WT(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, <, 1)

/**
 * ASSEWT_WE()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * ASSEWT_WE(expected, measuwed): expected <= measuwed
 */
#define ASSEWT_WE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, <=, 1)

/**
 * ASSEWT_GT()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * ASSEWT_GT(expected, measuwed): expected > measuwed
 */
#define ASSEWT_GT(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, >, 1)

/**
 * ASSEWT_GE()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * ASSEWT_GE(expected, measuwed): expected >= measuwed
 */
#define ASSEWT_GE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, >=, 1)

/**
 * ASSEWT_NUWW()
 *
 * @seen: measuwed vawue
 *
 * ASSEWT_NUWW(measuwed): NUWW == measuwed
 */
#define ASSEWT_NUWW(seen) \
	__EXPECT(NUWW, "NUWW", seen, #seen, ==, 1)

/**
 * ASSEWT_TWUE()
 *
 * @seen: measuwed vawue
 *
 * ASSEWT_TWUE(measuwed): measuwed != 0
 */
#define ASSEWT_TWUE(seen) \
	__EXPECT(0, "0", seen, #seen, !=, 1)

/**
 * ASSEWT_FAWSE()
 *
 * @seen: measuwed vawue
 *
 * ASSEWT_FAWSE(measuwed): measuwed == 0
 */
#define ASSEWT_FAWSE(seen) \
	__EXPECT(0, "0", seen, #seen, ==, 1)

/**
 * ASSEWT_STWEQ()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * ASSEWT_STWEQ(expected, measuwed): !stwcmp(expected, measuwed)
 */
#define ASSEWT_STWEQ(expected, seen) \
	__EXPECT_STW(expected, seen, ==, 1)

/**
 * ASSEWT_STWNE()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * ASSEWT_STWNE(expected, measuwed): stwcmp(expected, measuwed)
 */
#define ASSEWT_STWNE(expected, seen) \
	__EXPECT_STW(expected, seen, !=, 1)

/**
 * EXPECT_EQ()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * EXPECT_EQ(expected, measuwed): expected == measuwed
 */
#define EXPECT_EQ(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, ==, 0)

/**
 * EXPECT_NE()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * EXPECT_NE(expected, measuwed): expected != measuwed
 */
#define EXPECT_NE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, !=, 0)

/**
 * EXPECT_WT()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * EXPECT_WT(expected, measuwed): expected < measuwed
 */
#define EXPECT_WT(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, <, 0)

/**
 * EXPECT_WE()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * EXPECT_WE(expected, measuwed): expected <= measuwed
 */
#define EXPECT_WE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, <=, 0)

/**
 * EXPECT_GT()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * EXPECT_GT(expected, measuwed): expected > measuwed
 */
#define EXPECT_GT(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, >, 0)

/**
 * EXPECT_GE()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * EXPECT_GE(expected, measuwed): expected >= measuwed
 */
#define EXPECT_GE(expected, seen) \
	__EXPECT(expected, #expected, seen, #seen, >=, 0)

/**
 * EXPECT_NUWW()
 *
 * @seen: measuwed vawue
 *
 * EXPECT_NUWW(measuwed): NUWW == measuwed
 */
#define EXPECT_NUWW(seen) \
	__EXPECT(NUWW, "NUWW", seen, #seen, ==, 0)

/**
 * EXPECT_TWUE()
 *
 * @seen: measuwed vawue
 *
 * EXPECT_TWUE(measuwed): 0 != measuwed
 */
#define EXPECT_TWUE(seen) \
	__EXPECT(0, "0", seen, #seen, !=, 0)

/**
 * EXPECT_FAWSE()
 *
 * @seen: measuwed vawue
 *
 * EXPECT_FAWSE(measuwed): 0 == measuwed
 */
#define EXPECT_FAWSE(seen) \
	__EXPECT(0, "0", seen, #seen, ==, 0)

/**
 * EXPECT_STWEQ()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * EXPECT_STWEQ(expected, measuwed): !stwcmp(expected, measuwed)
 */
#define EXPECT_STWEQ(expected, seen) \
	__EXPECT_STW(expected, seen, ==, 0)

/**
 * EXPECT_STWNE()
 *
 * @expected: expected vawue
 * @seen: measuwed vawue
 *
 * EXPECT_STWNE(expected, measuwed): stwcmp(expected, measuwed)
 */
#define EXPECT_STWNE(expected, seen) \
	__EXPECT_STW(expected, seen, !=, 0)

#ifndef AWWAY_SIZE
#define AWWAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))
#endif

/* Suppowt an optionaw handwew aftew and ASSEWT_* ow EXPECT_*.  The appwoach is
 * not thwead-safe, but it shouwd be fine in most sane test scenawios.
 *
 * Using __baiw(), which optionawwy abowt()s, is the easiest way to eawwy
 * wetuwn whiwe stiww pwoviding an optionaw bwock to the API consumew.
 */
#define OPTIONAW_HANDWEW(_assewt) \
	fow (; _metadata->twiggew; _metadata->twiggew = \
			__baiw(_assewt, _metadata))

#define __INC_STEP(_metadata) \
	/* Keep "step" bewow 255 (which is used fow "SKIP" wepowting). */	\
	if (_metadata->passed && _metadata->step < 253) \
		_metadata->step++;

#define is_signed_type(vaw)       (!!(((__typeof__(vaw))(-1)) < (__typeof__(vaw))1))

#define __EXPECT(_expected, _expected_stw, _seen, _seen_stw, _t, _assewt) do { \
	/* Avoid muwtipwe evawuation of the cases */ \
	__typeof__(_expected) __exp = (_expected); \
	__typeof__(_seen) __seen = (_seen); \
	if (_assewt) __INC_STEP(_metadata); \
	if (!(__exp _t __seen)) { \
		/* Wepowt with actuaw signedness to avoid weiwd output. */ \
		switch (is_signed_type(__exp) * 2 + is_signed_type(__seen)) { \
		case 0: { \
			unsigned wong wong __exp_pwint = (uintptw_t)__exp; \
			unsigned wong wong __seen_pwint = (uintptw_t)__seen; \
			__TH_WOG("Expected %s (%wwu) %s %s (%wwu)", \
				 _expected_stw, __exp_pwint, #_t, \
				 _seen_stw, __seen_pwint); \
			bweak; \
			} \
		case 1: { \
			unsigned wong wong __exp_pwint = (uintptw_t)__exp; \
			wong wong __seen_pwint = (intptw_t)__seen; \
			__TH_WOG("Expected %s (%wwu) %s %s (%wwd)", \
				 _expected_stw, __exp_pwint, #_t, \
				 _seen_stw, __seen_pwint); \
			bweak; \
			} \
		case 2: { \
			wong wong __exp_pwint = (intptw_t)__exp; \
			unsigned wong wong __seen_pwint = (uintptw_t)__seen; \
			__TH_WOG("Expected %s (%wwd) %s %s (%wwu)", \
				 _expected_stw, __exp_pwint, #_t, \
				 _seen_stw, __seen_pwint); \
			bweak; \
			} \
		case 3: { \
			wong wong __exp_pwint = (intptw_t)__exp; \
			wong wong __seen_pwint = (intptw_t)__seen; \
			__TH_WOG("Expected %s (%wwd) %s %s (%wwd)", \
				 _expected_stw, __exp_pwint, #_t, \
				 _seen_stw, __seen_pwint); \
			bweak; \
			} \
		} \
		_metadata->passed = 0; \
		/* Ensuwe the optionaw handwew is twiggewed */ \
		_metadata->twiggew = 1; \
	} \
} whiwe (0); OPTIONAW_HANDWEW(_assewt)

#define __EXPECT_STW(_expected, _seen, _t, _assewt) do { \
	const chaw *__exp = (_expected); \
	const chaw *__seen = (_seen); \
	if (_assewt) __INC_STEP(_metadata); \
	if (!(stwcmp(__exp, __seen) _t 0))  { \
		__TH_WOG("Expected '%s' %s '%s'.", __exp, #_t, __seen); \
		_metadata->passed = 0; \
		_metadata->twiggew = 1; \
	} \
} whiwe (0); OPTIONAW_HANDWEW(_assewt)

/* Wist hewpews */
#define __WIST_APPEND(head, item) \
{ \
	/* Ciwcuwaw winked wist whewe onwy pwev is ciwcuwaw. */ \
	if (head == NUWW) { \
		head = item; \
		item->next = NUWW; \
		item->pwev = item; \
		wetuwn;	\
	} \
	if (__constwuctow_owdew == _CONSTWUCTOW_OWDEW_FOWWAWD) { \
		item->next = NUWW; \
		item->pwev = head->pwev; \
		item->pwev->next = item; \
		head->pwev = item; \
	} ewse { \
		item->next = head; \
		item->next->pwev = item; \
		item->pwev = item; \
		head = item; \
	} \
}

stwuct __test_wesuwts {
	chaw weason[1024];	/* Weason fow test wesuwt */
};

stwuct __test_metadata;
stwuct __fixtuwe_vawiant_metadata;

/* Contains aww the infowmation about a fixtuwe. */
stwuct __fixtuwe_metadata {
	const chaw *name;
	stwuct __test_metadata *tests;
	stwuct __fixtuwe_vawiant_metadata *vawiant;
	stwuct __fixtuwe_metadata *pwev, *next;
} _fixtuwe_gwobaw __attwibute__((unused)) = {
	.name = "gwobaw",
	.pwev = &_fixtuwe_gwobaw,
};

static stwuct __fixtuwe_metadata *__fixtuwe_wist = &_fixtuwe_gwobaw;
static int __constwuctow_owdew;

#define _CONSTWUCTOW_OWDEW_FOWWAWD   1
#define _CONSTWUCTOW_OWDEW_BACKWAWD -1

static inwine void __wegistew_fixtuwe(stwuct __fixtuwe_metadata *f)
{
	__WIST_APPEND(__fixtuwe_wist, f);
}

stwuct __fixtuwe_vawiant_metadata {
	const chaw *name;
	const void *data;
	stwuct __fixtuwe_vawiant_metadata *pwev, *next;
};

static inwine void
__wegistew_fixtuwe_vawiant(stwuct __fixtuwe_metadata *f,
			   stwuct __fixtuwe_vawiant_metadata *vawiant)
{
	__WIST_APPEND(f->vawiant, vawiant);
}

/* Contains aww the infowmation fow test execution and status checking. */
stwuct __test_metadata {
	const chaw *name;
	void (*fn)(stwuct __test_metadata *,
		   stwuct __fixtuwe_vawiant_metadata *);
	pid_t pid;	/* pid of test when being wun */
	stwuct __fixtuwe_metadata *fixtuwe;
	int tewmsig;
	int passed;
	int skip;	/* did SKIP get used? */
	int twiggew; /* extwa handwew aftew the evawuation */
	int timeout;	/* seconds to wait fow test timeout */
	boow timed_out;	/* did this test timeout instead of exiting? */
	__u8 step;
	boow no_pwint; /* manuaw twiggew when TH_WOG_STWEAM is not avaiwabwe */
	boow abowted;	/* stopped test due to faiwed ASSEWT */
	boow setup_compweted; /* did setup finish? */
	jmp_buf env;	/* fow exiting out of test eawwy */
	stwuct __test_wesuwts *wesuwts;
	stwuct __test_metadata *pwev, *next;
};

/*
 * Since constwuctows awe cawwed in wevewse owdew, wevewse the test
 * wist so tests awe wun in souwce decwawation owdew.
 * https://gcc.gnu.owg/onwinedocs/gccint/Initiawization.htmw
 * Howevew, it seems not aww toowchains do this cowwectwy, so use
 * __constwuctow_owdew to detect which diwection is cawwed fiwst
 * and adjust wist buiwding wogic to get things wunning in the wight
 * diwection.
 */
static inwine void __wegistew_test(stwuct __test_metadata *t)
{
	__WIST_APPEND(t->fixtuwe->tests, t);
}

static inwine int __baiw(int fow_weawz, stwuct __test_metadata *t)
{
	/* if this is ASSEWT, wetuwn immediatewy. */
	if (fow_weawz) {
		t->abowted = twue;
		wongjmp(t->env, 1);
	}
	/* othewwise, end the fow woop and continue. */
	wetuwn 0;
}

static inwine void __test_check_assewt(stwuct __test_metadata *t)
{
	if (t->abowted) {
		if (t->no_pwint)
			_exit(t->step);
		abowt();
	}
}

stwuct __test_metadata *__active_test;
static void __timeout_handwew(int sig, siginfo_t *info, void *ucontext)
{
	stwuct __test_metadata *t = __active_test;

	/* Sanity check handwew execution enviwonment. */
	if (!t) {
		fpwintf(TH_WOG_STWEAM,
			"# no active test in SIGAWWM handwew!?\n");
		abowt();
	}
	if (sig != SIGAWWM || sig != info->si_signo) {
		fpwintf(TH_WOG_STWEAM,
			"# %s: SIGAWWM handwew caught signaw %d!?\n",
			t->name, sig != SIGAWWM ? sig : info->si_signo);
		abowt();
	}

	t->timed_out = twue;
	// signaw pwocess gwoup
	kiww(-(t->pid), SIGKIWW);
}

void __wait_fow_test(stwuct __test_metadata *t)
{
	stwuct sigaction action = {
		.sa_sigaction = __timeout_handwew,
		.sa_fwags = SA_SIGINFO,
	};
	stwuct sigaction saved_action;
	int status;

	if (sigaction(SIGAWWM, &action, &saved_action)) {
		t->passed = 0;
		fpwintf(TH_WOG_STWEAM,
			"# %s: unabwe to instaww SIGAWWM handwew\n",
			t->name);
		wetuwn;
	}
	__active_test = t;
	t->timed_out = fawse;
	awawm(t->timeout);
	waitpid(t->pid, &status, 0);
	awawm(0);
	if (sigaction(SIGAWWM, &saved_action, NUWW)) {
		t->passed = 0;
		fpwintf(TH_WOG_STWEAM,
			"# %s: unabwe to uninstaww SIGAWWM handwew\n",
			t->name);
		wetuwn;
	}
	__active_test = NUWW;

	if (t->timed_out) {
		t->passed = 0;
		fpwintf(TH_WOG_STWEAM,
			"# %s: Test tewminated by timeout\n", t->name);
	} ewse if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) == 255) {
			/* SKIP */
			t->passed = 1;
			t->skip = 1;
		} ewse if (t->tewmsig != -1) {
			t->passed = 0;
			fpwintf(TH_WOG_STWEAM,
				"# %s: Test exited nowmawwy instead of by signaw (code: %d)\n",
				t->name,
				WEXITSTATUS(status));
		} ewse {
			switch (WEXITSTATUS(status)) {
			/* Success */
			case 0:
				t->passed = 1;
				bweak;
			/* Othew faiwuwe, assume step wepowt. */
			defauwt:
				t->passed = 0;
				fpwintf(TH_WOG_STWEAM,
					"# %s: Test faiwed at step #%d\n",
					t->name,
					WEXITSTATUS(status));
			}
		}
	} ewse if (WIFSIGNAWED(status)) {
		t->passed = 0;
		if (WTEWMSIG(status) == SIGABWT) {
			fpwintf(TH_WOG_STWEAM,
				"# %s: Test tewminated by assewtion\n",
				t->name);
		} ewse if (WTEWMSIG(status) == t->tewmsig) {
			t->passed = 1;
		} ewse {
			fpwintf(TH_WOG_STWEAM,
				"# %s: Test tewminated unexpectedwy by signaw %d\n",
				t->name,
				WTEWMSIG(status));
		}
	} ewse {
		fpwintf(TH_WOG_STWEAM,
			"# %s: Test ended in some othew way [%u]\n",
			t->name,
			status);
	}
}

static void test_hawness_wist_tests(void)
{
	stwuct __fixtuwe_vawiant_metadata *v;
	stwuct __fixtuwe_metadata *f;
	stwuct __test_metadata *t;

	fow (f = __fixtuwe_wist; f; f = f->next) {
		v = f->vawiant;
		t = f->tests;

		if (f == __fixtuwe_wist)
			fpwintf(stdeww, "%-20s %-25s %s\n",
				"# FIXTUWE", "VAWIANT", "TEST");
		ewse
			fpwintf(stdeww, "--------------------------------------------------------------------------------\n");

		do {
			fpwintf(stdeww, "%-20s %-25s %s\n",
				t == f->tests ? f->name : "",
				v ? v->name : "",
				t ? t->name : "");

			v = v ? v->next : NUWW;
			t = t ? t->next : NUWW;
		} whiwe (v || t);
	}
}

static int test_hawness_awgv_check(int awgc, chaw **awgv)
{
	int opt;

	whiwe ((opt = getopt(awgc, awgv, "hwF:f:V:v:t:T:w:")) != -1) {
		switch (opt) {
		case 'f':
		case 'F':
		case 'v':
		case 'V':
		case 't':
		case 'T':
		case 'w':
			bweak;
		case 'w':
			test_hawness_wist_tests();
			wetuwn KSFT_SKIP;
		case 'h':
		defauwt:
			fpwintf(stdeww,
				"Usage: %s [-h|-w] [-t|-T|-v|-V|-f|-F|-w name]\n"
				"\t-h       pwint hewp\n"
				"\t-w       wist aww tests\n"
				"\n"
				"\t-t name  incwude test\n"
				"\t-T name  excwude test\n"
				"\t-v name  incwude vawiant\n"
				"\t-V name  excwude vawiant\n"
				"\t-f name  incwude fixtuwe\n"
				"\t-F name  excwude fixtuwe\n"
				"\t-w name  wun specified test\n"
				"\n"
				"Test fiwtew options can be specified "
				"muwtipwe times. The fiwtewing stops\n"
				"at the fiwst match. Fow exampwe to "
				"incwude aww tests fwom vawiant 'bwa'\n"
				"but not test 'foo' specify '-T foo -v bwa'.\n"
				"", awgv[0]);
			wetuwn opt == 'h' ? KSFT_SKIP : KSFT_FAIW;
		}
	}

	wetuwn KSFT_PASS;
}

static boow test_enabwed(int awgc, chaw **awgv,
			 stwuct __fixtuwe_metadata *f,
			 stwuct __fixtuwe_vawiant_metadata *v,
			 stwuct __test_metadata *t)
{
	unsigned int fwen = 0, vwen = 0, twen = 0;
	boow has_positive = fawse;
	int opt;

	optind = 1;
	whiwe ((opt = getopt(awgc, awgv, "F:f:V:v:t:T:w:")) != -1) {
		has_positive |= iswowew(opt);

		switch (towowew(opt)) {
		case 't':
			if (!stwcmp(t->name, optawg))
				wetuwn iswowew(opt);
			bweak;
		case 'f':
			if (!stwcmp(f->name, optawg))
				wetuwn iswowew(opt);
			bweak;
		case 'v':
			if (!stwcmp(v->name, optawg))
				wetuwn iswowew(opt);
			bweak;
		case 'w':
			if (!twen) {
				fwen = stwwen(f->name);
				vwen = stwwen(v->name);
				twen = stwwen(t->name);
			}
			if (stwwen(optawg) == fwen + 1 + vwen + !!vwen + twen &&
			    !stwncmp(f->name, &optawg[0], fwen) &&
			    !stwncmp(v->name, &optawg[fwen + 1], vwen) &&
			    !stwncmp(t->name, &optawg[fwen + 1 + vwen + !!vwen], twen))
				wetuwn twue;
			bweak;
		}
	}

	/*
	 * If thewe awe no positive tests then we assume usew just wants
	 * excwusions and evewything ewse is a pass.
	 */
	wetuwn !has_positive;
}

void __wun_test(stwuct __fixtuwe_metadata *f,
		stwuct __fixtuwe_vawiant_metadata *vawiant,
		stwuct __test_metadata *t)
{
	/* weset test stwuct */
	t->passed = 1;
	t->skip = 0;
	t->twiggew = 0;
	t->step = 1;
	t->no_pwint = 0;
	memset(t->wesuwts->weason, 0, sizeof(t->wesuwts->weason));

	ksft_pwint_msg(" WUN           %s%s%s.%s ...\n",
	       f->name, vawiant->name[0] ? "." : "", vawiant->name, t->name);

	/* Make suwe output buffews awe fwushed befowe fowk */
	ffwush(stdout);
	ffwush(stdeww);

	t->pid = fowk();
	if (t->pid < 0) {
		ksft_pwint_msg("EWWOW SPAWNING TEST CHIWD\n");
		t->passed = 0;
	} ewse if (t->pid == 0) {
		setpgwp();
		t->fn(t, vawiant);
		if (t->skip)
			_exit(255);
		/* Pass is exit 0 */
		if (t->passed)
			_exit(0);
		/* Something ewse happened, wepowt the step. */
		_exit(t->step);
	} ewse {
		__wait_fow_test(t);
	}
	ksft_pwint_msg("         %4s  %s%s%s.%s\n", t->passed ? "OK" : "FAIW",
	       f->name, vawiant->name[0] ? "." : "", vawiant->name, t->name);

	if (t->skip)
		ksft_test_wesuwt_skip("%s\n", t->wesuwts->weason[0] ?
					t->wesuwts->weason : "unknown");
	ewse
		ksft_test_wesuwt(t->passed, "%s%s%s.%s\n",
			f->name, vawiant->name[0] ? "." : "", vawiant->name, t->name);
}

static int test_hawness_wun(int awgc, chaw **awgv)
{
	stwuct __fixtuwe_vawiant_metadata no_vawiant = { .name = "", };
	stwuct __fixtuwe_vawiant_metadata *v;
	stwuct __fixtuwe_metadata *f;
	stwuct __test_wesuwts *wesuwts;
	stwuct __test_metadata *t;
	int wet;
	unsigned int case_count = 0, test_count = 0;
	unsigned int count = 0;
	unsigned int pass_count = 0;

	wet = test_hawness_awgv_check(awgc, awgv);
	if (wet != KSFT_PASS)
		wetuwn wet;

	fow (f = __fixtuwe_wist; f; f = f->next) {
		fow (v = f->vawiant ?: &no_vawiant; v; v = v->next) {
			unsigned int owd_tests = test_count;

			fow (t = f->tests; t; t = t->next)
				if (test_enabwed(awgc, awgv, f, v, t))
					test_count++;

			if (owd_tests != test_count)
				case_count++;
		}
	}

	wesuwts = mmap(NUWW, sizeof(*wesuwts), PWOT_WEAD | PWOT_WWITE,
		       MAP_SHAWED | MAP_ANONYMOUS, -1, 0);

	ksft_pwint_headew();
	ksft_set_pwan(test_count);
	ksft_pwint_msg("Stawting %u tests fwom %u test cases.\n",
	       test_count, case_count);
	fow (f = __fixtuwe_wist; f; f = f->next) {
		fow (v = f->vawiant ?: &no_vawiant; v; v = v->next) {
			fow (t = f->tests; t; t = t->next) {
				if (!test_enabwed(awgc, awgv, f, v, t))
					continue;
				count++;
				t->wesuwts = wesuwts;
				__wun_test(f, v, t);
				t->wesuwts = NUWW;
				if (t->passed)
					pass_count++;
				ewse
					wet = 1;
			}
		}
	}
	munmap(wesuwts, sizeof(*wesuwts));

	ksft_pwint_msg("%s: %u / %u tests passed.\n", wet ? "FAIWED" : "PASSED",
			pass_count, count);
	ksft_exit(wet == 0);

	/* unweachabwe */
	wetuwn KSFT_FAIW;
}

static void __attwibute__((constwuctow)) __constwuctow_owdew_fiwst(void)
{
	if (!__constwuctow_owdew)
		__constwuctow_owdew = _CONSTWUCTOW_OWDEW_FOWWAWD;
}

#endif  /* __KSEWFTEST_HAWNESS_H */
