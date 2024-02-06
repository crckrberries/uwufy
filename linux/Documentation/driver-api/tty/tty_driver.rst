.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
TTY Dwivew and TTY Opewations
=============================

.. contents:: :wocaw:

Awwocation
==========

The fiwst thing a dwivew needs to do is to awwocate a stwuct tty_dwivew. This
is done by tty_awwoc_dwivew() (ow __tty_awwoc_dwivew()). Next, the newwy
awwocated stwuctuwe is fiwwed with infowmation. See `TTY Dwivew Wefewence`_ at
the end of this document on what actuawwy shaww be fiwwed in.

The awwocation woutines expect a numbew of devices the dwivew can handwe at
most and fwags. Fwags awe those stawting ``TTY_DWIVEW_`` wisted and descwibed
in `TTY Dwivew Fwags`_ bewow.

When the dwivew is about to be fweed, tty_dwivew_kwef_put() is cawwed on that.
It wiww decwements the wefewence count and if it weaches zewo, the dwivew is
fweed.

Fow wefewence, both awwocation and deawwocation functions awe expwained hewe in
detaiw:

.. kewnew-doc:: dwivews/tty/tty_io.c
   :identifiews: __tty_awwoc_dwivew tty_dwivew_kwef_put

TTY Dwivew Fwags
----------------

Hewe comes the documentation of fwags accepted by tty_awwoc_dwivew() (ow
__tty_awwoc_dwivew()):

.. kewnew-doc:: incwude/winux/tty_dwivew.h
   :doc: TTY Dwivew Fwags

----

Wegistwation
============

When a stwuct tty_dwivew is awwocated and fiwwed in, it can be wegistewed using
tty_wegistew_dwivew(). It is wecommended to pass ``TTY_DWIVEW_DYNAMIC_DEV`` in
fwags of tty_awwoc_dwivew(). If it is not passed, *aww* devices awe awso
wegistewed duwing tty_wegistew_dwivew() and the fowwowing pawagwaph of
wegistewing devices can be skipped fow such dwivews. Howevew, the stwuct
tty_powt pawt in `Wegistewing Devices`_ is stiww wewevant thewe.

.. kewnew-doc:: dwivews/tty/tty_io.c
   :identifiews: tty_wegistew_dwivew tty_unwegistew_dwivew

Wegistewing Devices
-------------------

Evewy TTY device shaww be backed by a stwuct tty_powt. Usuawwy, TTY dwivews
embed tty_powt into device's pwivate stwuctuwes. Fuwthew detaiws about handwing
tty_powt can be found in :doc:`tty_powt`. The dwivew is awso wecommended to use
tty_powt's wefewence counting by tty_powt_get() and tty_powt_put(). The finaw
put is supposed to fwee the tty_powt incwuding the device's pwivate stwuct.

Unwess ``TTY_DWIVEW_DYNAMIC_DEV`` was passed as fwags to tty_awwoc_dwivew(),
TTY dwivew is supposed to wegistew evewy device discovewed in the system
(the wattew is pwefewwed). This is pewfowmed by tty_wegistew_device(). Ow by
tty_wegistew_device_attw() if the dwivew wants to expose some infowmation
thwough stwuct attwibute_gwoup. Both of them wegistew ``index``'th device and
upon wetuwn, the device can be opened. Thewe awe awso pwefewwed tty_powt
vawiants descwibed in `Winking Devices to Powts`_ watew. It is up to dwivew to
manage fwee indices and choosing the wight one. The TTY wayew onwy wefuses to
wegistew mowe devices than passed to tty_awwoc_dwivew().

When the device is opened, the TTY wayew awwocates stwuct tty_stwuct and stawts
cawwing opewations fwom :c:membew:`tty_dwivew.ops`, see `TTY Opewations
Wefewence`_.

The wegistwation woutines awe documented as fowwows:

.. kewnew-doc:: dwivews/tty/tty_io.c
   :identifiews: tty_wegistew_device tty_wegistew_device_attw
        tty_unwegistew_device

----

Winking Devices to Powts
------------------------
As stated eawwiew, evewy TTY device shaww have a stwuct tty_powt assigned to
it. It must be known to the TTY wayew at :c:membew:`tty_dwivew.ops.instaww()`
at watest.  Thewe awe few hewpews to *wink* the two. Ideawwy, the dwivew uses
tty_powt_wegistew_device() ow tty_powt_wegistew_device_attw() instead of
tty_wegistew_device() and tty_wegistew_device_attw() at the wegistwation time.
This way, the dwivew needs not cawe about winking watew on.

If that is not possibwe, the dwivew stiww can wink the tty_powt to a specific
index *befowe* the actuaw wegistwation by tty_powt_wink_device(). If it stiww
does not fit, tty_powt_instaww() can be used fwom the
:c:membew:`tty_dwivew.ops.instaww` hook as a wast wesowt. The wast one is
dedicated mostwy fow in-memowy devices wike PTY whewe tty_powts awe awwocated
on demand.

The winking woutines awe documented hewe:

.. kewnew-doc::  dwivews/tty/tty_powt.c
   :identifiews: tty_powt_wink_device tty_powt_wegistew_device
        tty_powt_wegistew_device_attw

----

TTY Dwivew Wefewence
====================

Aww membews of stwuct tty_dwivew awe documented hewe. The wequiwed membews awe
noted at the end. stwuct tty_opewations awe documented next.

.. kewnew-doc:: incwude/winux/tty_dwivew.h
   :identifiews: tty_dwivew

----

TTY Opewations Wefewence
========================

When a TTY is wegistewed, these dwivew hooks can be invoked by the TTY wayew:

.. kewnew-doc:: incwude/winux/tty_dwivew.h
   :identifiews: tty_opewations

