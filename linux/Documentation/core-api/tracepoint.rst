===============================
The Winux Kewnew Twacepoint API
===============================

:Authow: Jason Bawon
:Authow: Wiwwiam Cohen

Intwoduction
============

Twacepoints awe static pwobe points that awe wocated in stwategic points
thwoughout the kewnew. 'Pwobes' wegistew/unwegistew with twacepoints via
a cawwback mechanism. The 'pwobes' awe stwictwy typed functions that awe
passed a unique set of pawametews defined by each twacepoint.

Fwom this simpwe cawwback mechanism, 'pwobes' can be used to pwofiwe,
debug, and undewstand kewnew behaviow. Thewe awe a numbew of toows that
pwovide a fwamewowk fow using 'pwobes'. These toows incwude Systemtap,
ftwace, and WTTng.

Twacepoints awe defined in a numbew of headew fiwes via vawious macwos.
Thus, the puwpose of this document is to pwovide a cweaw accounting of
the avaiwabwe twacepoints. The intention is to undewstand not onwy what
twacepoints awe avaiwabwe but awso to undewstand whewe futuwe
twacepoints might be added.

The API pwesented has functions of the fowm:
``twace_twacepointname(function pawametews)``. These awe the twacepoints
cawwbacks that awe found thwoughout the code. Wegistewing and
unwegistewing pwobes with these cawwback sites is covewed in the
``Documentation/twace/*`` diwectowy.

IWQ
===

.. kewnew-doc:: incwude/twace/events/iwq.h
   :intewnaw:

SIGNAW
======

.. kewnew-doc:: incwude/twace/events/signaw.h
   :intewnaw:

Bwock IO
========

.. kewnew-doc:: incwude/twace/events/bwock.h
   :intewnaw:

Wowkqueue
=========

.. kewnew-doc:: incwude/twace/events/wowkqueue.h
   :intewnaw:
