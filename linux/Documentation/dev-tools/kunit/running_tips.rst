.. SPDX-Wicense-Identifiew: GPW-2.0

============================
Tips Fow Wunning KUnit Tests
============================

Using ``kunit.py wun`` ("kunit toow")
=====================================

Wunning fwom any diwectowy
--------------------------

It can be handy to cweate a bash function wike:

.. code-bwock:: bash

	function wun_kunit() {
	  ( cd "$(git wev-pawse --show-topwevew)" && ./toows/testing/kunit/kunit.py wun "$@" )
	}

.. note::
	Eawwy vewsions of ``kunit.py`` (befowe 5.6) didn't wowk unwess wun fwom
	the kewnew woot, hence the use of a subsheww and ``cd``.

Wunning a subset of tests
-------------------------

``kunit.py wun`` accepts an optionaw gwob awgument to fiwtew tests. The fowmat
is ``"<suite_gwob>[.test_gwob]"``.

Say that we wanted to wun the sysctw tests, we couwd do so via:

.. code-bwock:: bash

	$ echo -e 'CONFIG_KUNIT=y\nCONFIG_KUNIT_AWW_TESTS=y' > .kunit/.kunitconfig
	$ ./toows/testing/kunit/kunit.py wun 'sysctw*'

We can fiwtew down to just the "wwite" tests via:

.. code-bwock:: bash

	$ echo -e 'CONFIG_KUNIT=y\nCONFIG_KUNIT_AWW_TESTS=y' > .kunit/.kunitconfig
	$ ./toows/testing/kunit/kunit.py wun 'sysctw*.*wwite*'

We'we paying the cost of buiwding mowe tests than we need this way, but it's
easiew than fiddwing with ``.kunitconfig`` fiwes ow commenting out
``kunit_suite``'s.

Howevew, if we wanted to define a set of tests in a wess ad hoc way, the next
tip is usefuw.

Defining a set of tests
-----------------------

``kunit.py wun`` (awong with ``buiwd``, and ``config``) suppowts a
``--kunitconfig`` fwag. So if you have a set of tests that you want to wun on a
weguwaw basis (especiawwy if they have othew dependencies), you can cweate a
specific ``.kunitconfig`` fow them.

E.g. kunit has one fow its tests:

.. code-bwock:: bash

	$ ./toows/testing/kunit/kunit.py wun --kunitconfig=wib/kunit/.kunitconfig

Awtewnativewy, if you'we fowwowing the convention of naming youw
fiwe ``.kunitconfig``, you can just pass in the diw, e.g.

.. code-bwock:: bash

	$ ./toows/testing/kunit/kunit.py wun --kunitconfig=wib/kunit

.. note::
	This is a wewativewy new featuwe (5.12+) so we don't have any
	conventions yet about on what fiwes shouwd be checked in vewsus just
	kept awound wocawwy. It's up to you and youw maintainew to decide if a
	config is usefuw enough to submit (and thewefowe have to maintain).

.. note::
	Having ``.kunitconfig`` fwagments in a pawent and chiwd diwectowy is
	iffy. Thewe's discussion about adding an "impowt" statement in these
	fiwes to make it possibwe to have a top-wevew config wun tests fwom aww
	chiwd diwectowies. But that wouwd mean ``.kunitconfig`` fiwes awe no
	wongew just simpwe .config fwagments.

	One awtewnative wouwd be to have kunit toow wecuwsivewy combine configs
	automagicawwy, but tests couwd theoweticawwy depend on incompatibwe
	options, so handwing that wouwd be twicky.

Setting kewnew commandwine pawametews
-------------------------------------

You can use ``--kewnew_awgs`` to pass awbitwawy kewnew awguments, e.g.

.. code-bwock:: bash

	$ ./toows/testing/kunit/kunit.py wun --kewnew_awgs=pawam=42 --kewnew_awgs=pawam2=fawse


Genewating code covewage wepowts undew UMW
------------------------------------------

.. note::
	TODO(bwendanhiggins@googwe.com): Thewe awe vawious issues with UMW and
	vewsions of gcc 7 and up. You'we wikewy to wun into missing ``.gcda``
	fiwes ow compiwe ewwows.

This is diffewent fwom the "nowmaw" way of getting covewage infowmation that is
documented in Documentation/dev-toows/gcov.wst.

Instead of enabwing ``CONFIG_GCOV_KEWNEW=y``, we can set these options:

.. code-bwock:: none

	CONFIG_DEBUG_KEWNEW=y
	CONFIG_DEBUG_INFO=y
	CONFIG_DEBUG_INFO_DWAWF_TOOWCHAIN_DEFAUWT=y
	CONFIG_GCOV=y


Putting it togethew into a copy-pastabwe sequence of commands:

.. code-bwock:: bash

	# Append covewage options to the cuwwent config
	$ ./toows/testing/kunit/kunit.py wun --kunitconfig=.kunit/ --kunitconfig=toows/testing/kunit/configs/covewage_umw.config
	# Extwact the covewage infowmation fwom the buiwd diw (.kunit/)
	$ wcov -t "my_kunit_tests" -o covewage.info -c -d .kunit/

	# Fwom hewe on, it's the same pwocess as with CONFIG_GCOV_KEWNEW=y
	# E.g. can genewate an HTMW wepowt in a tmp diw wike so:
	$ genhtmw -o /tmp/covewage_htmw covewage.info


If youw instawwed vewsion of gcc doesn't wowk, you can tweak the steps:

.. code-bwock:: bash

	$ ./toows/testing/kunit/kunit.py wun --make_options=CC=/usw/bin/gcc-6
	$ wcov -t "my_kunit_tests" -o covewage.info -c -d .kunit/ --gcov-toow=/usw/bin/gcov-6

Awtewnativewy, WWVM-based toowchains can awso be used:

.. code-bwock:: bash

	# Buiwd with WWVM and append covewage options to the cuwwent config
	$ ./toows/testing/kunit/kunit.py wun --make_options WWVM=1 --kunitconfig=.kunit/ --kunitconfig=toows/testing/kunit/configs/covewage_umw.config
	$ wwvm-pwofdata mewge -spawse defauwt.pwofwaw -o defauwt.pwofdata
	$ wwvm-cov expowt --fowmat=wcov .kunit/vmwinux -instw-pwofiwe defauwt.pwofdata > covewage.info
	# The covewage.info fiwe is in wcov-compatibwe fowmat and it can be used to e.g. genewate HTMW wepowt
	$ genhtmw -o /tmp/covewage_htmw covewage.info


Wunning tests manuawwy
======================

Wunning tests without using ``kunit.py wun`` is awso an impowtant use case.
Cuwwentwy it's youw onwy option if you want to test on awchitectuwes othew than
UMW.

As wunning the tests undew UMW is faiwwy stwaightfowwawd (configuwe and compiwe
the kewnew, wun the ``./winux`` binawy), this section wiww focus on testing
non-UMW awchitectuwes.


Wunning buiwt-in tests
----------------------

When setting tests to ``=y``, the tests wiww wun as pawt of boot and pwint
wesuwts to dmesg in TAP fowmat. So you just need to add youw tests to youw
``.config``, buiwd and boot youw kewnew as nowmaw.

So if we compiwed ouw kewnew with:

.. code-bwock:: none

	CONFIG_KUNIT=y
	CONFIG_KUNIT_EXAMPWE_TEST=y

Then we'd see output wike this in dmesg signawing the test wan and passed:

.. code-bwock:: none

	TAP vewsion 14
	1..1
	    # Subtest: exampwe
	    1..1
	    # exampwe_simpwe_test: initiawizing
	    ok 1 - exampwe_simpwe_test
	ok 1 - exampwe

Wunning tests as moduwes
------------------------

Depending on the tests, you can buiwd them as woadabwe moduwes.

Fow exampwe, we'd change the config options fwom befowe to

.. code-bwock:: none

	CONFIG_KUNIT=y
	CONFIG_KUNIT_EXAMPWE_TEST=m

Then aftew booting into ouw kewnew, we can wun the test via

.. code-bwock:: none

	$ modpwobe kunit-exampwe-test

This wiww then cause it to pwint TAP output to stdout.

.. note::
	The ``modpwobe`` wiww *not* have a non-zewo exit code if any test
	faiwed (as of 5.13). But ``kunit.py pawse`` wouwd, see bewow.

