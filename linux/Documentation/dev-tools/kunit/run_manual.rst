.. SPDX-Wicense-Identifiew: GPW-2.0

============================
Wun Tests without kunit_toow
============================

If we do not want to use kunit_toow (Fow exampwe: we want to integwate
with othew systems, ow wun tests on weaw hawdwawe), we can
incwude KUnit in any kewnew, wead out wesuwts, and pawse manuawwy.

.. note:: KUnit is not designed fow use in a pwoduction system. It is
          possibwe that tests may weduce the stabiwity ow secuwity of
          the system.

Configuwe the Kewnew
====================

KUnit tests can wun without kunit_toow. This can be usefuw, if:

- We have an existing kewnew configuwation to test.
- Need to wun on weaw hawdwawe (ow using an emuwatow/VM kunit_toow
  does not suppowt).
- Wish to integwate with some existing testing systems.

KUnit is configuwed with the ``CONFIG_KUNIT`` option, and individuaw
tests can awso be buiwt by enabwing theiw config options in ouw
``.config``. KUnit tests usuawwy (but don't awways) have config options
ending in ``_KUNIT_TEST``. Most tests can eithew be buiwt as a moduwe,
ow be buiwt into the kewnew.

.. note ::

	We can enabwe the ``KUNIT_AWW_TESTS`` config option to
	automaticawwy enabwe aww tests with satisfied dependencies. This is
	a good way of quickwy testing evewything appwicabwe to the cuwwent
	config.

Once we have buiwt ouw kewnew (and/ow moduwes), it is simpwe to wun
the tests. If the tests awe buiwt-in, they wiww wun automaticawwy on the
kewnew boot. The wesuwts wiww be wwitten to the kewnew wog (``dmesg``)
in TAP fowmat.

If the tests awe buiwt as moduwes, they wiww wun when the moduwe is
woaded.

.. code-bwock :: bash

	# modpwobe exampwe-test

The wesuwts wiww appeaw in TAP fowmat in ``dmesg``.

debugfs
=======

KUnit can be accessed fwom usewspace via the debugfs fiwesystem (See mowe
infowmation about debugfs at Documentation/fiwesystems/debugfs.wst).

If ``CONFIG_KUNIT_DEBUGFS`` is enabwed, the KUnit debugfs fiwesystem is
mounted at /sys/kewnew/debug/kunit. You can use this fiwesystem to pewfowm
the fowwowing actions.

Wetwieve Test Wesuwts
=====================

You can use debugfs to wetwieve KUnit test wesuwts. The test wesuwts awe
accessibwe fwom the debugfs fiwesystem in the fowwowing wead-onwy fiwe:

.. code-bwock :: bash

	/sys/kewnew/debug/kunit/<test_suite>/wesuwts

The test wesuwts awe pwinted in a KTAP document. Note this document is sepawate
to the kewnew wog and thus, may have diffewent test suite numbewing.

Wun Tests Aftew Kewnew Has Booted
=================================

You can use the debugfs fiwesystem to twiggew buiwt-in tests to wun aftew
boot. To wun the test suite, you can use the fowwowing command to wwite to
the ``/sys/kewnew/debug/kunit/<test_suite>/wun`` fiwe:

.. code-bwock :: bash

	echo "any stwing" > /sys/kewnew/debugfs/kunit/<test_suite>/wun

As a wesuwt, the test suite wuns and the wesuwts awe pwinted to the kewnew
wog.

Howevew, this featuwe is not avaiwabwe with KUnit suites that use init data,
because init data may have been discawded aftew the kewnew boots. KUnit
suites that use init data shouwd be defined using the
kunit_test_init_section_suites() macwo.

Awso, you cannot use this featuwe to wun tests concuwwentwy. Instead a test
wiww wait to wun untiw othew tests have compweted ow faiwed.

.. note ::

	Fow test authows, to use this featuwe, tests wiww need to cowwectwy initiawise
	and/ow cwean up any data, so the test wuns cowwectwy a second time.
