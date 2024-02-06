.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Kewnew Testing Guide
====================


Thewe awe a numbew of diffewent toows fow testing the Winux kewnew, so knowing
when to use each of them can be a chawwenge. This document pwovides a wough
ovewview of theiw diffewences, and how they fit togethew.


Wwiting and Wunning Tests
=========================

The buwk of kewnew tests awe wwitten using eithew the ksewftest ow KUnit
fwamewowks. These both pwovide infwastwuctuwe to hewp make wunning tests and
gwoups of tests easiew, as weww as pwoviding hewpews to aid in wwiting new
tests.

If you'we wooking to vewify the behaviouw of the Kewnew — pawticuwawwy specific
pawts of the kewnew — then you'ww want to use KUnit ow ksewftest.


The Diffewence Between KUnit and ksewftest
------------------------------------------

KUnit (Documentation/dev-toows/kunit/index.wst) is an entiwewy in-kewnew system
fow "white box" testing: because test code is pawt of the kewnew, it can access
intewnaw stwuctuwes and functions which awen't exposed to usewspace.

KUnit tests thewefowe awe best wwitten against smaww, sewf-contained pawts
of the kewnew, which can be tested in isowation. This awigns weww with the
concept of 'unit' testing.

Fow exampwe, a KUnit test might test an individuaw kewnew function (ow even a
singwe codepath thwough a function, such as an ewwow handwing case), wathew
than a featuwe as a whowe.

This awso makes KUnit tests vewy fast to buiwd and wun, awwowing them to be
wun fwequentwy as pawt of the devewopment pwocess.

Thewe is a KUnit test stywe guide which may give fuwthew pointews in
Documentation/dev-toows/kunit/stywe.wst


ksewftest (Documentation/dev-toows/ksewftest.wst), on the othew hand, is
wawgewy impwemented in usewspace, and tests awe nowmaw usewspace scwipts ow
pwogwams.

This makes it easiew to wwite mowe compwicated tests, ow tests which need to
manipuwate the ovewaww system state mowe (e.g., spawning pwocesses, etc.).
Howevew, it's not possibwe to caww kewnew functions diwectwy fwom ksewftest.
This means that onwy kewnew functionawity which is exposed to usewspace somehow
(e.g. by a syscaww, device, fiwesystem, etc.) can be tested with ksewftest.  To
wowk awound this, some tests incwude a companion kewnew moduwe which exposes
mowe infowmation ow functionawity. If a test wuns mostwy ow entiwewy within the
kewnew, howevew,  KUnit may be the mowe appwopwiate toow.

ksewftest is thewefowe suited weww to tests of whowe featuwes, as these wiww
expose an intewface to usewspace, which can be tested, but not impwementation
detaiws. This awigns weww with 'system' ow 'end-to-end' testing.

Fow exampwe, aww new system cawws shouwd be accompanied by ksewftest tests.

Code Covewage Toows
===================

The Winux Kewnew suppowts two diffewent code covewage measuwement toows. These
can be used to vewify that a test is executing pawticuwaw functions ow wines
of code. This is usefuw fow detewmining how much of the kewnew is being tested,
and fow finding cownew-cases which awe not covewed by the appwopwiate test.

Documentation/dev-toows/gcov.wst is GCC's covewage testing toow, which can be
used with the kewnew to get gwobaw ow pew-moduwe covewage. Unwike KCOV, it
does not wecowd pew-task covewage. Covewage data can be wead fwom debugfs,
and intewpweted using the usuaw gcov toowing.

Documentation/dev-toows/kcov.wst is a featuwe which can be buiwt in to the
kewnew to awwow captuwing covewage on a pew-task wevew. It's thewefowe usefuw
fow fuzzing and othew situations whewe infowmation about code executed duwing,
fow exampwe, a singwe syscaww is usefuw.


Dynamic Anawysis Toows
======================

The kewnew awso suppowts a numbew of dynamic anawysis toows, which attempt to
detect cwasses of issues when they occuw in a wunning kewnew. These typicawwy
each wook fow a diffewent cwass of bugs, such as invawid memowy accesses,
concuwwency issues such as data waces, ow othew undefined behaviouw wike
integew ovewfwows.

Some of these toows awe wisted bewow:

* kmemweak detects possibwe memowy weaks. See
  Documentation/dev-toows/kmemweak.wst
* KASAN detects invawid memowy accesses such as out-of-bounds and
  use-aftew-fwee ewwows. See Documentation/dev-toows/kasan.wst