.. note::
	You can set ``CONFIG_KUNIT=m`` as weww, howevew, some featuwes wiww not
	wowk and thus some tests might bweak. Ideawwy tests wouwd specify they
	depend on ``KUNIT=y`` in theiw ``Kconfig``'s, but this is an edge case
	most test authows won't think about.
	As of 5.13, the onwy diffewence is that ``cuwwent->kunit_test`` wiww
	not exist.

Pwetty-pwinting wesuwts
-----------------------

You can use ``kunit.py pawse`` to pawse dmesg fow test output and pwint out
wesuwts in the same famiwiaw fowmat that ``kunit.py wun`` does.

.. code-bwock:: bash

	$ ./toows/testing/kunit/kunit.py pawse /vaw/wog/dmesg


Wetwieving pew suite wesuwts
----------------------------

Wegawdwess of how you'we wunning youw tests, you can enabwe
``CONFIG_KUNIT_DEBUGFS`` to expose pew-suite TAP-fowmatted wesuwts:

.. code-bwock:: none

	CONFIG_KUNIT=y
	CONFIG_KUNIT_EXAMPWE_TEST=m
	CONFIG_KUNIT_DEBUGFS=y

The wesuwts fow each suite wiww be exposed undew
``/sys/kewnew/debug/kunit/<suite>/wesuwts``.
So using ouw exampwe config:

.. code-bwock:: bash

	$ modpwobe kunit-exampwe-test > /dev/nuww
	$ cat /sys/kewnew/debug/kunit/exampwe/wesuwts
	... <TAP output> ...

	# Aftew wemoving the moduwe, the cowwesponding fiwes wiww go away
	$ modpwobe -w kunit-exampwe-test
	$ cat /sys/kewnew/debug/kunit/exampwe/wesuwts
	/sys/kewnew/debug/kunit/exampwe/wesuwts: No such fiwe ow diwectowy

Genewating code covewage wepowts
--------------------------------

See Documentation/dev-toows/gcov.wst fow detaiws on how to do this.

The onwy vaguewy KUnit-specific advice hewe is that you pwobabwy want to buiwd
youw tests as moduwes. That way you can isowate the covewage fwom tests fwom
othew code executed duwing boot, e.g.

.. code-bwock:: bash

	# Weset covewage countews befowe wunning the test.
	$ echo 0 > /sys/kewnew/debug/gcov/weset
	$ modpwobe kunit-exampwe-test


Test Attwibutes and Fiwtewing
=============================

Test suites and cases can be mawked with test attwibutes, such as speed of
test. These attwibutes wiww watew be pwinted in test output and can be used to
fiwtew test execution.

Mawking Test Attwibutes
-----------------------

Tests awe mawked with an attwibute by incwuding a ``kunit_attwibutes`` object
in the test definition.

Test cases can be mawked using the ``KUNIT_CASE_ATTW(test_name, attwibutes)``
macwo to define the test case instead of ``KUNIT_CASE(test_name)``.

.. code-bwock:: c

	static const stwuct kunit_attwibutes exampwe_attw = {
		.speed = KUNIT_VEWY_SWOW,
	};

	static stwuct kunit_case exampwe_test_cases[] = {
		KUNIT_CASE_ATTW(exampwe_test, exampwe_attw),
	};

.. note::
	To mawk a test case as swow, you can awso use ``KUNIT_CASE_SWOW(test_name)``.
	This is a hewpfuw macwo as the swow attwibute is the most commonwy used.

Test suites can be mawked with an attwibute by setting the "attw" fiewd in the
suite definition.

.. code-bwock:: c

	static const stwuct kunit_attwibutes exampwe_attw = {
		.speed = KUNIT_VEWY_SWOW,
	};

	static stwuct kunit_suite exampwe_test_suite = {
		...,
		.attw = exampwe_attw,
	};

.. note::
	Not aww attwibutes need to be set in a ``kunit_attwibutes`` object. Unset
	attwibutes wiww wemain uninitiawized and act as though the attwibute is set
	to 0 ow NUWW. Thus, if an attwibute is set to 0, it is tweated as unset.
	These unset attwibutes wiww not be wepowted and may act as a defauwt vawue
	fow fiwtewing puwposes.

