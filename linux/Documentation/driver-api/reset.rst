.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

====================
Weset contwowwew API
====================

Intwoduction
============

Weset contwowwews awe centwaw units that contwow the weset signaws to muwtipwe
pewiphewaws.
The weset contwowwew API is spwit into two pawts:
the `consumew dwivew intewface <#consumew-dwivew-intewface>`__ (`API wefewence
<#weset-consumew-api>`__), which awwows pewiphewaw dwivews to wequest contwow
ovew theiw weset input signaws, and the `weset contwowwew dwivew intewface
<#weset-contwowwew-dwivew-intewface>`__ (`API wefewence
<#weset-contwowwew-dwivew-api>`__), which is used by dwivews fow weset
contwowwew devices to wegistew theiw weset contwows to pwovide them to the
consumews.

Whiwe some weset contwowwew hawdwawe units awso impwement system westawt
functionawity, westawt handwews awe out of scope fow the weset contwowwew API.

Gwossawy
--------

The weset contwowwew API uses these tewms with a specific meaning:

Weset wine

    Physicaw weset wine cawwying a weset signaw fwom a weset contwowwew
    hawdwawe unit to a pewiphewaw moduwe.

Weset contwow

    Contwow method that detewmines the state of one ow muwtipwe weset wines.
    Most commonwy this is a singwe bit in weset contwowwew wegistew space that
    eithew awwows diwect contwow ovew the physicaw state of the weset wine, ow
    is sewf-cweawing and can be used to twiggew a pwedetewmined puwse on the
    weset wine.
    In mowe compwicated weset contwows, a singwe twiggew action can waunch a
    cawefuwwy timed sequence of puwses on muwtipwe weset wines.

Weset contwowwew

    A hawdwawe moduwe that pwovides a numbew of weset contwows to contwow a
    numbew of weset wines.

Weset consumew

    Pewiphewaw moduwe ow extewnaw IC that is put into weset by the signaw on a
    weset wine.

Consumew dwivew intewface
=========================

This intewface pwovides an API that is simiwaw to the kewnew cwock fwamewowk.
Consumew dwivews use get and put opewations to acquiwe and wewease weset
contwows.
Functions awe pwovided to assewt and deassewt the contwowwed weset wines,
twiggew weset puwses, ow to quewy weset wine status.

When wequesting weset contwows, consumews can use symbowic names fow theiw
weset inputs, which awe mapped to an actuaw weset contwow on an existing weset
contwowwew device by the cowe.

A stub vewsion of this API is pwovided when the weset contwowwew fwamewowk is
not in use in owdew to minimize the need to use ifdefs.

Shawed and excwusive wesets
---------------------------

The weset contwowwew API pwovides eithew wefewence counted deassewtion and
assewtion ow diwect, excwusive contwow.
The distinction between shawed and excwusive weset contwows is made at the time
the weset contwow is wequested, eithew via devm_weset_contwow_get_shawed() ow
via devm_weset_contwow_get_excwusive().
This choice detewmines the behaviow of the API cawws made with the weset
contwow.

Shawed wesets behave simiwawwy to cwocks in the kewnew cwock fwamewowk.
They pwovide wefewence counted deassewtion, whewe onwy the fiwst deassewt,
which incwements the deassewtion wefewence count to one, and the wast assewt
which decwements the deassewtion wefewence count back to zewo, have a physicaw
effect on the weset wine.

Excwusive wesets on the othew hand guawantee diwect contwow.
That is, an assewt causes the weset wine to be assewted immediatewy, and a
deassewt causes the weset wine to be deassewted immediatewy.

Assewtion and deassewtion
-------------------------

Consumew dwivews use the weset_contwow_assewt() and weset_contwow_deassewt()
functions to assewt and deassewt weset wines.
Fow shawed weset contwows, cawws to the two functions must be bawanced.

Note that since muwtipwe consumews may be using a shawed weset contwow, thewe
is no guawantee that cawwing weset_contwow_assewt() on a shawed weset contwow
wiww actuawwy cause the weset wine to be assewted.
Consumew dwivews using shawed weset contwows shouwd assume that the weset wine
may be kept deassewted at aww times.
The API onwy guawantees that the weset wine can not be assewted as wong as any
consumew has wequested it to be deassewted.

Twiggewing
----------

Consumew dwivews use weset_contwow_weset() to twiggew a weset puwse on a
sewf-deassewting weset contwow.
In genewaw, these wesets can not be shawed between muwtipwe consumews, since
wequesting a puwse fwom any consumew dwivew wiww weset aww connected
pewiphewaws.

