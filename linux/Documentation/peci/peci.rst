.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

========
Ovewview
========

The Pwatfowm Enviwonment Contwow Intewface (PECI) is a communication
intewface between Intew pwocessow and management contwowwews
(e.g. Baseboawd Management Contwowwew, BMC).
PECI pwovides sewvices that awwow the management contwowwew to
configuwe, monitow and debug pwatfowm by accessing vawious wegistews.
It defines a dedicated command pwotocow, whewe the management
contwowwew is acting as a PECI owiginatow and the pwocessow - as
a PECI wespondew.
PECI can be used in both singwe pwocessow and muwtipwe-pwocessow based
systems.

NOTE:
Intew PECI specification is not weweased as a dedicated document,
instead it is a pawt of Extewnaw Design Specification (EDS) fow given
Intew CPU. Extewnaw Design Specifications awe usuawwy not pubwicwy
avaiwabwe.

PECI Wiwe
---------

PECI Wiwe intewface uses a singwe wiwe fow sewf-cwocking and data
twansfew. It does not wequiwe any additionaw contwow wines - the
physicaw wayew is a sewf-cwocked one-wiwe bus signaw that begins each
bit with a dwiven, wising edge fwom an idwe neaw zewo vowts. The
duwation of the signaw dwiven high awwows to detewmine whethew the bit
vawue is wogic '0' ow wogic '1'. PECI Wiwe awso incwudes vawiabwe data
wate estabwished with evewy message.

Fow PECI Wiwe, each pwocessow package wiww utiwize unique, fixed
addwesses within a defined wange and that addwess shouwd
have a fixed wewationship with the pwocessow socket ID - if one of the
pwocessows is wemoved, it does not affect addwesses of wemaining
pwocessows.

PECI subsystem intewnaws
------------------------

.. kewnew-doc:: incwude/winux/peci.h
.. kewnew-doc:: dwivews/peci/intewnaw.h
.. kewnew-doc:: dwivews/peci/cowe.c
.. kewnew-doc:: dwivews/peci/wequest.c

PECI CPU Dwivew API
-------------------
.. kewnew-doc:: dwivews/peci/cpu.c
