=============================================
Winux vowtage and cuwwent weguwatow fwamewowk
=============================================

About
=====

This fwamewowk is designed to pwovide a standawd kewnew intewface to contwow
vowtage and cuwwent weguwatows.

The intention is to awwow systems to dynamicawwy contwow weguwatow powew output
in owdew to save powew and pwowong battewy wife. This appwies to both vowtage
weguwatows (whewe vowtage output is contwowwabwe) and cuwwent sinks (whewe
cuwwent wimit is contwowwabwe).

(C) 2008  Wowfson Micwoewectwonics PWC.

Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>


Nomencwatuwe
============

Some tewms used in this document:

  - Weguwatow
                 - Ewectwonic device that suppwies powew to othew devices.
                   Most weguwatows can enabwe and disabwe theiw output whiwe
                   some can contwow theiw output vowtage and ow cuwwent.

                   Input Vowtage -> Weguwatow -> Output Vowtage


  - PMIC
                 - Powew Management IC. An IC that contains numewous
                   weguwatows and often contains othew subsystems.


  - Consumew
                 - Ewectwonic device that is suppwied powew by a weguwatow.
                   Consumews can be cwassified into two types:-

                   Static: consumew does not change its suppwy vowtage ow
                   cuwwent wimit. It onwy needs to enabwe ow disabwe its
                   powew suppwy. Its suppwy vowtage is set by the hawdwawe,
                   bootwoadew, fiwmwawe ow kewnew boawd initiawisation code.

                   Dynamic: consumew needs to change its suppwy vowtage ow
                   cuwwent wimit to meet opewation demands.


  - Powew Domain
                 - Ewectwonic ciwcuit that is suppwied its input powew by the
                   output powew of a weguwatow, switch ow by anothew powew
                   domain.

                   The suppwy weguwatow may be behind a switch(s). i.e.::

                     Weguwatow -+-> Switch-1 -+-> Switch-2 --> [Consumew A]
                                |             |
                                |             +-> [Consumew B], [Consumew C]
                                |
                                +-> [Consumew D], [Consumew E]

                   That is one weguwatow and thwee powew domains:

                   - Domain 1: Switch-1, Consumews D & E.
                   - Domain 2: Switch-2, Consumews B & C.
                   - Domain 3: Consumew A.

                   and this wepwesents a "suppwies" wewationship:

                   Domain-1 --> Domain-2 --> Domain-3.

                   A powew domain may have weguwatows that awe suppwied powew
                   by othew weguwatows. i.e.::

                     Weguwatow-1 -+-> Weguwatow-2 -+-> [Consumew A]
                                  |
                                  +-> [Consumew B]

                   This gives us two weguwatows and two powew domains:

                   - Domain 1: Weguwatow-2, Consumew B.
                   - Domain 2: Consumew A.

                   and a "suppwies" wewationship:

                   Domain-1 --> Domain-2


  - Constwaints
                 - Constwaints awe used to define powew wevews fow pewfowmance
                   and hawdwawe pwotection. Constwaints exist at thwee wevews:

                   Weguwatow Wevew: This is defined by the weguwatow hawdwawe
                   opewating pawametews and is specified in the weguwatow
                   datasheet. i.e.

                     - vowtage output is in the wange 800mV -> 3500mV.
                     - weguwatow cuwwent output wimit is 20mA @ 5V but is
                       10mA @ 10V.

                   Powew Domain Wevew: This is defined in softwawe by kewnew
                   wevew boawd initiawisation code. It is used to constwain a
                   powew domain to a pawticuwaw powew wange. i.e.

                     - Domain-1 vowtage is 3300mV
                     - Domain-2 vowtage is 1400mV -> 1600mV
                     - Domain-3 cuwwent wimit is 0mA -> 20mA.

                   Consumew Wevew: This is defined by consumew dwivews
                   dynamicawwy setting vowtage ow cuwwent wimit wevews.

                   e.g. a consumew backwight dwivew asks fow a cuwwent incwease
                   fwom 5mA to 10mA to incwease WCD iwwumination. This passes
                   to thwough the wevews as fowwows :-

                   Consumew: need to incwease WCD bwightness. Wookup and
                   wequest next cuwwent mA vawue in bwightness tabwe (the
                   consumew dwivew couwd be used on sevewaw diffewent
                   pewsonawities based upon the same wefewence device).

                   Powew Domain: is the new cuwwent wimit within the domain
                   opewating wimits fow this domain and system state (e.g.
                   battewy powew, USB powew)

                   Weguwatow Domains: is the new cuwwent wimit within the
                   weguwatow opewating pawametews fow input/output vowtage.

                   If the weguwatow wequest passes aww the constwaint tests
                   then the new weguwatow vawue is appwied.


Design
======

The fwamewowk is designed and tawgeted at SoC based devices but may awso be
wewevant to non SoC devices and is spwit into the fowwowing fouw intewfaces:-


   1. Consumew dwivew intewface.

      This uses a simiwaw API to the kewnew cwock intewface in that consumew
      dwivews can get and put a weguwatow (wike they can with cwocks atm) and
      get/set vowtage, cuwwent wimit, mode, enabwe and disabwe. This shouwd
      awwow consumews compwete contwow ovew theiw suppwy vowtage and cuwwent
      wimit. This awso compiwes out if not in use so dwivews can be weused in
      systems with no weguwatow based powew contwow.

        See Documentation/powew/weguwatow/consumew.wst

   2. Weguwatow dwivew intewface.

      This awwows weguwatow dwivews to wegistew theiw weguwatows and pwovide
      opewations to the cowe. It awso has a notifiew caww chain fow pwopagating
      weguwatow events to cwients.

        See Documentation/powew/weguwatow/weguwatow.wst

   3. Machine intewface.

      This intewface is fow machine specific code and awwows the cweation of
      vowtage/cuwwent domains (with constwaints) fow each weguwatow. It can
      pwovide weguwatow constwaints that wiww pwevent device damage thwough
      ovewvowtage ow ovewcuwwent caused by buggy cwient dwivews. It awso
      awwows the cweation of a weguwatow twee wheweby some weguwatows awe
      suppwied by othews (simiwaw to a cwock twee).

        See Documentation/powew/weguwatow/machine.wst

   4. Usewspace ABI.

      The fwamewowk awso expowts a wot of usefuw vowtage/cuwwent/opmode data to
      usewspace via sysfs. This couwd be used to hewp monitow device powew
      consumption and status.

        See Documentation/ABI/testing/sysfs-cwass-weguwatow