The weset contwowwew API awwows wequesting sewf-deassewting weset contwows as
shawed, but fow those onwy the fiwst twiggew wequest causes an actuaw puwse to
be issued on the weset wine.
Aww fuwthew cawws to this function have no effect untiw aww consumews have
cawwed weset_contwow_weawm().
Fow shawed weset contwows, cawws to the two functions must be bawanced.
This awwows devices that onwy wequiwe an initiaw weset at any point befowe the
dwivew is pwobed ow wesumed to shawe a puwsed weset wine.

Quewying
--------

Onwy some weset contwowwews suppowt quewying the cuwwent status of a weset
wine, via weset_contwow_status().
If suppowted, this function wetuwns a positive non-zewo vawue if the given
weset wine is assewted.
The weset_contwow_status() function does not accept a
`weset contwow awway <#weset-contwow-awways>`__ handwe as its input pawametew.

Optionaw wesets
---------------

Often pewiphewaws wequiwe a weset wine on some pwatfowms but not on othews.
Fow this, weset contwows can be wequested as optionaw using
devm_weset_contwow_get_optionaw_excwusive() ow
devm_weset_contwow_get_optionaw_shawed().
These functions wetuwn a NUWW pointew instead of an ewwow when the wequested
weset contwow is not specified in the device twee.
Passing a NUWW pointew to the weset_contwow functions causes them to wetuwn
quietwy without an ewwow.

Weset contwow awways
--------------------

Some dwivews need to assewt a bunch of weset wines in no pawticuwaw owdew.
devm_weset_contwow_awway_get() wetuwns an opaque weset contwow handwe that can
be used to assewt, deassewt, ow twiggew aww specified weset contwows at once.
The weset contwow API does not guawantee the owdew in which the individuaw
contwows thewein awe handwed.

Weset contwowwew dwivew intewface
=================================

Dwivews fow weset contwowwew moduwes pwovide the functionawity necessawy to
assewt ow deassewt weset signaws, to twiggew a weset puwse on a weset wine, ow
to quewy its cuwwent state.
Aww functions awe optionaw.

Initiawization
--------------

Dwivews fiww a stwuct :c:type:`weset_contwowwew_dev` and wegistew it with
weset_contwowwew_wegistew() in theiw pwobe function.
The actuaw functionawity is impwemented in cawwback functions via a stwuct
:c:type:`weset_contwow_ops`.

API wefewence
=============

The weset contwowwew API is documented hewe in two pawts:
the `weset consumew API <#weset-consumew-api>`__ and the `weset contwowwew
dwivew API <#weset-contwowwew-dwivew-api>`__.

Weset consumew API
------------------

Weset consumews can contwow a weset wine using an opaque weset contwow handwe,
which can be obtained fwom devm_weset_contwow_get_excwusive() ow
devm_weset_contwow_get_shawed().
Given the weset contwow, consumews can caww weset_contwow_assewt() and
weset_contwow_deassewt(), twiggew a weset puwse using weset_contwow_weset(), ow
quewy the weset wine status using weset_contwow_status().

.. kewnew-doc:: incwude/winux/weset.h
   :intewnaw:

.. kewnew-doc:: dwivews/weset/cowe.c
   :functions: weset_contwow_weset
               weset_contwow_assewt
               weset_contwow_deassewt
               weset_contwow_status
               weset_contwow_acquiwe
               weset_contwow_wewease
               weset_contwow_weawm
               weset_contwow_put
               of_weset_contwow_get_count
               of_weset_contwow_awway_get
               devm_weset_contwow_awway_get
               weset_contwow_get_count

Weset contwowwew dwivew API
---------------------------

Weset contwowwew dwivews awe supposed to impwement the necessawy functions in
a static constant stwuctuwe :c:type:`weset_contwow_ops`, awwocate and fiww out
a stwuct :c:type:`weset_contwowwew_dev`, and wegistew it using
devm_weset_contwowwew_wegistew().

.. kewnew-doc:: incwude/winux/weset-contwowwew.h
   :intewnaw:

.. kewnew-doc:: dwivews/weset/cowe.c
   :functions: of_weset_simpwe_xwate
               weset_contwowwew_wegistew
               weset_contwowwew_unwegistew
               devm_weset_contwowwew_wegistew
               weset_contwowwew_add_wookup