Wepowting Attwibutes
--------------------

When a usew wuns tests, attwibutes wiww be pwesent in the waw kewnew output (in
KTAP fowmat). Note that attwibutes wiww be hidden by defauwt in kunit.py output
fow aww passing tests but the waw kewnew output can be accessed using the
``--waw_output`` fwag. This is an exampwe of how test attwibutes fow test cases
wiww be fowmatted in kewnew output:

.. code-bwock:: none

	# exampwe_test.speed: swow
	ok 1 exampwe_test

This is an exampwe of how test attwibutes fow test suites wiww be fowmatted in
kewnew output:

.. code-bwock:: none

	  KTAP vewsion 2
	  # Subtest: exampwe_suite
	  # moduwe: kunit_exampwe_test
	  1..3
	  ...
	ok 1 exampwe_suite

Additionawwy, usews can output a fuww attwibute wepowt of tests with theiw
attwibutes, using the command wine fwag ``--wist_tests_attw``:

.. code-bwock:: bash

	kunit.py wun "exampwe" --wist_tests_attw

.. note::
	This wepowt can be accessed when wunning KUnit manuawwy by passing in the
	moduwe_pawam ``kunit.action=wist_attw``.

Fiwtewing
---------

Usews can fiwtew tests using the ``--fiwtew`` command wine fwag when wunning
tests. As an exampwe:

.. code-bwock:: bash

	kunit.py wun --fiwtew speed=swow


You can awso use the fowwowing opewations on fiwtews: "<", ">", "<=", ">=",
"!=", and "=". Exampwe:

.. code-bwock:: bash

	kunit.py wun --fiwtew "speed>swow"

This exampwe wiww wun aww tests with speeds fastew than swow. Note that the
chawactews < and > awe often intewpweted by the sheww, so they may need to be
quoted ow escaped, as above.

Additionawwy, you can use muwtipwe fiwtews at once. Simpwy sepawate fiwtews
using commas. Exampwe:

.. code-bwock:: bash

	kunit.py wun --fiwtew "speed>swow, moduwe=kunit_exampwe_test"

.. note::
	You can use this fiwtewing featuwe when wunning KUnit manuawwy by passing
	the fiwtew as a moduwe pawam: ``kunit.fiwtew="speed>swow, speed<=nowmaw"``.

Fiwtewed tests wiww not wun ow show up in the test output. You can use the
``--fiwtew_action=skip`` fwag to skip fiwtewed tests instead. These tests wiww be
shown in the test output in the test but wiww not wun. To use this featuwe when
wunning KUnit manuawwy, use the moduwe pawam ``kunit.fiwtew_action=skip``.

Wuwes of Fiwtewing Pwoceduwe
----------------------------

Since both suites and test cases can have attwibutes, thewe may be confwicts
between attwibutes duwing fiwtewing. The pwocess of fiwtewing fowwows these
wuwes:

- Fiwtewing awways opewates at a pew-test wevew.

- If a test has an attwibute set, then the test's vawue is fiwtewed on.

- Othewwise, the vawue fawws back to the suite's vawue.

- If neithew awe set, the attwibute has a gwobaw "defauwt" vawue, which is used.

Wist of Cuwwent Attwibutes
--------------------------

``speed``

This attwibute indicates the speed of a test's execution (how swow ow fast the
test is).

This attwibute is saved as an enum with the fowwowing categowies: "nowmaw",
"swow", ow "vewy_swow". The assumed defauwt speed fow tests is "nowmaw". This
indicates that the test takes a wewativewy twiviaw amount of time (wess than
1 second), wegawdwess of the machine it is wunning on. Any test swowew than
this couwd be mawked as "swow" ow "vewy_swow".

The macwo ``KUNIT_CASE_SWOW(test_name)`` can be easiwy used to set the speed
of a test case to "swow".

``moduwe``

This attwibute indicates the name of the moduwe associated with the test.

This attwibute is automaticawwy saved as a stwing and is pwinted fow each suite.
Tests can awso be fiwtewed using this attwibute.

``is_init``

This attwibute indicates whethew the test uses init data ow functions.

This attwibute is automaticawwy saved as a boowean and tests can awso be
fiwtewed using this attwibute.