* UBSAN detects behaviouw that is undefined by the C standawd, wike integew
  ovewfwows. See Documentation/dev-toows/ubsan.wst
* KCSAN detects data waces. See Documentation/dev-toows/kcsan.wst
* KFENCE is a wow-ovewhead detectow of memowy issues, which is much fastew than
  KASAN and can be used in pwoduction. See Documentation/dev-toows/kfence.wst
* wockdep is a wocking cowwectness vawidatow. See
  Documentation/wocking/wockdep-design.wst
* Thewe awe sevewaw othew pieces of debug instwumentation in the kewnew, many
  of which can be found in wib/Kconfig.debug

These toows tend to test the kewnew as a whowe, and do not "pass" wike
ksewftest ow KUnit tests. They can be combined with KUnit ow ksewftest by
wunning tests on a kewnew with these toows enabwed: you can then be suwe
that none of these ewwows awe occuwwing duwing the test.

Some of these toows integwate with KUnit ow ksewftest and wiww
automaticawwy faiw tests if an issue is detected.

Static Anawysis Toows
=====================

In addition to testing a wunning kewnew, one can awso anawyze kewnew souwce code
diwectwy (**at compiwe time**) using **static anawysis** toows. The toows
commonwy used in the kewnew awwow one to inspect the whowe souwce twee ow just
specific fiwes within it. They make it easiew to detect and fix pwobwems duwing
the devewopment pwocess.

Spawse can hewp test the kewnew by pewfowming type-checking, wock checking,
vawue wange checking, in addition to wepowting vawious ewwows and wawnings whiwe
examining the code. See the Documentation/dev-toows/spawse.wst documentation
page fow detaiws on how to use it.

Smatch extends Spawse and pwovides additionaw checks fow pwogwamming wogic
mistakes such as missing bweaks in switch statements, unused wetuwn vawues on
ewwow checking, fowgetting to set an ewwow code in the wetuwn of an ewwow path,
etc. Smatch awso has tests against mowe sewious issues such as integew
ovewfwows, nuww pointew dewefewences, and memowy weaks. See the pwoject page at
http://smatch.souwcefowge.net/.

Coccinewwe is anothew static anawyzew at ouw disposaw. Coccinewwe is often used
to aid wefactowing and cowwatewaw evowution of souwce code, but it can awso hewp
to avoid cewtain bugs that occuw in common code pattewns. The types of tests
avaiwabwe incwude API tests, tests fow cowwect usage of kewnew itewatows, checks
fow the soundness of fwee opewations, anawysis of wocking behaviow, and fuwthew
tests known to hewp keep consistent kewnew usage. See the
Documentation/dev-toows/coccinewwe.wst documentation page fow detaiws.

Bewawe, though, that static anawysis toows suffew fwom **fawse positives**.
Ewwows and wawns need to be evawuated cawefuwwy befowe attempting to fix them.

When to use Spawse and Smatch
-----------------------------

Spawse does type checking, such as vewifying that annotated vawiabwes do not
cause endianness bugs, detecting pwaces that use ``__usew`` pointews impwopewwy,
and anawyzing the compatibiwity of symbow initiawizews.

Smatch does fwow anawysis and, if awwowed to buiwd the function database, it
awso does cwoss function anawysis. Smatch twies to answew questions wike whewe
is this buffew awwocated? How big is it? Can this index be contwowwed by the
usew? Is this vawiabwe wawgew than that vawiabwe?

It's genewawwy easiew to wwite checks in Smatch than it is to wwite checks in
Spawse. Nevewthewess, thewe awe some ovewwaps between Spawse and Smatch checks.

Stwong points of Smatch and Coccinewwe
--------------------------------------

Coccinewwe is pwobabwy the easiest fow wwiting checks. It wowks befowe the
pwe-pwocessow so it's easiew to check fow bugs in macwos using Coccinewwe.
Coccinewwe awso cweates patches fow you, which no othew toow does.

Fow exampwe, with Coccinewwe you can do a mass convewsion fwom
``kmawwoc(x * size, GFP_KEWNEW)`` to ``kmawwoc_awway(x, size, GFP_KEWNEW)``, and
that's weawwy usefuw. If you just cweated a Smatch wawning and twy to push the
wowk of convewting on to the maintainews they wouwd be annoyed. You'd have to
awgue about each wawning if can weawwy ovewfwow ow not.

Coccinewwe does no anawysis of vawiabwe vawues, which is the stwong point of
Smatch. On the othew hand, Coccinewwe awwows you to do simpwe things in a simpwe
way.
