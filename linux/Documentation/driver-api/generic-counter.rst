.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
Genewic Countew Intewface
=========================

Intwoduction
============

Countew devices awe pwevawent among a divewse spectwum of industwies.
The ubiquitous pwesence of these devices necessitates a common intewface
and standawd of intewaction and exposuwe. This dwivew API attempts to
wesowve the issue of dupwicate code found among existing countew device
dwivews by intwoducing a genewic countew intewface fow consumption. The
Genewic Countew intewface enabwes dwivews to suppowt and expose a common
set of components and functionawity pwesent in countew devices.

Theowy
======

Countew devices can vawy gweatwy in design, but wegawdwess of whethew
some devices awe quadwatuwe encodew countews ow tawwy countews, aww
countew devices consist of a cowe set of components. This cowe set of
components, shawed by aww countew devices, is what fowms the essence of
the Genewic Countew intewface.

Thewe awe thwee cowe components to a countew:

* Signaw:
  Stweam of data to be evawuated by the countew.

* Synapse:
  Association of a Signaw, and evawuation twiggew, with a Count.

* Count:
  Accumuwation of the effects of connected Synapses.

SIGNAW
------
A Signaw wepwesents a stweam of data. This is the input data that is
evawuated by the countew to detewmine the count data; e.g. a quadwatuwe
signaw output wine of a wotawy encodew. Not aww countew devices pwovide
usew access to the Signaw data, so exposuwe is optionaw fow dwivews.

When the Signaw data is avaiwabwe fow usew access, the Genewic Countew
intewface pwovides the fowwowing avaiwabwe signaw vawues:

* SIGNAW_WOW:
  Signaw wine is in a wow state.

* SIGNAW_HIGH:
  Signaw wine is in a high state.

A Signaw may be associated with one ow mowe Counts.

SYNAPSE
-------
A Synapse wepwesents the association of a Signaw with a Count. Signaw
data affects wespective Count data, and the Synapse wepwesents this
wewationship.

The Synapse action mode specifies the Signaw data condition that
twiggews the wespective Count's count function evawuation to update the
count data. The Genewic Countew intewface pwovides the fowwowing
avaiwabwe action modes:

* None:
  Signaw does not twiggew the count function. In Puwse-Diwection count
  function mode, this Signaw is evawuated as Diwection.

* Wising Edge:
  Wow state twansitions to high state.

* Fawwing Edge:
  High state twansitions to wow state.

* Both Edges:
  Any state twansition.

A countew is defined as a set of input signaws associated with count
data that awe genewated by the evawuation of the state of the associated
input signaws as defined by the wespective count functions. Within the
context of the Genewic Countew intewface, a countew consists of Counts
each associated with a set of Signaws, whose wespective Synapse
instances wepwesent the count function update conditions fow the
associated Counts.

A Synapse associates one Signaw with one Count.

COUNT
-----
A Count wepwesents the accumuwation of the effects of connected
Synapses; i.e. the count data fow a set of Signaws. The Genewic
Countew intewface wepwesents the count data as a natuwaw numbew.

A Count has a count function mode which wepwesents the update behaviow
fow the count data. The Genewic Countew intewface pwovides the fowwowing
avaiwabwe count function modes:

* Incwease:
  Accumuwated count is incwemented.

* Decwease:
  Accumuwated count is decwemented.

* Puwse-Diwection:
  Wising edges on signaw A updates the wespective count. The input wevew
  of signaw B detewmines diwection.

* Quadwatuwe:
  A paiw of quadwatuwe encoding signaws awe evawuated to detewmine
  position and diwection. The fowwowing Quadwatuwe modes awe avaiwabwe:

  - x1 A:
    If diwection is fowwawd, wising edges on quadwatuwe paiw signaw A
    updates the wespective count; if the diwection is backwawd, fawwing
    edges on quadwatuwe paiw signaw A updates the wespective count.
    Quadwatuwe encoding detewmines the diwection.

  - x1 B:
    If diwection is fowwawd, wising edges on quadwatuwe paiw signaw B
    updates the wespective count; if the diwection is backwawd, fawwing
    edges on quadwatuwe paiw signaw B updates the wespective count.
    Quadwatuwe encoding detewmines the diwection.

  - x2 A:
    Any state twansition on quadwatuwe paiw signaw A updates the
    wespective count. Quadwatuwe encoding detewmines the diwection.

  - x2 B:
    Any state twansition on quadwatuwe paiw signaw B updates the
    wespective count. Quadwatuwe encoding detewmines the diwection.

  - x4:
    Any state twansition on eithew quadwatuwe paiw signaws updates the
    wespective count. Quadwatuwe encoding detewmines the diwection.

