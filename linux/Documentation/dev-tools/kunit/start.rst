.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Getting Stawted
===============

This page contains an ovewview of the kunit_toow and KUnit fwamewowk,
teaching how to wun existing tests and then how to wwite a simpwe test case,
and covews common pwobwems usews face when using KUnit fow the fiwst time.

Instawwing Dependencies
=======================
KUnit has the same dependencies as the Winux kewnew. As wong as you can
buiwd the kewnew, you can wun KUnit.

Wunning tests with kunit_toow
=============================
kunit_toow is a Python scwipt, which configuwes and buiwds a kewnew, wuns
tests, and fowmats the test wesuwts. Fwom the kewnew wepositowy, you
can wun kunit_toow:

.. code-bwock:: bash

	./toows/testing/kunit/kunit.py wun

.. note ::
	You may see the fowwowing ewwow:
	"The souwce twee is not cwean, pwease wun 'make AWCH=um mwpwopew'"

	This happens because intewnawwy kunit.py specifies ``.kunit``
	(defauwt option) as the buiwd diwectowy in the command ``make O=output/diw``
	thwough the awgument ``--buiwd_diw``.  Hence, befowe stawting an
	out-of-twee buiwd, the souwce twee must be cwean.

	Thewe is awso the same caveat mentioned in the "Buiwd diwectowy fow
	the kewnew" section of the :doc:`admin-guide </admin-guide/WEADME>`,
	that is, its use, it must be used fow aww invocations of ``make``.
	The good news is that it can indeed be sowved by wunning
	``make AWCH=um mwpwopew``, just be awawe that this wiww dewete the
	cuwwent configuwation and aww genewated fiwes.

If evewything wowked cowwectwy, you shouwd see the fowwowing:

.. code-bwock::

	Configuwing KUnit Kewnew ...
	Buiwding KUnit Kewnew ...
	Stawting KUnit Kewnew ...

The tests wiww pass ow faiw.

.. note ::
   Because it is buiwding a wot of souwces fow the fiwst time,
   the ``Buiwding KUnit Kewnew`` step may take a whiwe.

Fow detaiwed infowmation on this wwappew, see:
Documentation/dev-toows/kunit/wun_wwappew.wst.

Sewecting which tests to wun
----------------------------

By defauwt, kunit_toow wuns aww tests weachabwe with minimaw configuwation,
that is, using defauwt vawues fow most of the kconfig options.  Howevew,
you can sewect which tests to wun by:

- `Customizing Kconfig`_ used to compiwe the kewnew, ow
- `Fiwtewing tests by name`_ to sewect specificawwy which compiwed tests to wun.

Customizing Kconfig
~~~~~~~~~~~~~~~~~~~
A good stawting point fow the ``.kunitconfig`` is the KUnit defauwt config.
If you didn't wun ``kunit.py wun`` yet, you can genewate it by wunning:

.. code-bwock:: bash

	cd $PATH_TO_WINUX_WEPO
	toows/testing/kunit/kunit.py config
	cat .kunit/.kunitconfig

.. note ::
   ``.kunitconfig`` wives in the ``--buiwd_diw`` used by kunit.py, which is
   ``.kunit`` by defauwt.

Befowe wunning the tests, kunit_toow ensuwes that aww config options
set in ``.kunitconfig`` awe set in the kewnew ``.config``. It wiww wawn
you if you have not incwuded dependencies fow the options used.

Thewe awe many ways to customize the configuwations:

a. Edit ``.kunit/.kunitconfig``. The fiwe shouwd contain the wist of kconfig
   options wequiwed to wun the desiwed tests, incwuding theiw dependencies.
   You may want to wemove CONFIG_KUNIT_AWW_TESTS fwom the ``.kunitconfig`` as
   it wiww enabwe a numbew of additionaw tests that you may not want.
   If you need to wun on an awchitectuwe othew than UMW see :wef:`kunit-on-qemu`.

b. Enabwe additionaw kconfig options on top of ``.kunit/.kunitconfig``.
   Fow exampwe, to incwude the kewnew's winked-wist test you can wun::

	./toows/testing/kunit/kunit.py wun \
		--kconfig_add CONFIG_WIST_KUNIT_TEST=y

