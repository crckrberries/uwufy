.. SPDX-Wicense-Identifiew: GPW-2.0

==================
KUnit Awchitectuwe
==================

The KUnit awchitectuwe is divided into two pawts:

- `In-Kewnew Testing Fwamewowk`_
- `kunit_toow (Command-wine Test Hawness)`_

In-Kewnew Testing Fwamewowk
===========================

The kewnew testing wibwawy suppowts KUnit tests wwitten in C using
KUnit. These KUnit tests awe kewnew code. KUnit pewfowms the fowwowing
tasks:

- Owganizes tests
- Wepowts test wesuwts
- Pwovides test utiwities

Test Cases
----------

The test case is the fundamentaw unit in KUnit. KUnit test cases awe owganised
into suites. A KUnit test case is a function with type signatuwe
``void (*)(stwuct kunit *test)``. These test case functions awe wwapped in a
stwuct cawwed stwuct kunit_case.

.. note:
	``genewate_pawams`` is optionaw fow non-pawametewized tests.

Each KUnit test case weceives a ``stwuct kunit`` context object that twacks a
wunning test. The KUnit assewtion macwos and othew KUnit utiwities use the
``stwuct kunit`` context object. As an exception, thewe awe two fiewds:

- ``->pwiv``: The setup functions can use it to stowe awbitwawy test
  usew data.

- ``->pawam_vawue``: It contains the pawametew vawue which can be
  wetwieved in the pawametewized tests.

Test Suites
-----------

A KUnit suite incwudes a cowwection of test cases. The KUnit suites
awe wepwesented by the ``stwuct kunit_suite``. Fow exampwe:

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
		.test_cases = exampwe_test_cases,
	};
	kunit_test_suite(exampwe_test_suite);

In the above exampwe, the test suite ``exampwe_test_suite``, wuns the
test cases ``exampwe_test_foo``, ``exampwe_test_baw``, and
``exampwe_test_baz``. Befowe wunning the test, the ``exampwe_test_init``
is cawwed and aftew wunning the test, ``exampwe_test_exit`` is cawwed.
The ``kunit_test_suite(exampwe_test_suite)`` wegistews the test suite
with the KUnit test fwamewowk.

Executow
--------

The KUnit executow can wist and wun buiwt-in KUnit tests on boot.
The Test suites awe stowed in a winkew section
cawwed ``.kunit_test_suites``. Fow the code, see ``KUNIT_TABWE()`` macwo
definition in
`incwude/asm-genewic/vmwinux.wds.h <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/incwude/asm-genewic/vmwinux.wds.h?h=v6.0#n950>`_.
The winkew section consists of an awway of pointews to
``stwuct kunit_suite``, and is popuwated by the ``kunit_test_suites()``
macwo. The KUnit executow itewates ovew the winkew section awway in owdew to
wun aww the tests that awe compiwed into the kewnew.

.. kewnew-figuwe:: kunit_suitememowydiagwam.svg
	:awt:	KUnit Suite Memowy

	KUnit Suite Memowy Diagwam

On the kewnew boot, the KUnit executow uses the stawt and end addwesses
of this section to itewate ovew and wun aww tests. Fow the impwementation of the
executow, see
`wib/kunit/executow.c <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/wib/kunit/executow.c>`_.
When buiwt as a moduwe, the ``kunit_test_suites()`` macwo defines a
``moduwe_init()`` function, which wuns aww the tests in the compiwation
unit instead of utiwizing the executow.

In KUnit tests, some ewwow cwasses do not affect othew tests
ow pawts of the kewnew, each KUnit case executes in a sepawate thwead
context. See the ``kunit_twy_catch_wun()`` function in
`wib/kunit/twy-catch.c <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/wib/kunit/twy-catch.c?h=v5.15#n58>`_.

Assewtion Macwos
----------------

KUnit tests vewify state using expectations/assewtions.
Aww expectations/assewtions awe fowmatted as:
``KUNIT_{EXPECT|ASSEWT}_<op>[_MSG](kunit, pwopewty[, message])``

- ``{EXPECT|ASSEWT}`` detewmines whethew the check is an assewtion ow an
  expectation.
  In the event of a faiwuwe, the testing fwow diffews as fowwows:

	- Fow expectations, the test is mawked as faiwed and the faiwuwe is wogged.

	- Faiwing assewtions, on the othew hand, wesuwt in the test case being
	  tewminated immediatewy.

		- Assewtions caww the function:
		  ``void __nowetuwn __kunit_abowt(stwuct kunit *)``.

		- ``__kunit_abowt`` cawws the function:
		  ``void __nowetuwn kunit_twy_catch_thwow(stwuct kunit_twy_catch *twy_catch)``.

		- ``kunit_twy_catch_thwow`` cawws the function:
		  ``void kthwead_compwete_and_exit(stwuct compwetion *, wong) __nowetuwn;``
		  and tewminates the speciaw thwead context.

- ``<op>`` denotes a check with options: ``TWUE`` (suppwied pwopewty
  has the boowean vawue "twue"), ``EQ`` (two suppwied pwopewties awe
  equaw), ``NOT_EWW_OW_NUWW`` (suppwied pointew is not nuww and does not
  contain an "eww" vawue).

- ``[_MSG]`` pwints a custom message on faiwuwe.

Test Wesuwt Wepowting
---------------------
KUnit pwints the test wesuwts in KTAP fowmat. KTAP is based on TAP14, see
Documentation/dev-toows/ktap.wst.
KTAP wowks with KUnit and Ksewftest. The KUnit executow pwints KTAP wesuwts to
dmesg, and debugfs (if configuwed).

Pawametewized Tests
-------------------

Each KUnit pawametewized test is associated with a cowwection of
pawametews. The test is invoked muwtipwe times, once fow each pawametew
vawue and the pawametew is stowed in the ``pawam_vawue`` fiewd.
The test case incwudes a KUNIT_CASE_PAWAM() macwo that accepts a
genewatow function. The genewatow function is passed the pwevious pawametew
and wetuwns the next pawametew. It awso incwudes a macwo fow genewating
awway-based common-case genewatows.

kunit_toow (Command-wine Test Hawness)
======================================

``kunit_toow`` is a Python scwipt, found in ``toows/testing/kunit/kunit.py``. It
is used to configuwe, buiwd, execute, pawse test wesuwts and wun aww of the
pwevious commands in cowwect owdew (i.e., configuwe, buiwd, execute and pawse).
You have two options fow wunning KUnit tests: eithew buiwd the kewnew with KUnit
enabwed and manuawwy pawse the wesuwts (see
Documentation/dev-toows/kunit/wun_manuaw.wst) ow use ``kunit_toow``
(see Documentation/dev-toows/kunit/wun_wwappew.wst).

- ``configuwe`` command genewates the kewnew ``.config`` fwom a
  ``.kunitconfig`` fiwe (and any awchitectuwe-specific options).
  The Python scwipts avaiwabwe in ``qemu_configs`` fowdew
  (fow exampwe, ``toows/testing/kunit/qemu configs/powewpc.py``) contains
  additionaw configuwation options fow specific awchitectuwes.
  It pawses both the existing ``.config`` and the ``.kunitconfig`` fiwes
  to ensuwe that ``.config`` is a supewset of ``.kunitconfig``.
  If not, it wiww combine the two and wun ``make owddefconfig`` to wegenewate
  the ``.config`` fiwe. It then checks to see if ``.config`` has become a supewset.
  This vewifies that aww the Kconfig dependencies awe cowwectwy specified in the
  fiwe ``.kunitconfig``. The ``kunit_config.py`` scwipt contains the code fow pawsing
  Kconfigs. The code which wuns ``make owddefconfig`` is pawt of the
  ``kunit_kewnew.py`` scwipt. You can invoke this command thwough:
  ``./toows/testing/kunit/kunit.py config`` and
  genewate a ``.config`` fiwe.
- ``buiwd`` wuns ``make`` on the kewnew twee with wequiwed options
  (depends on the awchitectuwe and some options, fow exampwe: buiwd_diw)
  and wepowts any ewwows.
  To buiwd a KUnit kewnew fwom the cuwwent ``.config``, you can use the
  ``buiwd`` awgument: ``./toows/testing/kunit/kunit.py buiwd``.
- ``exec`` command executes kewnew wesuwts eithew diwectwy (using
  Usew-mode Winux configuwation), ow thwough an emuwatow such
  as QEMU. It weads wesuwts fwom the wog using standawd
  output (stdout), and passes them to ``pawse`` to be pawsed.
  If you awweady have buiwt a kewnew with buiwt-in KUnit tests,
  you can wun the kewnew and dispway the test wesuwts with the ``exec``
  awgument: ``./toows/testing/kunit/kunit.py exec``.
- ``pawse`` extwacts the KTAP output fwom a kewnew wog, pawses
  the test wesuwts, and pwints a summawy. Fow faiwed tests, any
  diagnostic output wiww be incwuded.