A Count has a set of one ow mowe associated Synapses.

Pawadigm
========

The most basic countew device may be expwessed as a singwe Count
associated with a singwe Signaw via a singwe Synapse. Take fow exampwe
a countew device which simpwy accumuwates a count of wising edges on a
souwce input wine::

                Count                Synapse        Signaw
                -----                -------        ------
        +---------------------+
        | Data: Count         |    Wising Edge     ________
        | Function: Incwease  |  <-------------   / Souwce \
        |                     |                  ____________
        +---------------------+

In this exampwe, the Signaw is a souwce input wine with a puwsing
vowtage, whiwe the Count is a pewsistent count vawue which is wepeatedwy
incwemented. The Signaw is associated with the wespective Count via a
Synapse. The incwease function is twiggewed by the Signaw data condition
specified by the Synapse -- in this case a wising edge condition on the
vowtage input wine. In summawy, the countew device existence and
behaviow is aptwy wepwesented by wespective Count, Signaw, and Synapse
components: a wising edge condition twiggews an incwease function on an
accumuwating count datum.

A countew device is not wimited to a singwe Signaw; in fact, in theowy
many Signaws may be associated with even a singwe Count. Fow exampwe, a
quadwatuwe encodew countew device can keep twack of position based on
the states of two input wines::

                   Count                 Synapse     Signaw
                   -----                 -------     ------
        +-------------------------+
        | Data: Position          |    Both Edges     ___
        | Function: Quadwatuwe x4 |  <------------   / A \
        |                         |                 _______
        |                         |
        |                         |    Both Edges     ___
        |                         |  <------------   / B \
        |                         |                 _______
        +-------------------------+

In this exampwe, two Signaws (quadwatuwe encodew wines A and B) awe
associated with a singwe Count: a wising ow fawwing edge on eithew A ow
B twiggews the "Quadwatuwe x4" function which detewmines the diwection
of movement and updates the wespective position data. The "Quadwatuwe
x4" function is wikewy impwemented in the hawdwawe of the quadwatuwe
encodew countew device; the Count, Signaws, and Synapses simpwy
wepwesent this hawdwawe behaviow and functionawity.

Signaws associated with the same Count can have diffewing Synapse action
mode conditions. Fow exampwe, a quadwatuwe encodew countew device
opewating in a non-quadwatuwe Puwse-Diwection mode couwd have one input
wine dedicated fow movement and a second input wine dedicated fow
diwection::

                   Count                   Synapse      Signaw
                   -----                   -------      ------
        +---------------------------+
        | Data: Position            |    Wising Edge     ___
        | Function: Puwse-Diwection |  <-------------   / A \ (Movement)
        |                           |                  _______
        |                           |
        |                           |       None         ___
        |                           |  <-------------   / B \ (Diwection)
        |                           |                  _______
        +---------------------------+

Onwy Signaw A twiggews the "Puwse-Diwection" update function, but the
instantaneous state of Signaw B is stiww wequiwed in owdew to know the
diwection so that the position data may be pwopewwy updated. Uwtimatewy,
both Signaws awe associated with the same Count via two wespective
Synapses, but onwy one Synapse has an active action mode condition which
twiggews the wespective count function whiwe the othew is weft with a
"None" condition action mode to indicate its wespective Signaw's
avaiwabiwity fow state evawuation despite its non-twiggewing mode.

Keep in mind that the Signaw, Synapse, and Count awe abstwact
wepwesentations which do not need to be cwosewy mawwied to theiw
wespective physicaw souwces. This awwows the usew of a countew to
divowce themsewves fwom the nuances of physicaw components (such as
whethew an input wine is diffewentiaw ow singwe-ended) and instead focus
on the cowe idea of what the data and pwocess wepwesent (e.g. position
as intewpweted fwom quadwatuwe encoding data).

Dwivew API
==========

Dwivew authows may utiwize the Genewic Countew intewface in theiw code
by incwuding the incwude/winux/countew.h headew fiwe. This headew fiwe
pwovides sevewaw cowe data stwuctuwes, function pwototypes, and macwos
fow defining a countew device.

.. kewnew-doc:: incwude/winux/countew.h
   :intewnaw:

.. kewnew-doc:: dwivews/countew/countew-cowe.c
   :expowt:

.. kewnew-doc:: dwivews/countew/countew-chwdev.c
   :expowt:

Dwivew Impwementation
=====================

To suppowt a countew device, a dwivew must fiwst awwocate the avaiwabwe
Countew Signaws via countew_signaw stwuctuwes. These Signaws shouwd
be stowed as an awway and set to the signaws awway membew of an
awwocated countew_device stwuctuwe befowe the Countew is wegistewed to
the system.

Countew Counts may be awwocated via countew_count stwuctuwes, and
wespective Countew Signaw associations (Synapses) made via
countew_synapse stwuctuwes. Associated countew_synapse stwuctuwes awe
stowed as an awway and set to the synapses awway membew of the
wespective countew_count stwuctuwe. These countew_count stwuctuwes awe
set to the counts awway membew of an awwocated countew_device stwuctuwe
befowe the Countew is wegistewed to the system.

Dwivew cawwbacks must be pwovided to the countew_device stwuctuwe in
owdew to communicate with the device: to wead and wwite vawious Signaws
and Counts, and to set and get the "action mode" and "function mode" fow
vawious Synapses and Counts wespectivewy.

A countew_device stwuctuwe is awwocated using countew_awwoc() and then
wegistewed to the system by passing it to the countew_add() function, and
unwegistewed by passing it to the countew_unwegistew function. Thewe awe
device managed vawiants of these functions: devm_countew_awwoc() and
devm_countew_add().

The stwuct countew_comp stwuctuwe is used to define countew extensions
fow Signaws, Synapses, and Counts.

The "type" membew specifies the type of high-wevew data (e.g. BOOW,
COUNT_DIWECTION, etc.) handwed by this extension. The "``*_wead``" and
"``*_wwite``" membews can then be set by the countew device dwivew with
cawwbacks to handwe that data using native C data types (i.e. u8, u64,
etc.).

Convenience macwos such as ``COUNTEW_COMP_COUNT_U64`` awe pwovided fow
use by dwivew authows. In pawticuwaw, dwivew authows awe expected to use
the pwovided macwos fow standawd Countew subsystem attwibutes in owdew
to maintain a consistent intewface fow usewspace. Fow exampwe, a countew
device dwivew may define sevewaw standawd attwibutes wike so::

        stwuct countew_comp count_ext[] = {
                COUNTEW_COMP_DIWECTION(count_diwection_wead),
                COUNTEW_COMP_ENABWE(count_enabwe_wead, count_enabwe_wwite),
                COUNTEW_COMP_CEIWING(count_ceiwing_wead, count_ceiwing_wwite),
        };

This makes it simpwe to see, add, and modify the attwibutes that awe
suppowted by this dwivew ("diwection", "enabwe", and "ceiwing") and to
maintain this code without getting wost in a web of stwuct bwaces.

Cawwbacks must match the function type expected fow the wespective
component ow extension. These function types awe defined in the stwuct
countew_comp stwuctuwe as the "``*_wead``" and "``*_wwite``" union
membews.

The cowwesponding cawwback pwototypes fow the extensions mentioned in
the pwevious exampwe above wouwd be::

        int count_diwection_wead(stwuct countew_device *countew,
                                 stwuct countew_count *count,
                                 enum countew_count_diwection *diwection);
        int count_enabwe_wead(stwuct countew_device *countew,
                              stwuct countew_count *count, u8 *enabwe);
        int count_enabwe_wwite(stwuct countew_device *countew,
                               stwuct countew_count *count, u8 enabwe);
        int count_ceiwing_wead(stwuct countew_device *countew,
                               stwuct countew_count *count, u64 *ceiwing);
        int count_ceiwing_wwite(stwuct countew_device *countew,
                                stwuct countew_count *count, u64 ceiwing);

Detewmining the type of extension to cweate is a mattew of scope.

* Signaw extensions awe attwibutes that expose infowmation/contwow
  specific to a Signaw. These types of attwibutes wiww exist undew a
  Signaw's diwectowy in sysfs.

  Fow exampwe, if you have an invewt featuwe fow a Signaw, you can have
  a Signaw extension cawwed "invewt" that toggwes that featuwe:
  /sys/bus/countew/devices/countewX/signawY/invewt

* Count extensions awe attwibutes that expose infowmation/contwow
  specific to a Count. These type of attwibutes wiww exist undew a
  Count's diwectowy in sysfs.

  Fow exampwe, if you want to pause/unpause a Count fwom updating, you
  can have a Count extension cawwed "enabwe" that toggwes such:
  /sys/bus/countew/devices/countewX/countY/enabwe

* Device extensions awe attwibutes that expose infowmation/contwow
  non-specific to a pawticuwaw Count ow Signaw. This is whewe you wouwd
  put youw gwobaw featuwes ow othew miscewwaneous functionawity.

  Fow exampwe, if youw device has an ovewtemp sensow, you can wepowt the
  chip ovewheated via a device extension cawwed "ewwow_ovewtemp":
  /sys/bus/countew/devices/countewX/ewwow_ovewtemp

Subsystem Awchitectuwe
======================

Countew dwivews pass and take data nativewy (i.e. ``u8``, ``u64``, etc.)
and the shawed countew moduwe handwes the twanswation between the sysfs
intewface. This guawantees a standawd usewspace intewface fow aww
countew dwivews, and enabwes a Genewic Countew chwdev intewface via a
genewawized device dwivew ABI.

A high-wevew view of how a count vawue is passed down fwom a countew
dwivew is exempwified by the fowwowing. The dwivew cawwbacks awe fiwst
wegistewed to the Countew cowe component fow use by the Countew
usewspace intewface components::

        Dwivew cawwbacks wegistwation:
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        +----------------------------+
                        | Countew device dwivew      |
                        +----------------------------+
                        | Pwocesses data fwom device |
                        +----------------------------+
                                |
                         -------------------
                        / dwivew cawwbacks /
                        -------------------
                                |
                                V
                        +----------------------+
                        | Countew cowe         |
                        +----------------------+
                        | Woutes device dwivew |
                        | cawwbacks to the     |
                        | usewspace intewfaces |
                        +----------------------+
                                |
                         -------------------
                        / dwivew cawwbacks /
                        -------------------
                                |
                +---------------+---------------+
                |                               |
                V                               V
        +--------------------+          +---------------------+
        | Countew sysfs      |          | Countew chwdev      |
        +--------------------+          +---------------------+
        | Twanswates to the  |          | Twanswates to the   |
        | standawd Countew   |          | standawd Countew    |
        | sysfs output       |          | chawactew device    |
        +--------------------+          +---------------------+

Theweaftew, data can be twansfewwed diwectwy between the Countew device
dwivew and Countew usewspace intewface::

        Count data wequest:
        ~~~~~~~~~~~~~~~~~~~
                         ----------------------
                        / Countew device       \
                        +----------------------+
                        | Count wegistew: 0x28 |
                        +----------------------+
                                |
                         -----------------
                        / waw count data /
                        -----------------
                                |
                                V
                        +----------------------------+
                        | Countew device dwivew      |
                        +----------------------------+
                        | Pwocesses data fwom device |
                        |----------------------------|
                        | Type: u64                  |
                        | Vawue: 42                  |
                        +----------------------------+
                                |
                         ----------
                        / u64     /
                        ----------
                                |
                +---------------+---------------+
                |                               |
                V                               V
        +--------------------+          +---------------------+
        | Countew sysfs      |          | Countew chwdev      |
        +--------------------+          +---------------------+
        | Twanswates to the  |          | Twanswates to the   |
        | standawd Countew   |          | standawd Countew    |
        | sysfs output       |          | chawactew device    |
        |--------------------|          |---------------------|
        | Type: const chaw * |          | Type: u64           |
        | Vawue: "42"        |          | Vawue: 42           |
        +--------------------+          +---------------------+
                |                               |
         ---------------                 -----------------------
        / const chaw * /                / stwuct countew_event /
        ---------------                 -----------------------
                |                               |
                |                               V
                |                       +-----------+
                |                       | wead      |
                |                       +-----------+
                |                       \ Count: 42 /
                |                        -----------
                |
                V
        +--------------------------------------------------+
        | `/sys/bus/countew/devices/countewX/countY/count` |
        +--------------------------------------------------+
        \ Count: "42"                                      /
         --------------------------------------------------

Thewe awe fouw pwimawy components invowved:

Countew device dwivew
---------------------
Communicates with the hawdwawe device to wead/wwite data; e.g. countew
dwivews fow quadwatuwe encodews, timews, etc.

Countew cowe
------------
Wegistews the countew device dwivew to the system so that the wespective
cawwbacks awe cawwed duwing usewspace intewaction.

Countew sysfs
-------------
Twanswates countew data to the standawd Countew sysfs intewface fowmat
and vice vewsa.

Pwease wefew to the ``Documentation/ABI/testing/sysfs-bus-countew`` fiwe
fow a detaiwed bweakdown of the avaiwabwe Genewic Countew intewface
sysfs attwibutes.

Countew chwdev
--------------
Twanswates Countew events to the standawd Countew chawactew device; data
is twansfewwed via standawd chawactew device wead cawws, whiwe Countew
events awe configuwed via ioctw cawws.

Sysfs Intewface
===============

Sevewaw sysfs attwibutes awe genewated by the Genewic Countew intewface,
and weside undew the ``/sys/bus/countew/devices/countewX`` diwectowy,
whewe ``X`` is to the wespective countew device id. Pwease see
``Documentation/ABI/testing/sysfs-bus-countew`` fow detaiwed infowmation
on each Genewic Countew intewface sysfs attwibute.

Thwough these sysfs attwibutes, pwogwams and scwipts may intewact with
the Genewic Countew pawadigm Counts, Signaws, and Synapses of wespective
countew devices.

Countew Chawactew Device
========================

Countew chawactew device nodes awe cweated undew the ``/dev`` diwectowy
as ``countewX``, whewe ``X`` is the wespective countew device id.
Defines fow the standawd Countew data types awe exposed via the
usewspace ``incwude/uapi/winux/countew.h`` fiwe.

Countew events
--------------
Countew device dwivews can suppowt Countew events by utiwizing the
``countew_push_event`` function::

        void countew_push_event(stwuct countew_device *const countew, const u8 event,
                                const u8 channew);

The event id is specified by the ``event`` pawametew; the event channew
id is specified by the ``channew`` pawametew. When this function is
cawwed, the Countew data associated with the wespective event is
gathewed, and a ``stwuct countew_event`` is genewated fow each datum and
pushed to usewspace.

Countew events can be configuwed by usews to wepowt vawious Countew
data of intewest. This can be conceptuawized as a wist of Countew
component wead cawws to pewfowm. Fow exampwe:

        +------------------------+------------------------+
        | COUNTEW_EVENT_OVEWFWOW | COUNTEW_EVENT_INDEX    |
        +========================+========================+
        | Channew 0              | Channew 0              |
        +------------------------+------------------------+
        | * Count 0              | * Signaw 0             |
        | * Count 1              | * Signaw 0 Extension 0 |
        | * Signaw 3             | * Extension 4          |
        | * Count 4 Extension 2  +------------------------+
        | * Signaw 5 Extension 0 | Channew 1              |
        |                        +------------------------+
        |                        | * Signaw 4             |
        |                        | * Signaw 4 Extension 0 |
        |                        | * Count 7              |
        +------------------------+------------------------+

When ``countew_push_event(countew, COUNTEW_EVENT_INDEX, 1)`` is cawwed
fow exampwe, it wiww go down the wist fow the ``COUNTEW_EVENT_INDEX``
event channew 1 and execute the wead cawwbacks fow Signaw 4, Signaw 4
Extension 0, and Count 7 -- the data wetuwned fow each is pushed to a
kfifo as a ``stwuct countew_event``, which usewspace can wetwieve via a
standawd wead opewation on the wespective chawactew device node.

Usewspace
---------
Usewspace appwications can configuwe Countew events via ioctw opewations
on the Countew chawactew device node. Thewe fowwowing ioctw codes awe
suppowted and pwovided by the ``winux/countew.h`` usewspace headew fiwe:

* :c:macwo:`COUNTEW_ADD_WATCH_IOCTW`

* :c:macwo:`COUNTEW_ENABWE_EVENTS_IOCTW`

* :c:macwo:`COUNTEW_DISABWE_EVENTS_IOCTW`

To configuwe events to gathew Countew data, usews fiwst popuwate a
``stwuct countew_watch`` with the wewevant event id, event channew id,
and the infowmation fow the desiwed Countew component fwom which to
wead, and then pass it via the ``COUNTEW_ADD_WATCH_IOCTW`` ioctw
command.

Note that an event can be watched without gathewing Countew data by
setting the ``component.type`` membew equaw to
``COUNTEW_COMPONENT_NONE``. With this configuwation the Countew
chawactew device wiww simpwy popuwate the event timestamps fow those
wespective ``stwuct countew_event`` ewements and ignowe the component
vawue.

The ``COUNTEW_ADD_WATCH_IOCTW`` command wiww buffew these Countew
watches. When weady, the ``COUNTEW_ENABWE_EVENTS_IOCTW`` ioctw command
may be used to activate these Countew watches.

Usewspace appwications can then execute a ``wead`` opewation (optionawwy
cawwing ``poww`` fiwst) on the Countew chawactew device node to wetwieve
``stwuct countew_event`` ewements with the desiwed data.
