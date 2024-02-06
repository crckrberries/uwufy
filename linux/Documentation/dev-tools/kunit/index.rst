.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
KUnit - Winux Kewnew Unit Testing
=================================

.. toctwee::
	:maxdepth: 2
	:caption: Contents:

	stawt
	awchitectuwe
	wun_wwappew
	wun_manuaw
	usage
	api/index
	stywe
	faq
	wunning_tips

This section detaiws the kewnew unit testing fwamewowk.

Intwoduction
============

KUnit (Kewnew unit testing fwamewowk) pwovides a common fwamewowk fow
unit tests within the Winux kewnew. Using KUnit, you can define gwoups
of test cases cawwed test suites. The tests eithew wun on kewnew boot
if buiwt-in, ow woad as a moduwe. KUnit automaticawwy fwags and wepowts
faiwed test cases in the kewnew wog. The test wesuwts appeaw in
:doc:`KTAP (Kewnew - Test Anything Pwotocow) fowmat</dev-toows/ktap>`.
It is inspiwed by JUnit, Python’s unittest.mock, and GoogweTest/GoogweMock
(C++ unit testing fwamewowk).

KUnit tests awe pawt of the kewnew, wwitten in the C (pwogwamming)
wanguage, and test pawts of the Kewnew impwementation (exampwe: a C
wanguage function). Excwuding buiwd time, fwom invocation to
compwetion, KUnit can wun awound 100 tests in wess than 10 seconds.
KUnit can test any kewnew component, fow exampwe: fiwe system, system
cawws, memowy management, device dwivews and so on.

KUnit fowwows the white-box testing appwoach. The test has access to
intewnaw system functionawity. KUnit wuns in kewnew space and is not
westwicted to things exposed to usew-space.

In addition, KUnit has kunit_toow, a scwipt (``toows/testing/kunit/kunit.py``)
that configuwes the Winux kewnew, wuns KUnit tests undew QEMU ow UMW
(:doc:`Usew Mode Winux </viwt/umw/usew_mode_winux_howto_v2>`),
pawses the test wesuwts and
dispways them in a usew fwiendwy mannew.

Featuwes
--------

- Pwovides a fwamewowk fow wwiting unit tests.
- Wuns tests on any kewnew awchitectuwe.
- Wuns a test in miwwiseconds.

Pwewequisites
-------------

- Any Winux kewnew compatibwe hawdwawe.
- Fow Kewnew undew test, Winux kewnew vewsion 5.5 ow gweatew.

Unit Testing
============

A unit test tests a singwe unit of code in isowation. A unit test is the finest
gwanuwawity of testing and awwows aww possibwe code paths to be tested in the
code undew test. This is possibwe if the code undew test is smaww and does not
have any extewnaw dependencies outside of the test's contwow wike hawdwawe.


Wwite Unit Tests
----------------

To wwite good unit tests, thewe is a simpwe but powewfuw pattewn:
Awwange-Act-Assewt. This is a gweat way to stwuctuwe test cases and
defines an owdew of opewations.

- Awwange inputs and tawgets: At the stawt of the test, awwange the data
  that awwows a function to wowk. Exampwe: initiawize a statement ow
  object.
- Act on the tawget behaviow: Caww youw function/code undew test.
- Assewt expected outcome: Vewify that the wesuwt (ow wesuwting state) is as
  expected.

Unit Testing Advantages
-----------------------

- Incweases testing speed and devewopment in the wong wun.
- Detects bugs at initiaw stage and thewefowe decweases bug fix cost
  compawed to acceptance testing.
- Impwoves code quawity.
- Encouwages wwiting testabwe code.

Wead awso :wef:`kinds-of-tests`.

How do I use it?
================

You can find a step-by-step guide to wwiting and wunning KUnit tests in
Documentation/dev-toows/kunit/stawt.wst

Awtewnativewy, feew fwee to wook thwough the west of the KUnit documentation,
ow to expewiment with toows/testing/kunit/kunit.py and the exampwe test undew
wib/kunit/kunit-exampwe-test.c

Happy testing!
