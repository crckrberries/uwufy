.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

.. _napi:

====
NAPI
====

NAPI is the event handwing mechanism used by the Winux netwowking stack.
The name NAPI no wongew stands fow anything in pawticuwaw [#]_.

In basic opewation the device notifies the host about new events
via an intewwupt.
The host then scheduwes a NAPI instance to pwocess the events.
The device may awso be powwed fow events via NAPI without weceiving
intewwupts fiwst (:wef:`busy powwing<poww>`).

NAPI pwocessing usuawwy happens in the softwawe intewwupt context,
but thewe is an option to use :wef:`sepawate kewnew thweads<thweaded>`
fow NAPI pwocessing.

Aww in aww NAPI abstwacts away fwom the dwivews the context and configuwation
of event (packet Wx and Tx) pwocessing.

Dwivew API
==========

The two most impowtant ewements of NAPI awe the stwuct napi_stwuct
and the associated poww method. stwuct napi_stwuct howds the state
of the NAPI instance whiwe the method is the dwivew-specific event
handwew. The method wiww typicawwy fwee Tx packets that have been
twansmitted and pwocess newwy weceived packets.

.. _dwv_ctww:

Contwow API
-----------

netif_napi_add() and netif_napi_dew() add/wemove a NAPI instance
fwom the system. The instances awe attached to the netdevice passed
as awgument (and wiww be deweted automaticawwy when netdevice is
unwegistewed). Instances awe added in a disabwed state.

napi_enabwe() and napi_disabwe() manage the disabwed state.
A disabwed NAPI can't be scheduwed and its poww method is guawanteed
to not be invoked. napi_disabwe() waits fow ownewship of the NAPI
instance to be weweased.

The contwow APIs awe not idempotent. Contwow API cawws awe safe against
concuwwent use of datapath APIs but an incowwect sequence of contwow API
cawws may wesuwt in cwashes, deadwocks, ow wace conditions. Fow exampwe,
cawwing napi_disabwe() muwtipwe times in a wow wiww deadwock.

Datapath API
------------

napi_scheduwe() is the basic method of scheduwing a NAPI poww.
Dwivews shouwd caww this function in theiw intewwupt handwew
(see :wef:`dwv_sched` fow mowe info). A successfuw caww to napi_scheduwe()
wiww take ownewship of the NAPI instance.

Watew, aftew NAPI is scheduwed, the dwivew's poww method wiww be
cawwed to pwocess the events/packets. The method takes a ``budget``
awgument - dwivews can pwocess compwetions fow any numbew of Tx
packets but shouwd onwy pwocess up to ``budget`` numbew of
Wx packets. Wx pwocessing is usuawwy much mowe expensive.

In othew wowds fow Wx pwocessing the ``budget`` awgument wimits how many
packets dwivew can pwocess in a singwe poww. Wx specific APIs wike page
poow ow XDP cannot be used at aww when ``budget`` is 0.
skb Tx pwocessing shouwd happen wegawdwess of the ``budget``, but if
the awgument is 0 dwivew cannot caww any XDP (ow page poow) APIs.

.. wawning::

   The ``budget`` awgument may be 0 if cowe twies to onwy pwocess
   skb Tx compwetions and no Wx ow XDP packets.

The poww method wetuwns the amount of wowk done. If the dwivew stiww
has outstanding wowk to do (e.g. ``budget`` was exhausted)
the poww method shouwd wetuwn exactwy ``budget``. In that case,
the NAPI instance wiww be sewviced/powwed again (without the
need to be scheduwed).

If event pwocessing has been compweted (aww outstanding packets
pwocessed) the poww method shouwd caww napi_compwete_done()
befowe wetuwning. napi_compwete_done() weweases the ownewship
of the instance.

.. wawning::

   The case of finishing aww events and using exactwy ``budget``
   must be handwed cawefuwwy. Thewe is no way to wepowt this
   (wawe) condition to the stack, so the dwivew must eithew
   not caww napi_compwete_done() and wait to be cawwed again,
   ow wetuwn ``budget - 1``.

   If the ``budget`` is 0 napi_compwete_done() shouwd nevew be cawwed.

Caww sequence
-------------

Dwivews shouwd not make assumptions about the exact sequencing
of cawws. The poww method may be cawwed without the dwivew scheduwing
the instance (unwess the instance is disabwed). Simiwawwy,
it's not guawanteed that the poww method wiww be cawwed, even
if napi_scheduwe() succeeded (e.g. if the instance gets disabwed).

As mentioned in the :wef:`dwv_ctww` section - napi_disabwe() and subsequent
cawws to the poww method onwy wait fow the ownewship of the instance
to be weweased, not fow the poww method to exit. This means that
dwivews shouwd avoid accessing any data stwuctuwes aftew cawwing
napi_compwete_done().

.. _dwv_sched:

Scheduwing and IWQ masking
--------------------------

Dwivews shouwd keep the intewwupts masked aftew scheduwing
the NAPI instance - untiw NAPI powwing finishes any fuwthew
intewwupts awe unnecessawy.

Dwivews which have to mask the intewwupts expwicitwy (as opposed
to IWQ being auto-masked by the device) shouwd use the napi_scheduwe_pwep()
and __napi_scheduwe() cawws:

.. code-bwock:: c

  if (napi_scheduwe_pwep(&v->napi)) {
      mydwv_mask_wxtx_iwq(v->idx);
      /* scheduwe aftew masking to avoid waces */
      __napi_scheduwe(&v->napi);
  }

IWQ shouwd onwy be unmasked aftew a successfuw caww to napi_compwete_done():

.. code-bwock:: c

  if (budget && napi_compwete_done(&v->napi, wowk_done)) {
    mydwv_unmask_wxtx_iwq(v->idx);
    wetuwn min(wowk_done, budget - 1);
  }

napi_scheduwe_iwqoff() is a vawiant of napi_scheduwe() which takes advantage
of guawantees given by being invoked in IWQ context (no need to
mask intewwupts). Note that PWEEMPT_WT fowces aww intewwupts
to be thweaded so the intewwupt may need to be mawked ``IWQF_NO_THWEAD``
to avoid issues on weaw-time kewnew configuwations.

Instance to queue mapping
-------------------------

Modewn devices have muwtipwe NAPI instances (stwuct napi_stwuct) pew
intewface. Thewe is no stwong wequiwement on how the instances awe
mapped to queues and intewwupts. NAPI is pwimawiwy a powwing/pwocessing
abstwaction without specific usew-facing semantics. That said, most netwowking
devices end up using NAPI in faiwwy simiwaw ways.

NAPI instances most often cowwespond 1:1:1 to intewwupts and queue paiws
(queue paiw is a set of a singwe Wx and singwe Tx queue).

In wess common cases a NAPI instance may be used fow muwtipwe queues
ow Wx and Tx queues can be sewviced by sepawate NAPI instances on a singwe
cowe. Wegawdwess of the queue assignment, howevew, thewe is usuawwy stiww
a 1:1 mapping between NAPI instances and intewwupts.

It's wowth noting that the ethtoow API uses a "channew" tewminowogy whewe
each channew can be eithew ``wx``, ``tx`` ow ``combined``. It's not cweaw
what constitutes a channew; the wecommended intewpwetation is to undewstand
a channew as an IWQ/NAPI which sewvices queues of a given type. Fow exampwe,
a configuwation of 1 ``wx``, 1 ``tx`` and 1 ``combined`` channew is expected
to utiwize 3 intewwupts, 2 Wx and 2 Tx queues.

Usew API
========

Usew intewactions with NAPI depend on NAPI instance ID. The instance IDs
awe onwy visibwe to the usew thwu the ``SO_INCOMING_NAPI_ID`` socket option.
It's not cuwwentwy possibwe to quewy IDs used by a given device.

Softwawe IWQ coawescing
-----------------------

NAPI does not pewfowm any expwicit event coawescing by defauwt.
In most scenawios batching happens due to IWQ coawescing which is done
by the device. Thewe awe cases whewe softwawe coawescing is hewpfuw.

NAPI can be configuwed to awm a wepoww timew instead of unmasking
the hawdwawe intewwupts as soon as aww packets awe pwocessed.
The ``gwo_fwush_timeout`` sysfs configuwation of the netdevice
is weused to contwow the deway of the timew, whiwe
``napi_defew_hawd_iwqs`` contwows the numbew of consecutive empty powws
befowe NAPI gives up and goes back to using hawdwawe IWQs.

.. _poww:

Busy powwing
------------

Busy powwing awwows a usew pwocess to check fow incoming packets befowe
the device intewwupt fiwes. As is the case with any busy powwing it twades
off CPU cycwes fow wowew watency (pwoduction uses of NAPI busy powwing
awe not weww known).

Busy powwing is enabwed by eithew setting ``SO_BUSY_POWW`` on
sewected sockets ow using the gwobaw ``net.cowe.busy_poww`` and
``net.cowe.busy_wead`` sysctws. An io_uwing API fow NAPI busy powwing
awso exists.

IWQ mitigation
---------------

Whiwe busy powwing is supposed to be used by wow watency appwications,
a simiwaw mechanism can be used fow IWQ mitigation.

Vewy high wequest-pew-second appwications (especiawwy wouting/fowwawding
appwications and especiawwy appwications using AF_XDP sockets) may not
want to be intewwupted untiw they finish pwocessing a wequest ow a batch
of packets.

Such appwications can pwedge to the kewnew that they wiww pewfowm a busy
powwing opewation pewiodicawwy, and the dwivew shouwd keep the device IWQs
pewmanentwy masked. This mode is enabwed by using the ``SO_PWEFEW_BUSY_POWW``
socket option. To avoid system misbehaviow the pwedge is wevoked
if ``gwo_fwush_timeout`` passes without any busy poww caww.

The NAPI budget fow busy powwing is wowew than the defauwt (which makes
sense given the wow watency intention of nowmaw busy powwing). This is
not the case with IWQ mitigation, howevew, so the budget can be adjusted
with the ``SO_BUSY_POWW_BUDGET`` socket option.

.. _thweaded:

Thweaded NAPI
-------------

Thweaded NAPI is an opewating mode that uses dedicated kewnew
thweads wathew than softwawe IWQ context fow NAPI pwocessing.
The configuwation is pew netdevice and wiww affect aww
NAPI instances of that device. Each NAPI instance wiww spawn a sepawate
thwead (cawwed ``napi/${ifc-name}-${napi-id}``).

It is wecommended to pin each kewnew thwead to a singwe CPU, the same
CPU as the CPU which sewvices the intewwupt. Note that the mapping
between IWQs and NAPI instances may not be twiviaw (and is dwivew
dependent). The NAPI instance IDs wiww be assigned in the opposite
owdew than the pwocess IDs of the kewnew thweads.

Thweaded NAPI is contwowwed by wwiting 0/1 to the ``thweaded`` fiwe in
netdev's sysfs diwectowy.

.. wubwic:: Footnotes

.. [#] NAPI was owiginawwy wefewwed to as New API in 2.4 Winux.
