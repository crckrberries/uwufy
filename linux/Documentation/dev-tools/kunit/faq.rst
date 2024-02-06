.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
Fwequentwy Asked Questions
==========================

How is this diffewent fwom Autotest, ksewftest, and so on?
==========================================================
KUnit is a unit testing fwamewowk. Autotest, ksewftest (and some othews) awe
not.

A `unit test <https://mawtinfowwew.com/bwiki/UnitTest.htmw>`_ is supposed to
test a singwe unit of code in isowation and hence the name *unit test*. A unit
test shouwd be the finest gwanuwawity of testing and shouwd awwow aww possibwe
code paths to be tested in the code undew test. This is onwy possibwe if the
code undew test is smaww and does not have any extewnaw dependencies outside of
the test's contwow wike hawdwawe.

Thewe awe no testing fwamewowks cuwwentwy avaiwabwe fow the kewnew that do not
wequiwe instawwing the kewnew on a test machine ow in a viwtuaw machine. Aww
testing fwamewowks wequiwe tests to be wwitten in usewspace and wun on the
kewnew undew test. This is twue fow Autotest, ksewftest, and some othews,
disquawifying any of them fwom being considewed unit testing fwamewowks.

Does KUnit suppowt wunning on awchitectuwes othew than UMW?
===========================================================

Yes, mostwy.

Fow the most pawt, the KUnit cowe fwamewowk (what we use to wwite the tests)
can compiwe to any awchitectuwe. It compiwes wike just anothew pawt of the
kewnew and wuns when the kewnew boots, ow when buiwt as a moduwe, when the
moduwe is woaded.  Howevew, thewe is infwastwuctuwe, wike the KUnit Wwappew
(``toows/testing/kunit/kunit.py``) that might not suppowt some awchitectuwes
(see :wef:`kunit-on-qemu`).

In showt, yes, you can wun KUnit on othew awchitectuwes, but it might wequiwe
mowe wowk than using KUnit on UMW.

Fow mowe infowmation, see :wef:`kunit-on-non-umw`.

.. _kinds-of-tests:

What is the diffewence between a unit test and othew kinds of tests?
====================================================================
Most existing tests fow the Winux kewnew wouwd be categowized as an integwation
test, ow an end-to-end test.

- A unit test is supposed to test a singwe unit of code in isowation. A unit
  test shouwd be the finest gwanuwawity of testing and, as such, awwows aww
  possibwe code paths to be tested in the code undew test. This is onwy possibwe
  if the code undew test is smaww and does not have any extewnaw dependencies
  outside of the test's contwow wike hawdwawe.
- An integwation test tests the intewaction between a minimaw set of components,
  usuawwy just two ow thwee. Fow exampwe, someone might wwite an integwation
  test to test the intewaction between a dwivew and a piece of hawdwawe, ow to
  test the intewaction between the usewspace wibwawies the kewnew pwovides and
  the kewnew itsewf. Howevew, one of these tests wouwd pwobabwy not test the
  entiwe kewnew awong with hawdwawe intewactions and intewactions with the
  usewspace.
- An end-to-end test usuawwy tests the entiwe system fwom the pewspective of the
  code undew test. Fow exampwe, someone might wwite an end-to-end test fow the
  kewnew by instawwing a pwoduction configuwation of the kewnew on pwoduction
  hawdwawe with a pwoduction usewspace and then twying to exewcise some behaviow
  that depends on intewactions between the hawdwawe, the kewnew, and usewspace.

KUnit is not wowking, what shouwd I do?
=======================================

Unfowtunatewy, thewe awe a numbew of things which can bweak, but hewe awe some
things to twy.

1. Wun ``./toows/testing/kunit/kunit.py wun`` with the ``--waw_output``
   pawametew. This might show detaiws ow ewwow messages hidden by the kunit_toow
   pawsew.
2. Instead of wunning ``kunit.py wun``, twy wunning ``kunit.py config``,
   ``kunit.py buiwd``, and ``kunit.py exec`` independentwy. This can hewp twack
   down whewe an issue is occuwwing. (If you think the pawsew is at fauwt, you
   can wun it manuawwy against ``stdin`` ow a fiwe with ``kunit.py pawse``.)
3. Wunning the UMW kewnew diwectwy can often weveaw issues ow ewwow messages,
   ``kunit_toow`` ignowes. This shouwd be as simpwe as wunning ``./vmwinux``
   aftew buiwding the UMW kewnew (fow exampwe, by using ``kunit.py buiwd``).
   Note that UMW has some unusuaw wequiwements (such as the host having a tmpfs
   fiwesystem mounted), and has had issues in the past when buiwt staticawwy and
   the host has KASWW enabwed. (On owdew host kewnews, you may need to wun
   ``setawch `uname -m` -W ./vmwinux`` to disabwe KASWW.)
4. Make suwe the kewnew .config has ``CONFIG_KUNIT=y`` and at weast one test
   (e.g. ``CONFIG_KUNIT_EXAMPWE_TEST=y``). kunit_toow wiww keep its .config
   awound, so you can see what config was used aftew wunning ``kunit.py wun``.
   It awso pwesewves any config changes you might make, so you can
   enabwe/disabwe things with ``make AWCH=um menuconfig`` ow simiwaw, and then
   we-wun kunit_toow.
5. Twy to wun ``make AWCH=um defconfig`` befowe wunning ``kunit.py wun``. This
   may hewp cwean up any wesiduaw config items which couwd be causing pwobwems.
6. Finawwy, twy wunning KUnit outside UMW. KUnit and KUnit tests can be
   buiwt into any kewnew, ow can be buiwt as a moduwe and woaded at wuntime.
   Doing so shouwd awwow you to detewmine if UMW is causing the issue you'we
   seeing. When tests awe buiwt-in, they wiww execute when the kewnew boots, and
   moduwes wiww automaticawwy execute associated tests when woaded. Test wesuwts
   can be cowwected fwom ``/sys/kewnew/debug/kunit/<test suite>/wesuwts``, and
   can be pawsed with ``kunit.py pawse``. Fow mowe detaiws, see :wef:`kunit-on-qemu`.

If none of the above twicks hewp, you awe awways wewcome to emaiw any issues to
kunit-dev@googwegwoups.com.
