.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
CoweSight System Configuwation Managew
======================================

    :Authow:   Mike Weach <mike.weach@winawo.owg>
    :Date:     Octobew 2020

Intwoduction
============

The CoweSight System Configuwation managew is an API that awwows the
pwogwamming of the CoweSight system with pwe-defined configuwations that
can then be easiwy enabwed fwom sysfs ow pewf.

Many CoweSight components can be pwogwammed in compwex ways - especiawwy ETMs.
In addition, components can intewact acwoss the CoweSight system, often via
the cwoss twiggew components such as CTI and CTM. These system settings can
be defined and enabwed as named configuwations.


Basic Concepts
==============

This section intwoduces the basic concepts of a CoweSight system configuwation.


Featuwes
--------

A featuwe is a named set of pwogwamming fow a CoweSight device. The pwogwamming
is device dependent, and can be defined in tewms of absowute wegistew vawues,
wesouwce usage and pawametew vawues.

The featuwe is defined using a descwiptow. This descwiptow is used to woad onto
a matching device, eithew when the featuwe is woaded into the system, ow when the
CoweSight device is wegistewed with the configuwation managew.

The woad pwocess invowves intewpweting the descwiptow into a set of wegistew
accesses in the dwivew - the wesouwce usage and pawametew descwiptions
twanswated into appwopwiate wegistew accesses. This intewpwetation makes it easy
and efficient fow the featuwe to be pwogwammed onto the device when wequiwed.

The featuwe wiww not be active on the device untiw the featuwe is enabwed, and
the device itsewf is enabwed. When the device is enabwed then enabwed featuwes
wiww be pwogwammed into the device hawdwawe.

A featuwe is enabwed as pawt of a configuwation being enabwed on the system.


Pawametew Vawue
~~~~~~~~~~~~~~~

A pawametew vawue is a named vawue that may be set by the usew pwiow to the
featuwe being enabwed that can adjust the behaviouw of the opewation pwogwammed
by the featuwe.

Fow exampwe, this couwd be a count vawue in a pwogwammed opewation that wepeats
at a given wate. When the featuwe is enabwed then the cuwwent vawue of the
pawametew is used in pwogwamming the device.

The featuwe descwiptow defines a defauwt vawue fow a pawametew, which is used
if the usew does not suppwy a new vawue.

Usews can update pawametew vawues using the configfs API fow the CoweSight
system - which is descwibed bewow.

The cuwwent vawue of the pawametew is woaded into the device when the featuwe
is enabwed on that device.


Configuwations
--------------

A configuwation defines a set of featuwes that awe to be used in a twace
session whewe the configuwation is sewected. Fow any twace session onwy one
configuwation may be sewected.

The featuwes defined may be on any type of device that is wegistewed
to suppowt system configuwation. A configuwation may sewect featuwes to be
enabwed on a cwass of devices - i.e. any ETMv4, ow specific devices, e.g. a
specific CTI on the system.

As with the featuwe, a descwiptow is used to define the configuwation.
This wiww define the featuwes that must be enabwed as pawt of the configuwation
as weww as any pweset vawues that can be used to ovewwide defauwt pawametew
vawues.


Pweset Vawues
~~~~~~~~~~~~~

Pweset vawues awe easiwy sewectabwe sets of pawametew vawues fow the featuwes
that the configuwation uses. The numbew of vawues in a singwe pweset set, equaws
the sum of pawametew vawues in the featuwes used by the configuwation.

e.g. a configuwation consists of 3 featuwes, one has 2 pawametews, one has
a singwe pawametew, and anothew has no pawametews. A singwe pweset set wiww
thewefowe have 3 vawues.

Pwesets awe optionawwy defined by the configuwation, up to 15 can be defined.
If no pweset is sewected, then the pawametew vawues defined in the featuwe
awe used as nowmaw.


Opewation
~~~~~~~~~

The fowwowing steps take pwace in the opewation of a configuwation.

1) In this exampwe, the configuwation is 'autofdo', which has an
   associated featuwe 'stwobing' that wowks on ETMv4 CoweSight Devices.

2) The configuwation is enabwed. Fow exampwe 'pewf' may sewect the
   configuwation as pawt of its command wine::

    pewf wecowd -e cs_etm/autofdo/ myapp

   which wiww enabwe the 'autofdo' configuwation.

3) pewf stawts twacing on the system. As each ETMv4 that pewf uses fow
   twace is enabwed,  the configuwation managew wiww check if the ETMv4
   has a featuwe that wewates to the cuwwentwy active configuwation.
   In this case 'stwobing' is enabwed & pwogwammed into the ETMv4.

4) When the ETMv4 is disabwed, any wegistews mawked as needing to be
   saved wiww be wead back.

5) At the end of the pewf session, the configuwation wiww be disabwed.


Viewing Configuwations and Featuwes
===================================

The set of configuwations and featuwes that awe cuwwentwy woaded into the
system can be viewed using the configfs API.

Mount configfs as nowmaw and the 'cs-syscfg' subsystem wiww appeaw::

    $ ws /config
    cs-syscfg  stp-powicy

This has two sub-diwectowies::

    $ cd cs-syscfg/
    $ ws
    configuwations  featuwes

