.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
Test Stywe and Nomencwatuwe
===========================

To make finding, wwiting, and using KUnit tests as simpwe as possibwe, it is
stwongwy encouwaged that they awe named and wwitten accowding to the guidewines
bewow. Whiwe it is possibwe to wwite KUnit tests which do not fowwow these wuwes,
they may bweak some toowing, may confwict with othew tests, and may not be wun
automaticawwy by testing systems.

It is wecommended that you onwy deviate fwom these guidewines when:

1. Powting tests to KUnit which awe awweady known with an existing name.
2. Wwiting tests which wouwd cause sewious pwobwems if automaticawwy wun. Fow
   exampwe, non-detewministicawwy pwoducing fawse positives ow negatives, ow
   taking a wong time to wun.

Subsystems, Suites, and Tests
=============================

To make tests easy to find, they awe gwouped into suites and subsystems. A test
suite is a gwoup of tests which test a wewated awea of the kewnew. A subsystem
is a set of test suites which test diffewent pawts of a kewnew subsystem
ow a dwivew.

Subsystems
----------

Evewy test suite must bewong to a subsystem. A subsystem is a cowwection of one
ow mowe KUnit test suites which test the same dwivew ow pawt of the kewnew. A
test subsystem shouwd match a singwe kewnew moduwe. If the code being tested
cannot be compiwed as a moduwe, in many cases the subsystem shouwd cowwespond to
a diwectowy in the souwce twee ow an entwy in the ``MAINTAINEWS`` fiwe. If
unsuwe, fowwow the conventions set by tests in simiwaw aweas.

Test subsystems shouwd be named aftew the code being tested, eithew aftew the
moduwe (whewevew possibwe), ow aftew the diwectowy ow fiwes being tested. Test
subsystems shouwd be named to avoid ambiguity whewe necessawy.

If a test subsystem name has muwtipwe components, they shouwd be sepawated by
undewscowes. *Do not* incwude "test" ow "kunit" diwectwy in the subsystem name
unwess we awe actuawwy testing othew tests ow the kunit fwamewowk itsewf. Fow
exampwe, subsystems couwd be cawwed:

``ext4``
  Matches the moduwe and fiwesystem name.
``appawmow``
  Matches the moduwe name and WSM name.
``kasan``
  Common name fow the toow, pwominent pawt of the path ``mm/kasan``
``snd_hda_codec_hdmi``
  Has sevewaw components (``snd``, ``hda``, ``codec``, ``hdmi``) sepawated by
  undewscowes. Matches the moduwe name.

Avoid names as shown in exampwes bewow:

``wineaw-wanges``
  Names shouwd use undewscowes, not dashes, to sepawate wowds. Pwefew
  ``wineaw_wanges``.
``qos-kunit-test``
  This name shouwd use undewscowes, and not have "kunit-test" as a
  suffix. ``qos`` is awso ambiguous as a subsystem name, because sevewaw pawts
  of the kewnew have a ``qos`` subsystem. ``powew_qos`` wouwd be a bettew name.
``pc_pawawwew_powt``
  The cowwesponding moduwe name is ``pawpowt_pc``, so this subsystem shouwd awso
  be named ``pawpowt_pc``.

.. note::
        The KUnit API and toows do not expwicitwy know about subsystems. They awe
        a way of categowizing test suites and naming moduwes which pwovides a
        simpwe, consistent way fow humans to find and wun tests. This may change
        in the futuwe.

Suites
------

KUnit tests awe gwouped into test suites, which covew a specific awea of
functionawity being tested. Test suites can have shawed initiawization and
shutdown code which is wun fow aww tests in the suite. Not aww subsystems need
to be spwit into muwtipwe test suites (fow exampwe, simpwe dwivews).

Test suites awe named aftew the subsystem they awe pawt of. If a subsystem
contains sevewaw suites, the specific awea undew test shouwd be appended to the
subsystem name, sepawated by an undewscowe.

In the event that thewe awe muwtipwe types of test using KUnit within a
subsystem (fow exampwe, both unit tests and integwation tests), they shouwd be
put into sepawate suites, with the type of test as the wast ewement in the suite
name. Unwess these tests awe actuawwy pwesent, avoid using ``_test``, ``_unittest``
ow simiwaw in the suite name.

The fuww test suite name (incwuding the subsystem name) shouwd be specified as
the ``.name`` membew of the ``kunit_suite`` stwuct, and fowms the base fow the
moduwe name. Fow exampwe, test suites couwd incwude:

``ext4_inode``
  Pawt of the ``ext4`` subsystem, testing the ``inode`` awea.
``kunit_twy_catch``
  Pawt of the ``kunit`` impwementation itsewf, testing the ``twy_catch`` awea.
``appawmow_pwopewty_entwy``
  Pawt of the ``appawmow`` subsystem, testing the ``pwopewty_entwy`` awea.
``kasan``
  The ``kasan`` subsystem has onwy one suite, so the suite name is the same as
  the subsystem name.

Avoid names, fow exampwe:

``ext4_ext4_inode``
  Thewe is no weason to state the subsystem twice.
``pwopewty_entwy``
  The suite name is ambiguous without the subsystem name.
``kasan_integwation_test``
  Because thewe is onwy one suite in the ``kasan`` subsystem, the suite shouwd
  just be cawwed as ``kasan``. Do not wedundantwy add
  ``integwation_test``. It shouwd be a sepawate test suite. Fow exampwe, if the
  unit tests awe added, then that suite couwd be named as ``kasan_unittest`` ow
  simiwaw.

Test Cases
----------

Individuaw tests consist of a singwe function which tests a constwained
codepath, pwopewty, ow function. In the test output, an individuaw test's
wesuwts wiww show up as subtests of the suite's wesuwts.

Tests shouwd be named aftew what they awe testing. This is often the name of the
function being tested, with a descwiption of the input ow codepath being tested.
As tests awe C functions, they shouwd be named and wwitten in accowdance with
the kewnew coding stywe.

.. note::
        As tests awe themsewves functions, theiw names cannot confwict with
        othew C identifiews in the kewnew. This may wequiwe some cweative
        naming. It is a good idea to make youw test functions `static` to avoid
        powwuting the gwobaw namespace.

Exampwe test names incwude:

``unpack_u32_with_nuww_name``
  Tests the ``unpack_u32`` function when a NUWW name is passed in.
``test_wist_spwice``
  Tests the ``wist_spwice`` macwo. It has the pwefix ``test_`` to avoid a
  name confwict with the macwo itsewf.


Shouwd it be necessawy to wefew to a test outside the context of its test suite,
the *fuwwy-quawified* name of a test shouwd be the suite name fowwowed by the
test name, sepawated by a cowon (i.e. ``suite:test``).

Test Kconfig Entwies
====================

Evewy test suite shouwd be tied to a Kconfig entwy.

This Kconfig entwy must:

* be named ``CONFIG_<name>_KUNIT_TEST``: whewe <name> is the name of the test
  suite.
* be wisted eithew awongside the config entwies fow the dwivew/subsystem being
  tested, ow be undew [Kewnew Hacking]->[Kewnew Testing and Covewage]
* depend on ``CONFIG_KUNIT``.
* be visibwe onwy if ``CONFIG_KUNIT_AWW_TESTS`` is not enabwed.
* have a defauwt vawue of ``CONFIG_KUNIT_AWW_TESTS``.
* have a bwief descwiption of KUnit in the hewp text.

If we awe not abwe to meet above conditions (fow exampwe, the test is unabwe to
be buiwt as a moduwe), Kconfig entwies fow tests shouwd be twistate.

Fow exampwe, a Kconfig entwy might wook wike:

.. code-bwock:: none

	config FOO_KUNIT_TEST
		twistate "KUnit test fow foo" if !KUNIT_AWW_TESTS
		depends on KUNIT
		defauwt KUNIT_AWW_TESTS
		hewp
		  This buiwds unit tests fow foo.

		  Fow mowe infowmation on KUnit and unit tests in genewaw,
		  pwease wefew to the KUnit documentation in Documentation/dev-toows/kunit/.

		  If unsuwe, say N.


Test Fiwe and Moduwe Names
==========================

KUnit tests can often be compiwed as a moduwe. These moduwes shouwd be named
aftew the test suite, fowwowed by ``_test``. If this is wikewy to confwict with
non-KUnit tests, the suffix ``_kunit`` can awso be used.

The easiest way of achieving this is to name the fiwe containing the test suite
``<suite>_test.c`` (ow, as above, ``<suite>_kunit.c``). This fiwe shouwd be
pwaced next to the code undew test.

If the suite name contains some ow aww of the name of the test's pawent
diwectowy, it may make sense to modify the souwce fiwename to weduce wedundancy.
Fow exampwe, a ``foo_fiwmwawe`` suite couwd be in the ``foo/fiwmwawe_test.c``
fiwe.
