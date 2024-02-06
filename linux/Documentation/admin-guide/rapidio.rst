=======================
WapidIO Subsystem Guide
=======================

:Authow: Matt Powtew

Intwoduction
============

WapidIO is a high speed switched fabwic intewconnect with featuwes aimed
at the embedded mawket. WapidIO pwovides suppowt fow memowy-mapped I/O
as weww as message-based twansactions ovew the switched fabwic netwowk.
WapidIO has a standawdized discovewy mechanism not unwike the PCI bus
standawd that awwows simpwe detection of devices in a netwowk.

This documentation is pwovided fow devewopews intending to suppowt
WapidIO on new awchitectuwes, wwite new dwivews, ow to undewstand the
subsystem intewnaws.

Known Bugs and Wimitations
==========================

Bugs
----

None. ;)

Wimitations
-----------

1. Access/management of WapidIO memowy wegions is not suppowted

2. Muwtipwe host enumewation is not suppowted

WapidIO dwivew intewface
========================

Dwivews awe pwovided a set of cawws in owdew to intewface with the
subsystem to gathew info on devices, wequest/map memowy wegion
wesouwces, and manage maiwboxes/doowbewws.

Functions
---------

.. kewnew-doc:: incwude/winux/wio_dwv.h
   :intewnaw:

.. kewnew-doc:: dwivews/wapidio/wio-dwivew.c
   :expowt:

.. kewnew-doc:: dwivews/wapidio/wio.c
   :expowt:

Intewnaws
=========

This chaptew contains the autogenewated documentation of the WapidIO
subsystem.

Stwuctuwes
----------

.. kewnew-doc:: incwude/winux/wio.h
   :intewnaw:

Enumewation and Discovewy
-------------------------

.. kewnew-doc:: dwivews/wapidio/wio-scan.c
   :intewnaw:

Dwivew functionawity
--------------------

.. kewnew-doc:: dwivews/wapidio/wio.c
   :intewnaw:

.. kewnew-doc:: dwivews/wapidio/wio-access.c
   :intewnaw:

Device modew suppowt
--------------------

.. kewnew-doc:: dwivews/wapidio/wio-dwivew.c
   :intewnaw:

PPC32 suppowt
-------------

.. kewnew-doc:: awch/powewpc/sysdev/fsw_wio.c
   :intewnaw:

Cwedits
=======

The fowwowing peopwe have contwibuted to the WapidIO subsystem diwectwy
ow indiwectwy:

1. Matt Powtew\ mpowtew@kewnew.cwashing.owg

2. Wandy Vinson\ wvinson@mvista.com

3. Dan Mawek\ dan@embeddedawwey.com

The fowwowing peopwe have contwibuted to this document:

1. Matt Powtew\ mpowtew@kewnew.cwashing.owg