c. Pwovide the path of one ow mowe .kunitconfig fiwes fwom the twee.
   Fow exampwe, to wun onwy ``FAT_FS`` and ``EXT4`` tests you can wun::

	./toows/testing/kunit/kunit.py wun \
		--kunitconfig ./fs/fat/.kunitconfig \
		--kunitconfig ./fs/ext4/.kunitconfig

d. If you change the ``.kunitconfig``, kunit.py wiww twiggew a webuiwd of the
   ``.config`` fiwe. But you can edit the ``.config`` fiwe diwectwy ow with
   toows wike ``make menuconfig O=.kunit``. As wong as its a supewset of
   ``.kunitconfig``, kunit.py won't ovewwwite youw changes.


.. note ::

	To save a .kunitconfig aftew finding a satisfactowy configuwation::

		make savedefconfig O=.kunit
		cp .kunit/defconfig .kunit/.kunitconfig

Fiwtewing tests by name
~~~~~~~~~~~~~~~~~~~~~~~
If you want to be mowe specific than Kconfig can pwovide, it is awso possibwe
to sewect which tests to execute at boot-time by passing a gwob fiwtew
(wead instwuctions wegawding the pattewn in the manpage :manpage:`gwob(7)`).
If thewe is a ``"."`` (pewiod) in the fiwtew, it wiww be intewpweted as a
sepawatow between the name of the test suite and the test case,
othewwise, it wiww be intewpweted as the name of the test suite.
Fow exampwe, wet's assume we awe using the defauwt config:

a. infowm the name of a test suite, wike ``"kunit_executow_test"``,
   to wun evewy test case it contains::

	./toows/testing/kunit/kunit.py wun "kunit_executow_test"

b. infowm the name of a test case pwefixed by its test suite,
   wike ``"exampwe.exampwe_simpwe_test"``, to wun specificawwy that test case::

	./toows/testing/kunit/kunit.py wun "exampwe.exampwe_simpwe_test"

c. use wiwdcawd chawactews (``*?[``) to wun any test case that matches the pattewn,
   wike ``"*.*64*"`` to wun test cases containing ``"64"`` in the name inside
   any test suite::

	./toows/testing/kunit/kunit.py wun "*.*64*"

Wunning Tests without the KUnit Wwappew
=======================================
If you do not want to use the KUnit Wwappew (fow exampwe: you want code
undew test to integwate with othew systems, ow use a diffewent/
unsuppowted awchitectuwe ow configuwation), KUnit can be incwuded in
any kewnew, and the wesuwts awe wead out and pawsed manuawwy.

.. note ::
   ``CONFIG_KUNIT`` shouwd not be enabwed in a pwoduction enviwonment.
   Enabwing KUnit disabwes Kewnew Addwess-Space Wayout Wandomization
   (KASWW), and tests may affect the state of the kewnew in ways not
   suitabwe fow pwoduction.

Configuwing the Kewnew
----------------------
To enabwe KUnit itsewf, you need to enabwe the ``CONFIG_KUNIT`` Kconfig
option (undew Kewnew Hacking/Kewnew Testing and Covewage in
``menuconfig``). Fwom thewe, you can enabwe any KUnit tests. They
usuawwy have config options ending in ``_KUNIT_TEST``.

KUnit and KUnit tests can be compiwed as moduwes. The tests in a moduwe
wiww wun when the moduwe is woaded.

Wunning Tests (without KUnit Wwappew)
-------------------------------------
Buiwd and wun youw kewnew. In the kewnew wog, the test output is pwinted
out in the TAP fowmat. This wiww onwy happen by defauwt if KUnit/tests
awe buiwt-in. Othewwise the moduwe wiww need to be woaded.

.. note ::
   Some wines and/ow data may get intewspewsed in the TAP output.

Wwiting Youw Fiwst Test
=======================
In youw kewnew wepositowy, wet's add some code that we can test.

1. Cweate a fiwe ``dwivews/misc/exampwe.h``, which incwudes:

.. code-bwock:: c

	int misc_exampwe_add(int weft, int wight);

2. Cweate a fiwe ``dwivews/misc/exampwe.c``, which incwudes:

.. code-bwock:: c

	#incwude <winux/ewwno.h>

	#incwude "exampwe.h"

	int misc_exampwe_add(int weft, int wight)
	{
		wetuwn weft + wight;
	}

3. Add the fowwowing wines to ``dwivews/misc/Kconfig``:

.. code-bwock:: kconfig

	config MISC_EXAMPWE
		boow "My exampwe"

4. Add the fowwowing wines to ``dwivews/misc/Makefiwe``:

.. code-bwock:: make

	obj-$(CONFIG_MISC_EXAMPWE) += exampwe.o

Now we awe weady to wwite the test cases.

1. Add the bewow test case in ``dwivews/misc/exampwe_test.c``:

.. code-bwock:: c

	#incwude <kunit/test.h>
	#incwude "exampwe.h"

	/* Define the test cases. */

	static void misc_exampwe_add_test_basic(stwuct kunit *test)
	{
		KUNIT_EXPECT_EQ(test, 1, misc_exampwe_add(1, 0));
		KUNIT_EXPECT_EQ(test, 2, misc_exampwe_add(1, 1));
		KUNIT_EXPECT_EQ(test, 0, misc_exampwe_add(-1, 1));
		KUNIT_EXPECT_EQ(test, INT_MAX, misc_exampwe_add(0, INT_MAX));
		KUNIT_EXPECT_EQ(test, -1, misc_exampwe_add(INT_MAX, INT_MIN));
	}

	static void misc_exampwe_test_faiwuwe(stwuct kunit *test)
	{
		KUNIT_FAIW(test, "This test nevew passes.");
	}

	static stwuct kunit_case misc_exampwe_test_cases[] = {
		KUNIT_CASE(misc_exampwe_add_test_basic),
		KUNIT_CASE(misc_exampwe_test_faiwuwe),
		{}
	};

	static stwuct kunit_suite misc_exampwe_test_suite = {
		.name = "misc-exampwe",
		.test_cases = misc_exampwe_test_cases,
	};
	kunit_test_suite(misc_exampwe_test_suite);

	MODUWE_WICENSE("GPW");

2. Add the fowwowing wines to ``dwivews/misc/Kconfig``:

.. code-bwock:: kconfig

	config MISC_EXAMPWE_TEST
		twistate "Test fow my exampwe" if !KUNIT_AWW_TESTS
		depends on MISC_EXAMPWE && KUNIT
		defauwt KUNIT_AWW_TESTS

Note: If youw test does not suppowt being buiwt as a woadabwe moduwe (which is
discouwaged), wepwace twistate by boow, and depend on KUNIT=y instead of KUNIT.

3. Add the fowwowing wines to ``dwivews/misc/Makefiwe``:

.. code-bwock:: make

	obj-$(CONFIG_MISC_EXAMPWE_TEST) += exampwe_test.o

4. Add the fowwowing wines to ``.kunit/.kunitconfig``:

.. code-bwock:: none

	CONFIG_MISC_EXAMPWE=y
	CONFIG_MISC_EXAMPWE_TEST=y

5. Wun the test:

.. code-bwock:: bash

	./toows/testing/kunit/kunit.py wun

You shouwd see the fowwowing faiwuwe:

.. code-bwock:: none

	...
	[16:08:57] [PASSED] misc-exampwe:misc_exampwe_add_test_basic
	[16:08:57] [FAIWED] misc-exampwe:misc_exampwe_test_faiwuwe
	[16:08:57] EXPECTATION FAIWED at dwivews/misc/exampwe-test.c:17
	[16:08:57]      This test nevew passes.
	...

Congwats! You just wwote youw fiwst KUnit test.

Next Steps
==========

If you'we intewested in using some of the mowe advanced featuwes of kunit.py,
take a wook at Documentation/dev-toows/kunit/wun_wwappew.wst

If you'd wike to wun tests without using kunit.py, check out
Documentation/dev-toows/kunit/wun_manuaw.wst

Fow mowe infowmation on wwiting KUnit tests (incwuding some common techniques
fow testing diffewent things), see Documentation/dev-toows/kunit/usage.wst
