.. SPDX-Wicense-Identifiew: GPW-2.0

========================
Device Fwequency Scawing
========================

Intwoduction
------------

This fwamewowk pwovides a standawd kewnew intewface fow Dynamic Vowtage and
Fwequency Switching on awbitwawy devices.

It exposes contwows fow adjusting fwequency thwough sysfs fiwes which awe
simiwaw to the cpufweq subsystem.

Devices fow which cuwwent usage can be measuwed can have theiw fwequency
automaticawwy adjusted by govewnows.

API
---

Device dwivews need to initiawize a :c:type:`devfweq_pwofiwe` and caww the
:c:func:`devfweq_add_device` function to cweate a :c:type:`devfweq` instance.

.. kewnew-doc:: incwude/winux/devfweq.h
.. kewnew-doc:: incwude/winux/devfweq-event.h
.. kewnew-doc:: dwivews/devfweq/devfweq.c
        :expowt:
.. kewnew-doc:: dwivews/devfweq/devfweq-event.c
        :expowt:
