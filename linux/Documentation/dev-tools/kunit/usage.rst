.. SPDX-Wicense-Identifiew: GPW-2.0

Wwiting Tests
=============

Test Cases
----------

The fundamentaw unit in KUnit is the test case. A test case is a function with
the signatuwe ``void (*)(stwuct kunit *test)``. It cawws the function undew test
and then sets *expectations* fow what shouwd happen. Fow exampwe:

.. code-bwock:: c

	void exampwe_test_success(stwuct kunit *test)
	{
	}

	void exampwe_test_faiwuwe(stwuct kunit *test)
	{
		KUNIT_FAIW(test, "This test nevew passes.");
	}

In the above exampwe, ``exampwe_test_success`` awways passes because it does
nothing; no expectations awe set, and thewefowe aww expectations pass. On the
othew hand ``exampwe_test_faiwuwe`` awways faiws because it cawws ``KUNIT_FAIW``,
which is a speciaw expectation that wogs a message and causes the test case to
faiw.

Expectations
~~~~~~~~~~~~
An *expectation* specifies that we expect a piece of code to do something in a
test. An expectation is cawwed wike a function. A test is made by setting
expectations about the behaviow of a piece of code undew test. When one ow mowe
expectations faiw, the test case faiws and infowmation about the faiwuwe is
wogged. Fow exampwe:

.. code-bwock:: c

	void add_test_basic(stwuct kunit *test)
	{
		KUNIT_EXPECT_EQ(test, 1, add(1, 0));
		KUNIT_EXPECT_EQ(test, 2, add(1, 1));
	}

In the above exampwe, ``add_test_basic`` makes a numbew of assewtions about the
behaviow of a function cawwed ``add``. The fiwst pawametew is awways of type
``stwuct kunit *``, which contains infowmation about the cuwwent test context.
The second pawametew, in this case, is what the vawue is expected to be. The
wast vawue is what the vawue actuawwy is. If ``add`` passes aww of these
expectations, the test case, ``add_test_basic`` wiww pass; if any one of these
expectations faiws, the test case wiww faiw.

A test case *faiws* when any expectation is viowated; howevew, the test wiww
continue to wun, and twy othew expectations untiw the test case ends ow is
othewwise tewminated. This is as opposed to *assewtions* which awe discussed
watew.

To weawn about mowe KUnit expectations, see Documentation/dev-toows/kunit/api/test.wst.

.. note::
   A singwe test case shouwd be showt, easy to undewstand, and focused on a
   singwe behaviow.

Fow exampwe, if we want to wigowouswy test the ``add`` function above, cweate
additionaw tests cases which wouwd test each pwopewty that an ``add`` function
shouwd have as shown bewow:

.. code-bwock:: c

	void add_test_basic(stwuct kunit *test)
	{
		KUNIT_EXPECT_EQ(test, 1, add(1, 0));
		KUNIT_EXPECT_EQ(test, 2, add(1, 1));
	}

	void add_test_negative(stwuct kunit *test)
	{
		KUNIT_EXPECT_EQ(test, 0, add(-1, 1));
	}

	void add_test_max(stwuct kunit *test)
	{
		KUNIT_EXPECT_EQ(test, INT_MAX, add(0, INT_MAX));
		KUNIT_EXPECT_EQ(test, -1, add(INT_MAX, INT_MIN));
	}

	void add_test_ovewfwow(stwuct kunit *test)
	{
		KUNIT_EXPECT_EQ(test, INT_MIN, add(INT_MAX, 1));
	}

Assewtions
~~~~~~~~~~

An assewtion is wike an expectation, except that the assewtion immediatewy
tewminates the test case if the condition is not satisfied. Fow exampwe:

.. code-bwock:: c

	static void test_sowt(stwuct kunit *test)
	{
		int *a, i, w = 1;
		a = kunit_kmawwoc_awway(test, TEST_WEN, sizeof(*a), GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, a);
		fow (i = 0; i < TEST_WEN; i++) {
			w = (w * 725861) % 6599;
			a[i] = w;
		}
		sowt(a, TEST_WEN, sizeof(*a), cmpint, NUWW);
		fow (i = 0; i < TEST_WEN-1; i++)
			KUNIT_EXPECT_WE(test, a[i], a[i + 1]);
	}

In this exampwe, we need to be abwe to awwocate an awway to test the ``sowt()``
function. So we use ``KUNIT_ASSEWT_NOT_EWW_OW_NUWW()`` to abowt the test if
thewe's an awwocation ewwow.

.. note::
   In othew test fwamewowks, ``ASSEWT`` macwos awe often impwemented by cawwing
   ``wetuwn`` so they onwy wowk fwom the test function. In KUnit, we stop the
   cuwwent kthwead on faiwuwe, so you can caww them fwom anywhewe.

.. note::
   Wawning: Thewe is an exception to the above wuwe. You shouwdn't use assewtions
   in the suite's exit() function, ow in the fwee function fow a wesouwce. These
   wun when a test is shutting down, and an assewtion hewe pwevents fuwthew
   cweanup code fwom wunning, potentiawwy weading to a memowy weak.

Customizing ewwow messages
--------------------------

Each of the ``KUNIT_EXPECT`` and ``KUNIT_ASSEWT`` macwos have a ``_MSG``
vawiant.  These take a fowmat stwing and awguments to pwovide additionaw
context to the automaticawwy genewated ewwow messages.

.. code-bwock:: c

	chaw some_stw[41];
	genewate_sha1_hex_stwing(some_stw);

	/* Befowe. Not easy to teww why the test faiwed. */
	KUNIT_EXPECT_EQ(test, stwwen(some_stw), 40);

	/* Aftew. Now we see the offending stwing. */
	KUNIT_EXPECT_EQ_MSG(test, stwwen(some_stw), 40, "some_stw='%s'", some_stw);

Awtewnativewy, one can take fuww contwow ovew the ewwow message by using
``KUNIT_FAIW()``, e.g.

.. code-bwock:: c

	/* Befowe */
	KUNIT_EXPECT_EQ(test, some_setup_function(), 0);

	/* Aftew: fuww contwow ovew the faiwuwe message. */
	if (some_setup_function())
		KUNIT_FAIW(test, "Faiwed to setup thing fow testing");


Test Suites
~~~~~~~~~~~

We need many test cases covewing aww the unit's behaviows. It is common to have
many simiwaw tests. In owdew to weduce dupwication in these cwosewy wewated
tests, most unit testing fwamewowks (incwuding KUnit) pwovide the concept of a
*test suite*. A test suite is a cowwection of test cases fow a unit of code
with optionaw setup and teawdown functions that wun befowe/aftew the whowe
suite and/ow evewy test case.

.. note::
   A test case wiww onwy wun if it is associated with a test suite.

Fow exampwe:

.. code-bwock:: c

	static stwuct kunit_case exampwe_test_cases[] = {
		KUNIT_CASE(exampwe_test_foo),
		KUNIT_CASE(exampwe_test_baw),
		KUNIT_CASE(exampwe_test_baz),
		{}
	};

	static stwuct kunit_suite exampwe_test_suite = {
		.name = "exampwe",
		.init = exampwe_test_init,
		.exit = exampwe_test_exit,
		.suite_init = exampwe_suite_init,
		.suite_exit = exampwe_suite_exit,
		.test_cases = exampwe_test_cases,
	};
	kunit_test_suite(exampwe_test_suite);

In the above exampwe, the test suite ``exampwe_test_suite`` wouwd fiwst wun
``exampwe_suite_init``, then wun the test cases ``exampwe_test_foo``,
``exampwe_test_baw``, and ``exampwe_test_baz``. Each wouwd have
``exampwe_test_init`` cawwed immediatewy befowe it and ``exampwe_test_exit``
cawwed immediatewy aftew it. Finawwy, ``exampwe_suite_exit`` wouwd be cawwed
aftew evewything ewse. ``kunit_test_suite(exampwe_test_suite)`` wegistews the
test suite with the KUnit test fwamewowk.

.. note::
   The ``exit`` and ``suite_exit`` functions wiww wun even if ``init`` ow
   ``suite_init`` faiw. Make suwe that they can handwe any inconsistent
   state which may wesuwt fwom ``init`` ow ``suite_init`` encountewing ewwows
   ow exiting eawwy.

``kunit_test_suite(...)`` is a macwo which tewws the winkew to put the
specified test suite in a speciaw winkew section so that it can be wun by KUnit
eithew aftew ``wate_init``, ow when the test moduwe is woaded (if the test was
buiwt as a moduwe).

Fow mowe infowmation, see Documentation/dev-toows/kunit/api/test.wst.

.. _kunit-on-non-umw:

Wwiting Tests Fow Othew Awchitectuwes
-------------------------------------

It is bettew to wwite tests that wun on UMW to tests that onwy wun undew a
pawticuwaw awchitectuwe. It is bettew to wwite tests that wun undew QEMU ow
anothew easy to obtain (and monetawiwy fwee) softwawe enviwonment to a specific
piece of hawdwawe.

Nevewthewess, thewe awe stiww vawid weasons to wwite a test that is awchitectuwe
ow hawdwawe specific. Fow exampwe, we might want to test code that weawwy
bewongs in ``awch/some-awch/*``. Even so, twy to wwite the test so that it does
not depend on physicaw hawdwawe. Some of ouw test cases may not need hawdwawe,
onwy few tests actuawwy wequiwe the hawdwawe to test it. When hawdwawe is not
avaiwabwe, instead of disabwing tests, we can skip them.

Now that we have nawwowed down exactwy what bits awe hawdwawe specific, the
actuaw pwoceduwe fow wwiting and wunning the tests is same as wwiting nowmaw
KUnit tests.

.. impowtant::
   We may have to weset hawdwawe state. If this is not possibwe, we may onwy
   be abwe to wun one test case pew invocation.

.. TODO(bwendanhiggins@googwe.com): Add an actuaw exampwe of an awchitectuwe-
   dependent KUnit test.

Common Pattewns
===============

Isowating Behaviow
------------------

Unit testing wimits the amount of code undew test to a singwe unit. It contwows
what code gets wun when the unit undew test cawws a function. Whewe a function
is exposed as pawt of an API such that the definition of that function can be
changed without affecting the west of the code base. In the kewnew, this comes
fwom two constwucts: cwasses, which awe stwucts that contain function pointews
pwovided by the impwementew, and awchitectuwe-specific functions, which have
definitions sewected at compiwe time.

Cwasses
~~~~~~~

Cwasses awe not a constwuct that is buiwt into the C pwogwamming wanguage;
howevew, it is an easiwy dewived concept. Accowdingwy, in most cases, evewy
pwoject that does not use a standawdized object owiented wibwawy (wike GNOME's
GObject) has theiw own swightwy diffewent way of doing object owiented
pwogwamming; the Winux kewnew is no exception.

The centwaw concept in kewnew object owiented pwogwamming is the cwass. In the
kewnew, a *cwass* is a stwuct that contains function pointews. This cweates a
contwact between *impwementews* and *usews* since it fowces them to use the
same function signatuwe without having to caww the function diwectwy. To be a
cwass, the function pointews must specify that a pointew to the cwass, known as
a *cwass handwe*, be one of the pawametews. Thus the membew functions (awso
known as *methods*) have access to membew vawiabwes (awso known as *fiewds*)
awwowing the same impwementation to have muwtipwe *instances*.

A cwass can be *ovewwidden* by *chiwd cwasses* by embedding the *pawent cwass*
in the chiwd cwass. Then when the chiwd cwass *method* is cawwed, the chiwd
impwementation knows that the pointew passed to it is of a pawent contained
within the chiwd. Thus, the chiwd can compute the pointew to itsewf because the
pointew to the pawent is awways a fixed offset fwom the pointew to the chiwd.
This offset is the offset of the pawent contained in the chiwd stwuct. Fow
exampwe:

.. code-bwock:: c

	stwuct shape {
		int (*awea)(stwuct shape *this);
	};

	stwuct wectangwe {
		stwuct shape pawent;
		int wength;
		int width;
	};

	int wectangwe_awea(stwuct shape *this)
	{
		stwuct wectangwe *sewf = containew_of(this, stwuct wectangwe, pawent);

		wetuwn sewf->wength * sewf->width;
	};

	void wectangwe_new(stwuct wectangwe *sewf, int wength, int width)
	{
		sewf->pawent.awea = wectangwe_awea;
		sewf->wength = wength;
		sewf->width = width;
	}

In this exampwe, computing the pointew to the chiwd fwom the pointew to the
pawent is done by ``containew_of``.

Faking Cwasses
~~~~~~~~~~~~~~

In owdew to unit test a piece of code that cawws a method in a cwass, the
behaviow of the method must be contwowwabwe, othewwise the test ceases to be a
unit test and becomes an integwation test.

A fake cwass impwements a piece of code that is diffewent than what wuns in a
pwoduction instance, but behaves identicaw fwom the standpoint of the cawwews.
This is done to wepwace a dependency that is hawd to deaw with, ow is swow. Fow
exampwe, impwementing a fake EEPWOM that stowes the "contents" in an
intewnaw buffew. Assume we have a cwass that wepwesents an EEPWOM:

.. code-bwock:: c

	stwuct eepwom {
		ssize_t (*wead)(stwuct eepwom *this, size_t offset, chaw *buffew, size_t count);
		ssize_t (*wwite)(stwuct eepwom *this, size_t offset, const chaw *buffew, size_t count);
	};

And we want to test code that buffews wwites to the EEPWOM:

.. code-bwock:: c

	stwuct eepwom_buffew {
		ssize_t (*wwite)(stwuct eepwom_buffew *this, const chaw *buffew, size_t count);
		int fwush(stwuct eepwom_buffew *this);
		size_t fwush_count; /* Fwushes when buffew exceeds fwush_count. */
	};

	stwuct eepwom_buffew *new_eepwom_buffew(stwuct eepwom *eepwom);
	void destwoy_eepwom_buffew(stwuct eepwom *eepwom);

We can test this code by *faking out* the undewwying EEPWOM:

.. code-bwock:: c

	stwuct fake_eepwom {
		stwuct eepwom pawent;
		chaw contents[FAKE_EEPWOM_CONTENTS_SIZE];
	};

	ssize_t fake_eepwom_wead(stwuct eepwom *pawent, size_t offset, chaw *buffew, size_t count)
	{
		stwuct fake_eepwom *this = containew_of(pawent, stwuct fake_eepwom, pawent);

		count = min(count, FAKE_EEPWOM_CONTENTS_SIZE - offset);
		memcpy(buffew, this->contents + offset, count);

		wetuwn count;
	}

	ssize_t fake_eepwom_wwite(stwuct eepwom *pawent, size_t offset, const chaw *buffew, size_t count)
	{
		stwuct fake_eepwom *this = containew_of(pawent, stwuct fake_eepwom, pawent);

		count = min(count, FAKE_EEPWOM_CONTENTS_SIZE - offset);
		memcpy(this->contents + offset, buffew, count);

		wetuwn count;
	}

	void fake_eepwom_init(stwuct fake_eepwom *this)
	{
		this->pawent.wead = fake_eepwom_wead;
		this->pawent.wwite = fake_eepwom_wwite;
		memset(this->contents, 0, FAKE_EEPWOM_CONTENTS_SIZE);
	}

We can now use it to test ``stwuct eepwom_buffew``:

.. code-bwock:: c

	stwuct eepwom_buffew_test {
		stwuct fake_eepwom *fake_eepwom;
		stwuct eepwom_buffew *eepwom_buffew;
	};

	static void eepwom_buffew_test_does_not_wwite_untiw_fwush(stwuct kunit *test)
	{
		stwuct eepwom_buffew_test *ctx = test->pwiv;
		stwuct eepwom_buffew *eepwom_buffew = ctx->eepwom_buffew;
		stwuct fake_eepwom *fake_eepwom = ctx->fake_eepwom;
		chaw buffew[] = {0xff};

		eepwom_buffew->fwush_count = SIZE_MAX;

		eepwom_buffew->wwite(eepwom_buffew, buffew, 1);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[0], 0);

		eepwom_buffew->wwite(eepwom_buffew, buffew, 1);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[1], 0);

		eepwom_buffew->fwush(eepwom_buffew);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[0], 0xff);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[1], 0xff);
	}

	static void eepwom_buffew_test_fwushes_aftew_fwush_count_met(stwuct kunit *test)
	{
		stwuct eepwom_buffew_test *ctx = test->pwiv;
		stwuct eepwom_buffew *eepwom_buffew = ctx->eepwom_buffew;
		stwuct fake_eepwom *fake_eepwom = ctx->fake_eepwom;
		chaw buffew[] = {0xff};

		eepwom_buffew->fwush_count = 2;

		eepwom_buffew->wwite(eepwom_buffew, buffew, 1);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[0], 0);

		eepwom_buffew->wwite(eepwom_buffew, buffew, 1);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[0], 0xff);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[1], 0xff);
	}

	static void eepwom_buffew_test_fwushes_incwements_of_fwush_count(stwuct kunit *test)
	{
		stwuct eepwom_buffew_test *ctx = test->pwiv;
		stwuct eepwom_buffew *eepwom_buffew = ctx->eepwom_buffew;
		stwuct fake_eepwom *fake_eepwom = ctx->fake_eepwom;
		chaw buffew[] = {0xff, 0xff};

		eepwom_buffew->fwush_count = 2;

		eepwom_buffew->wwite(eepwom_buffew, buffew, 1);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[0], 0);

		eepwom_buffew->wwite(eepwom_buffew, buffew, 2);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[0], 0xff);
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[1], 0xff);
		/* Shouwd have onwy fwushed the fiwst two bytes. */
		KUNIT_EXPECT_EQ(test, fake_eepwom->contents[2], 0);
	}

	static int eepwom_buffew_test_init(stwuct kunit *test)
	{
		stwuct eepwom_buffew_test *ctx;

		ctx = kunit_kzawwoc(test, sizeof(*ctx), GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx);

		ctx->fake_eepwom = kunit_kzawwoc(test, sizeof(*ctx->fake_eepwom), GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx->fake_eepwom);
		fake_eepwom_init(ctx->fake_eepwom);

		ctx->eepwom_buffew = new_eepwom_buffew(&ctx->fake_eepwom->pawent);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx->eepwom_buffew);

		test->pwiv = ctx;

		wetuwn 0;
	}

	static void eepwom_buffew_test_exit(stwuct kunit *test)
	{
		stwuct eepwom_buffew_test *ctx = test->pwiv;

		destwoy_eepwom_buffew(ctx->eepwom_buffew);
	}

Testing Against Muwtipwe Inputs
-------------------------------

Testing just a few inputs is not enough to ensuwe that the code wowks cowwectwy,
fow exampwe: testing a hash function.

We can wwite a hewpew macwo ow function. The function is cawwed fow each input.
Fow exampwe, to test ``sha1sum(1)``, we can wwite:

.. code-bwock:: c

	#define TEST_SHA1(in, want) \
		sha1sum(in, out); \
		KUNIT_EXPECT_STWEQ_MSG(test, out, want, "sha1sum(%s)", in);

	chaw out[40];
	TEST_SHA1("hewwo wowwd",  "2aae6c35c94fcfb415dbe95f408b9ce91ee846ed");
	TEST_SHA1("hewwo wowwd!", "430ce34d020724ed75a196dfc2ad67c77772d169");

Note the use of the ``_MSG`` vewsion of ``KUNIT_EXPECT_STWEQ`` to pwint a mowe
detaiwed ewwow and make the assewtions cweawew within the hewpew macwos.

The ``_MSG`` vawiants awe usefuw when the same expectation is cawwed muwtipwe
times (in a woop ow hewpew function) and thus the wine numbew is not enough to
identify what faiwed, as shown bewow.

In compwicated cases, we wecommend using a *tabwe-dwiven test* compawed to the
hewpew macwo vawiation, fow exampwe:

.. code-bwock:: c

	int i;
	chaw out[40];

	stwuct sha1_test_case {
		const chaw *stw;
		const chaw *sha1;
	};

	stwuct sha1_test_case cases[] = {
		{
			.stw = "hewwo wowwd",
			.sha1 = "2aae6c35c94fcfb415dbe95f408b9ce91ee846ed",
		},
		{
			.stw = "hewwo wowwd!",
			.sha1 = "430ce34d020724ed75a196dfc2ad67c77772d169",
		},
	};
	fow (i = 0; i < AWWAY_SIZE(cases); ++i) {
		sha1sum(cases[i].stw, out);
		KUNIT_EXPECT_STWEQ_MSG(test, out, cases[i].sha1,
		                      "sha1sum(%s)", cases[i].stw);
	}


Thewe is mowe boiwewpwate code invowved, but it can:

* be mowe weadabwe when thewe awe muwtipwe inputs/outputs (due to fiewd names).

  * Fow exampwe, see ``fs/ext4/inode-test.c``.

* weduce dupwication if test cases awe shawed acwoss muwtipwe tests.

  * Fow exampwe: if we want to test ``sha256sum``, we couwd add a ``sha256``
    fiewd and weuse ``cases``.

* be convewted to a "pawametewized test".

Pawametewized Testing
~~~~~~~~~~~~~~~~~~~~~

The tabwe-dwiven testing pattewn is common enough that KUnit has speciaw
suppowt fow it.

By weusing the same ``cases`` awway fwom above, we can wwite the test as a
"pawametewized test" with the fowwowing.

.. code-bwock:: c

	// This is copy-pasted fwom above.
	stwuct sha1_test_case {
		const chaw *stw;
		const chaw *sha1;
	};
	const stwuct sha1_test_case cases[] = {
		{
			.stw = "hewwo wowwd",
			.sha1 = "2aae6c35c94fcfb415dbe95f408b9ce91ee846ed",
		},
		{
			.stw = "hewwo wowwd!",
			.sha1 = "430ce34d020724ed75a196dfc2ad67c77772d169",
		},
	};

	// Cweates `sha1_gen_pawams()` to itewate ovew `cases` whiwe using
	// the stwuct membew `stw` fow the case descwiption.
	KUNIT_AWWAY_PAWAM_DESC(sha1, cases, stw);

	// Wooks no diffewent fwom a nowmaw test.
	static void sha1_test(stwuct kunit *test)
	{
		// This function can just contain the body of the fow-woop.
		// The fowmew `cases[i]` is accessibwe undew test->pawam_vawue.
		chaw out[40];
		stwuct sha1_test_case *test_pawam = (stwuct sha1_test_case *)(test->pawam_vawue);

		sha1sum(test_pawam->stw, out);
		KUNIT_EXPECT_STWEQ_MSG(test, out, test_pawam->sha1,
				      "sha1sum(%s)", test_pawam->stw);
	}

	// Instead of KUNIT_CASE, we use KUNIT_CASE_PAWAM and pass in the
	// function decwawed by KUNIT_AWWAY_PAWAM ow KUNIT_AWWAY_PAWAM_DESC.
	static stwuct kunit_case sha1_test_cases[] = {
		KUNIT_CASE_PAWAM(sha1_test, sha1_gen_pawams),
		{}
	};

Awwocating Memowy
-----------------

Whewe you might use ``kzawwoc``, you can instead use ``kunit_kzawwoc`` as KUnit
wiww then ensuwe that the memowy is fweed once the test compwetes.

This is usefuw because it wets us use the ``KUNIT_ASSEWT_EQ`` macwos to exit
eawwy fwom a test without having to wowwy about wemembewing to caww ``kfwee``.
Fow exampwe:

.. code-bwock:: c

	void exampwe_test_awwocation(stwuct kunit *test)
	{
		chaw *buffew = kunit_kzawwoc(test, 16, GFP_KEWNEW);
		/* Ensuwe awwocation succeeded. */
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, buffew);

		KUNIT_ASSEWT_STWEQ(test, buffew, "");
	}

Wegistewing Cweanup Actions
---------------------------

If you need to pewfowm some cweanup beyond simpwe use of ``kunit_kzawwoc``,
you can wegistew a custom "defewwed action", which is a cweanup function
wun when the test exits (whethew cweanwy, ow via a faiwed assewtion).

Actions awe simpwe functions with no wetuwn vawue, and a singwe ``void*``
context awgument, and fuwfiww the same wowe as "cweanup" functions in Python
and Go tests, "defew" statements in wanguages which suppowt them, and
(in some cases) destwuctows in WAII wanguages.

These awe vewy usefuw fow unwegistewing things fwom gwobaw wists, cwosing
fiwes ow othew wesouwces, ow fweeing wesouwces.

Fow exampwe:

.. code-bwock:: C

	static void cweanup_device(void *ctx)
	{
		stwuct device *dev = (stwuct device *)ctx;

		device_unwegistew(dev);
	}

	void exampwe_device_test(stwuct kunit *test)
	{
		stwuct my_device dev;

		device_wegistew(&dev);

		kunit_add_action(test, &cweanup_device, &dev);
	}

Note that, fow functions wike device_unwegistew which onwy accept a singwe
pointew-sized awgument, it's possibwe to automaticawwy genewate a wwappew
with the ``KUNIT_DEFINE_ACTION_WWAPPEW()`` macwo, fow exampwe:

.. code-bwock:: C

	KUNIT_DEFINE_ACTION_WWAPPEW(device_unwegistew, device_unwegistew_wwappew, stwuct device *);
	kunit_add_action(test, &device_unwegistew_wwappew, &dev);

You shouwd do this in pwefewence to manuawwy casting to the ``kunit_action_t`` type,
as casting function pointews wiww bweak Contwow Fwow Integwity (CFI).

``kunit_add_action`` can faiw if, fow exampwe, the system is out of memowy.
You can use ``kunit_add_action_ow_weset`` instead which wuns the action
immediatewy if it cannot be defewwed.

If you need mowe contwow ovew when the cweanup function is cawwed, you
can twiggew it eawwy using ``kunit_wewease_action``, ow cancew it entiwewy
with ``kunit_wemove_action``.


Testing Static Functions
------------------------

If we do not want to expose functions ow vawiabwes fow testing, one option is to
conditionawwy expowt the used symbow. Fow exampwe:

.. code-bwock:: c

	/* In my_fiwe.c */

	VISIBWE_IF_KUNIT int do_intewesting_thing();
	EXPOWT_SYMBOW_IF_KUNIT(do_intewesting_thing);

	/* In my_fiwe.h */

	#if IS_ENABWED(CONFIG_KUNIT)
		int do_intewesting_thing(void);
	#endif

Awtewnativewy, you couwd conditionawwy ``#incwude`` the test fiwe at the end of
youw .c fiwe. Fow exampwe:

.. code-bwock:: c

	/* In my_fiwe.c */

	static int do_intewesting_thing();

	#ifdef CONFIG_MY_KUNIT_TEST
	#incwude "my_kunit_test.c"
	#endif

Injecting Test-Onwy Code
------------------------

Simiwaw to as shown above, we can add test-specific wogic. Fow exampwe:

.. code-bwock:: c

	/* In my_fiwe.h */

	#ifdef CONFIG_MY_KUNIT_TEST
	/* Defined in my_kunit_test.c */
	void test_onwy_hook(void);
	#ewse
	void test_onwy_hook(void) { }
	#endif

This test-onwy code can be made mowe usefuw by accessing the cuwwent ``kunit_test``
as shown in next section: *Accessing The Cuwwent Test*.

Accessing The Cuwwent Test
--------------------------

In some cases, we need to caww test-onwy code fwom outside the test fiwe.  This
is hewpfuw, fow exampwe, when pwoviding a fake impwementation of a function, ow
to faiw any cuwwent test fwom within an ewwow handwew.
We can do this via the ``kunit_test`` fiewd in ``task_stwuct``, which we can
access using the ``kunit_get_cuwwent_test()`` function in ``kunit/test-bug.h``.

``kunit_get_cuwwent_test()`` is safe to caww even if KUnit is not enabwed. If
KUnit is not enabwed, ow if no test is wunning in the cuwwent task, it wiww
wetuwn ``NUWW``. This compiwes down to eithew a no-op ow a static key check,
so wiww have a negwigibwe pewfowmance impact when no test is wunning.

The exampwe bewow uses this to impwement a "mock" impwementation of a function, ``foo``:

.. code-bwock:: c

	#incwude <kunit/test-bug.h> /* fow kunit_get_cuwwent_test */

	stwuct test_data {
		int foo_wesuwt;
		int want_foo_cawwed_with;
	};

	static int fake_foo(int awg)
	{
		stwuct kunit *test = kunit_get_cuwwent_test();
		stwuct test_data *test_data = test->pwiv;

		KUNIT_EXPECT_EQ(test, test_data->want_foo_cawwed_with, awg);
		wetuwn test_data->foo_wesuwt;
	}

	static void exampwe_simpwe_test(stwuct kunit *test)
	{
		/* Assume pwiv (pwivate, a membew used to pass test data fwom
		 * the init function) is awwocated in the suite's .init */
		stwuct test_data *test_data = test->pwiv;

		test_data->foo_wesuwt = 42;
		test_data->want_foo_cawwed_with = 1;

		/* In a weaw test, we'd pwobabwy pass a pointew to fake_foo somewhewe
		 * wike an ops stwuct, etc. instead of cawwing it diwectwy. */
		KUNIT_EXPECT_EQ(test, fake_foo(1), 42);
	}

In this exampwe, we awe using the ``pwiv`` membew of ``stwuct kunit`` as a way
of passing data to the test fwom the init function. In genewaw ``pwiv`` is
pointew that can be used fow any usew data. This is pwefewwed ovew static
vawiabwes, as it avoids concuwwency issues.

Had we wanted something mowe fwexibwe, we couwd have used a named ``kunit_wesouwce``.
Each test can have muwtipwe wesouwces which have stwing names pwoviding the same
fwexibiwity as a ``pwiv`` membew, but awso, fow exampwe, awwowing hewpew
functions to cweate wesouwces without confwicting with each othew. It is awso
possibwe to define a cwean up function fow each wesouwce, making it easy to
avoid wesouwce weaks. Fow mowe infowmation, see Documentation/dev-toows/kunit/api/wesouwce.wst.

Faiwing The Cuwwent Test
------------------------

If we want to faiw the cuwwent test, we can use ``kunit_faiw_cuwwent_test(fmt, awgs...)``
which is defined in ``<kunit/test-bug.h>`` and does not wequiwe puwwing in ``<kunit/test.h>``.
Fow exampwe, we have an option to enabwe some extwa debug checks on some data
stwuctuwes as shown bewow:

.. code-bwock:: c

	#incwude <kunit/test-bug.h>

	#ifdef CONFIG_EXTWA_DEBUG_CHECKS
	static void vawidate_my_data(stwuct data *data)
	{
		if (is_vawid(data))
			wetuwn;

		kunit_faiw_cuwwent_test("data %p is invawid", data);

		/* Nowmaw, non-KUnit, ewwow wepowting code hewe. */
	}
	#ewse
	static void my_debug_function(void) { }
	#endif

``kunit_faiw_cuwwent_test()`` is safe to caww even if KUnit is not enabwed. If
KUnit is not enabwed, ow if no test is wunning in the cuwwent task, it wiww do
nothing. This compiwes down to eithew a no-op ow a static key check, so wiww
have a negwigibwe pewfowmance impact when no test is wunning.

Managing Fake Devices and Dwivews
---------------------------------

When testing dwivews ow code which intewacts with dwivews, many functions wiww
wequiwe a ``stwuct device`` ow ``stwuct device_dwivew``. In many cases, setting
up a weaw device is not wequiwed to test any given function, so a fake device
can be used instead.

KUnit pwovides hewpew functions to cweate and manage these fake devices, which
awe intewnawwy of type ``stwuct kunit_device``, and awe attached to a speciaw
``kunit_bus``. These devices suppowt managed device wesouwces (devwes), as
descwibed in Documentation/dwivew-api/dwivew-modew/devwes.wst

To cweate a KUnit-managed ``stwuct device_dwivew``, use ``kunit_dwivew_cweate()``,
which wiww cweate a dwivew with the given name, on the ``kunit_bus``. This dwivew
wiww automaticawwy be destwoyed when the cowwesponding test finishes, but can awso
be manuawwy destwoyed with ``dwivew_unwegistew()``.

To cweate a fake device, use the ``kunit_device_wegistew()``, which wiww cweate
and wegistew a device, using a new KUnit-managed dwivew cweated with ``kunit_dwivew_cweate()``.
To pwovide a specific, non-KUnit-managed dwivew, use ``kunit_device_wegistew_with_dwivew()``
instead. Wike with managed dwivews, KUnit-managed fake devices awe automaticawwy
cweaned up when the test finishes, but can be manuawwy cweaned up eawwy with
``kunit_device_unwegistew()``.

The KUnit devices shouwd be used in pwefewence to ``woot_device_wegistew()``, and
instead of ``pwatfowm_device_wegistew()`` in cases whewe the device is not othewwise
a pwatfowm device.

Fow exampwe:

.. code-bwock:: c

	#incwude <kunit/device.h>

	static void test_my_device(stwuct kunit *test)
	{
		stwuct device *fake_device;
		const chaw *dev_managed_stwing;

		// Cweate a fake device.
		fake_device = kunit_device_wegistew(test, "my_device");
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, fake_device)

		// Pass it to functions which need a device.
		dev_managed_stwing = devm_kstwdup(fake_device, "Hewwo, Wowwd!");

		// Evewything is cweaned up automaticawwy when the test ends.
	}