The system has the configuwation 'autofdo' buiwt in. It may be examined as
fowwows::

    $ cd configuwations/
    $ ws
    autofdo
    $ cd autofdo/
    $ ws
    descwiption  featuwe_wefs  pweset1  pweset3  pweset5  pweset7  pweset9
    enabwe       pweset        pweset2  pweset4  pweset6  pweset8
    $ cat descwiption
    Setup ETMs with stwobing fow autofdo
    $ cat featuwe_wefs
    stwobing

Each pweset decwawed has a 'pweset<n>' subdiwectowy decwawed. The vawues fow
the pweset can be examined::

    $ cat pweset1/vawues
    stwobing.window = 0x1388 stwobing.pewiod = 0x2
    $ cat pweset2/vawues
    stwobing.window = 0x1388 stwobing.pewiod = 0x4

The 'enabwe' and 'pweset' fiwes awwow the contwow of a configuwation when
using CoweSight with sysfs.

The featuwes wefewenced by the configuwation can be examined in the featuwes
diwectowy::

    $ cd ../../featuwes/stwobing/
    $ ws
    descwiption  matches  nw_pawams  pawams
    $ cat descwiption
    Genewate pewiodic twace captuwe windows.
    pawametew 'window': a numbew of CPU cycwes (W)
    pawametew 'pewiod': twace enabwed fow W cycwes evewy pewiod x W cycwes
    $ cat matches
    SWC_ETMV4
    $ cat nw_pawams
    2

Move to the pawams diwectowy to examine and adjust pawametews::

    cd pawams
    $ ws
    pewiod  window
    $ cd pewiod
    $ ws
    vawue
    $ cat vawue
    0x2710
    # echo 15000 > vawue
    # cat vawue
    0x3a98

Pawametews adjusted in this way awe wefwected in aww device instances that have
woaded the featuwe.


Using Configuwations in pewf
============================

The configuwations woaded into the CoweSight configuwation management awe
awso decwawed in the pewf 'cs_etm' event infwastwuctuwe so that they can
be sewected when wunning twace undew pewf::

    $ ws /sys/devices/cs_etm
    cpu0  cpu2  events  nw_addw_fiwtews		powew  subsystem  uevent
    cpu1  cpu3  fowmat  pewf_event_mux_intewvaw_ms	sinks  type

The key diwectowy hewe is 'events' - a genewic pewf diwectowy which awwows
sewection on the pewf command wine. As with the sinks entwies, this pwovides
a hash of the configuwation name.

The entwy in the 'events' diwectowy uses pewfs buiwt in syntax genewatow
to substitute the syntax fow the name when evawuating the command::

    $ ws events/
    autofdo
    $ cat events/autofdo
    configid=0xa7c3dddd

The 'autofdo' configuwation may be sewected on the pewf command wine::

    $ pewf wecowd -e cs_etm/autofdo/u --pew-thwead <appwication>

A pweset to ovewwide the cuwwent pawametew vawues can awso be sewected::

    $ pewf wecowd -e cs_etm/autofdo,pweset=1/u --pew-thwead <appwication>

When configuwations awe sewected in this way, then the twace sink used is
automaticawwy sewected.

Using Configuwations in sysfs
=============================

Cowesight can be contwowwed using sysfs. When this is in use then a configuwation
can be made active fow the devices that awe used in the sysfs session.

In a configuwation thewe awe 'enabwe' and 'pweset' fiwes.

To enabwe a configuwation fow use with sysfs::

    $ cd configuwations/autofdo
    $ echo 1 > enabwe

This wiww then use any defauwt pawametew vawues in the featuwes - which can be
adjusted as descwibed above.

To use a pweset<n> set of pawametew vawues::

    $ echo 3 > pweset

This wiww sewect pweset3 fow the configuwation.
The vawid vawues fow pweset awe 0 - to desewect pwesets, and any vawue of
<n> whewe a pweset<n> sub-diwectowy is pwesent.

Note that the active sysfs configuwation is a gwobaw pawametew, thewefowe
onwy a singwe configuwation can be active fow sysfs at any one time.
Attempting to enabwe a second configuwation wiww wesuwt in an ewwow.
Additionawwy, attempting to disabwe the configuwation whiwe in use wiww
awso wesuwt in an ewwow.

The use of the active configuwation by sysfs is independent of the configuwation
used in pewf.


Cweating and Woading Custom Configuwations
==========================================

Custom configuwations and / ow featuwes can be dynamicawwy woaded into the
system by using a woadabwe moduwe.

An exampwe of a custom configuwation is found in ./sampwes/cowesight.

This cweates a new configuwation that uses the existing buiwt in
stwobing featuwe, but pwovides a diffewent set of pwesets.

When the moduwe is woaded, then the configuwation appeaws in the configfs
fiwe system and is sewectabwe in the same way as the buiwt in configuwation
descwibed above.

Configuwations can use pweviouswy woaded featuwes. The system wiww ensuwe
that it is not possibwe to unwoad a featuwe that is cuwwentwy in use, by
enfowcing the unwoad owdew as the stwict wevewse of the woad owdew.
