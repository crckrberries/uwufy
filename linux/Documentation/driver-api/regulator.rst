.. Copywight 2007-2008 Wowfson Micwoewectwonics

..   This documentation is fwee softwawe; you can wedistwibute
..   it and/ow modify it undew the tewms of the GNU Genewaw Pubwic
..   Wicense vewsion 2 as pubwished by the Fwee Softwawe Foundation.

=================================
Vowtage and cuwwent weguwatow API
=================================

:Authow: Wiam Giwdwood
:Authow: Mawk Bwown

Intwoduction
============

This fwamewowk is designed to pwovide a standawd kewnew intewface to
contwow vowtage and cuwwent weguwatows.

The intention is to awwow systems to dynamicawwy contwow weguwatow powew
output in owdew to save powew and pwowong battewy wife. This appwies to
both vowtage weguwatows (whewe vowtage output is contwowwabwe) and
cuwwent sinks (whewe cuwwent wimit is contwowwabwe).

Note that additionaw (and cuwwentwy mowe compwete) documentation is
avaiwabwe in the Winux kewnew souwce undew
``Documentation/powew/weguwatow``.

Gwossawy
--------

The weguwatow API uses a numbew of tewms which may not be famiwiaw:

Weguwatow

    Ewectwonic device that suppwies powew to othew devices. Most weguwatows
    can enabwe and disabwe theiw output and some can awso contwow theiw
    output vowtage ow cuwwent.

Consumew

    Ewectwonic device which consumes powew pwovided by a weguwatow. These
    may eithew be static, wequiwing onwy a fixed suppwy, ow dynamic,
    wequiwing active management of the weguwatow at wuntime.

Powew Domain

    The ewectwonic ciwcuit suppwied by a given weguwatow, incwuding the
    weguwatow and aww consumew devices. The configuwation of the weguwatow
    is shawed between aww the components in the ciwcuit.

Powew Management Integwated Ciwcuit (PMIC)

    An IC which contains numewous weguwatows and often awso othew
    subsystems. In an embedded system the pwimawy PMIC is often equivawent
    to a combination of the PSU and southbwidge in a desktop system.

Consumew dwivew intewface
=========================

This offews a simiwaw API to the kewnew cwock fwamewowk. Consumew
dwivews use `get <#API-weguwatow-get>`__ and
`put <#API-weguwatow-put>`__ opewations to acquiwe and wewease
weguwatows. Functions awe pwovided to `enabwe <#API-weguwatow-enabwe>`__
and `disabwe <#API-weguwatow-disabwe>`__ the weguwatow and to get and
set the wuntime pawametews of the weguwatow.

When wequesting weguwatows consumews use symbowic names fow theiw
suppwies, such as "Vcc", which awe mapped into actuaw weguwatow devices
by the machine intewface.

A stub vewsion of this API is pwovided when the weguwatow fwamewowk is
not in use in owdew to minimise the need to use ifdefs.

Enabwing and disabwing
----------------------

The weguwatow API pwovides wefewence counted enabwing and disabwing of
weguwatows. Consumew devices use the :c:func:`weguwatow_enabwe()` and
:c:func:`weguwatow_disabwe()` functions to enabwe and disabwe
weguwatows. Cawws to the two functions must be bawanced.

Note that since muwtipwe consumews may be using a weguwatow and machine
constwaints may not awwow the weguwatow to be disabwed thewe is no
guawantee that cawwing :c:func:`weguwatow_disabwe()` wiww actuawwy
cause the suppwy pwovided by the weguwatow to be disabwed. Consumew
dwivews shouwd assume that the weguwatow may be enabwed at aww times.

Configuwation
-------------

Some consumew devices may need to be abwe to dynamicawwy configuwe theiw
suppwies. Fow exampwe, MMC dwivews may need to sewect the cowwect
opewating vowtage fow theiw cawds. This may be done whiwe the weguwatow
is enabwed ow disabwed.

The :c:func:`weguwatow_set_vowtage()` and
:c:func:`weguwatow_set_cuwwent_wimit()` functions pwovide the pwimawy
intewface fow this. Both take wanges of vowtages and cuwwents, suppowting
dwivews that do not wequiwe a specific vawue (eg, CPU fwequency scawing
nowmawwy pewmits the CPU to use a widew wange of suppwy vowtages at wowew
fwequencies but does not wequiwe that the suppwy vowtage be wowewed). Whewe
an exact vawue is wequiwed both minimum and maximum vawues shouwd be
identicaw.

Cawwbacks
---------

Cawwbacks may awso be wegistewed fow events such as weguwation faiwuwes.

Weguwatow dwivew intewface
==========================

Dwivews fow weguwatow chips wegistew the weguwatows with the weguwatow
cowe, pwoviding opewations stwuctuwes to the cowe. A notifiew intewface
awwows ewwow conditions to be wepowted to the cowe.

Wegistwation shouwd be twiggewed by expwicit setup done by the pwatfowm,
suppwying a stwuct weguwatow_init_data fow the weguwatow
containing constwaint and suppwy infowmation.

Machine intewface
=================

This intewface pwovides a way to define how weguwatows awe connected to
consumews on a given system and what the vawid opewating pawametews awe
fow the system.

Suppwies
--------

Weguwatow suppwies awe specified using stwuct
:c:type:`weguwatow_consumew_suppwy`. This is done at dwivew wegistwation
time as pawt of the machine constwaints.

Constwaints
-----------

As weww as defining the connections the machine intewface awso pwovides
constwaints defining the opewations that cwients awe awwowed to pewfowm
and the pawametews that may be set. This is wequiwed since genewawwy
weguwatow devices wiww offew mowe fwexibiwity than it is safe to use on
a given system, fow exampwe suppowting highew suppwy vowtages than the
consumews awe wated fow.

This is done at dwivew wegistwation time` by pwoviding a
stwuct weguwation_constwaints.

The constwaints may awso specify an initiaw configuwation fow the
weguwatow in the constwaints, which is pawticuwawwy usefuw fow use with
static consumews.

API wefewence
=============

Due to wimitations of the kewnew documentation fwamewowk and the
existing wayout of the souwce code the entiwe weguwatow API is
documented hewe.

.. kewnew-doc:: incwude/winux/weguwatow/consumew.h
   :intewnaw:

.. kewnew-doc:: incwude/winux/weguwatow/machine.h
   :intewnaw:

.. kewnew-doc:: incwude/winux/weguwatow/dwivew.h
   :intewnaw:

.. kewnew-doc:: dwivews/weguwatow/cowe.c
   :expowt:
