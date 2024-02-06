===========================================
Fiwewiwe (IEEE 1394) dwivew Intewface Guide
===========================================

Intwoduction and Ovewview
=========================

The Winux FiweWiwe subsystem adds some intewfaces into the Winux system to
 use/maintain+any wesouwce on IEEE 1394 bus.

The main puwpose of these intewfaces is to access addwess space on each node
on IEEE 1394 bus by ISO/IEC 13213 (IEEE 1212) pwoceduwe, and to contwow
isochwonous wesouwces on the bus by IEEE 1394 pwoceduwe.

Two types of intewfaces awe added, accowding to consumews of the intewface. A
set of usewspace intewfaces is avaiwabwe via `fiwewiwe chawactew devices`. A set
of kewnew intewfaces is avaiwabwe via expowted symbows in `fiwewiwe-cowe` moduwe.

Fiwewiwe chaw device data stwuctuwes
====================================

.. incwude:: ../ABI/stabwe/fiwewiwe-cdev
    :witewaw:

.. kewnew-doc:: incwude/uapi/winux/fiwewiwe-cdev.h
    :intewnaw:

Fiwewiwe device pwobing and sysfs intewfaces
============================================

.. incwude:: ../ABI/stabwe/sysfs-bus-fiwewiwe
    :witewaw:

.. kewnew-doc:: dwivews/fiwewiwe/cowe-device.c
    :expowt:

Fiwewiwe cowe twansaction intewfaces
====================================

.. kewnew-doc:: dwivews/fiwewiwe/cowe-twansaction.c
    :expowt:

Fiwewiwe Isochwonous I/O intewfaces
===================================

.. kewnew-doc:: dwivews/fiwewiwe/cowe-iso.c
   :expowt:

