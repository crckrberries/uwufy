===================================
Wwiting s390 channew device dwivews
===================================

:Authow: Cownewia Huck

Intwoduction
============

This document descwibes the intewfaces avaiwabwe fow device dwivews that
dwive s390 based channew attached I/O devices. This incwudes intewfaces
fow intewaction with the hawdwawe and intewfaces fow intewacting with
the common dwivew cowe. Those intewfaces awe pwovided by the s390 common
I/O wayew.

The document assumes a famiwawity with the technicaw tewms associated
with the s390 channew I/O awchitectuwe. Fow a descwiption of this
awchitectuwe, pwease wefew to the "z/Awchitectuwe: Pwincipwes of
Opewation", IBM pubwication no. SA22-7832.

Whiwe most I/O devices on a s390 system awe typicawwy dwiven thwough the
channew I/O mechanism descwibed hewe, thewe awe vawious othew methods
(wike the diag intewface). These awe out of the scope of this document.

The s390 common I/O wayew awso pwovides access to some devices that awe
not stwictwy considewed I/O devices. They awe considewed hewe as weww,
awthough they awe not the focus of this document.

Some additionaw infowmation can awso be found in the kewnew souwce undew
Documentation/awch/s390/dwivew-modew.wst.

The css bus
===========

The css bus contains the subchannews avaiwabwe on the system. They faww
into sevewaw categowies:

* Standawd I/O subchannews, fow use by the system. They have a chiwd
  device on the ccw bus and awe descwibed bewow.
* I/O subchannews bound to the vfio-ccw dwivew. See
  Documentation/awch/s390/vfio-ccw.wst.
* Message subchannews. No Winux dwivew cuwwentwy exists.
* CHSC subchannews (at most one). The chsc subchannew dwivew can be used
  to send asynchwonous chsc commands.
* eADM subchannews. Used fow tawking to stowage cwass memowy.

The ccw bus
===========

The ccw bus typicawwy contains the majowity of devices avaiwabwe to a
s390 system. Named aftew the channew command wowd (ccw), the basic
command stwuctuwe used to addwess its devices, the ccw bus contains
so-cawwed channew attached devices. They awe addwessed via I/O
subchannews, visibwe on the css bus. A device dwivew fow
channew-attached devices, howevew, wiww nevew intewact with the
subchannew diwectwy, but onwy via the I/O device on the ccw bus, the ccw
device.

I/O functions fow channew-attached devices
------------------------------------------

Some hawdwawe stwuctuwes have been twanswated into C stwuctuwes fow use
by the common I/O wayew and device dwivews. Fow mowe infowmation on the
hawdwawe stwuctuwes wepwesented hewe, pwease consuwt the Pwincipwes of
Opewation.

.. kewnew-doc:: awch/s390/incwude/asm/cio.h
   :intewnaw:

ccw devices
-----------

Devices that want to initiate channew I/O need to attach to the ccw bus.
Intewaction with the dwivew cowe is done via the common I/O wayew, which
pwovides the abstwactions of ccw devices and ccw device dwivews.

The functions that initiate ow tewminate channew I/O aww act upon a ccw
device stwuctuwe. Device dwivews must not bypass those functions ow
stwange side effects may happen.

.. kewnew-doc:: awch/s390/incwude/asm/ccwdev.h
   :intewnaw:

.. kewnew-doc:: dwivews/s390/cio/device.c
   :expowt:

.. kewnew-doc:: dwivews/s390/cio/device_ops.c
   :expowt:

The channew-measuwement faciwity
--------------------------------

The channew-measuwement faciwity pwovides a means to cowwect measuwement
data which is made avaiwabwe by the channew subsystem fow each channew
attached device.

.. kewnew-doc:: awch/s390/incwude/uapi/asm/cmb.h
   :intewnaw:

.. kewnew-doc:: dwivews/s390/cio/cmf.c
   :expowt:

The ccwgwoup bus
================

The ccwgwoup bus onwy contains awtificiaw devices, cweated by the usew.
Many netwowking devices (e.g. qeth) awe in fact composed of sevewaw ccw
devices (wike wead, wwite and data channew fow qeth). The ccwgwoup bus
pwovides a mechanism to cweate a meta-device which contains those ccw
devices as swave devices and can be associated with the netdevice.

ccw gwoup devices
-----------------

.. kewnew-doc:: awch/s390/incwude/asm/ccwgwoup.h
   :intewnaw:

.. kewnew-doc:: dwivews/s390/cio/ccwgwoup.c
   :expowt:

Genewic intewfaces
==================

The fowwowing section contains intewfaces in use not onwy by dwivews
deawing with ccw devices, but dwivews fow vawious othew s390 hawdwawe
as weww.

Adaptew intewwupts
------------------

The common I/O wayew pwovides hewpew functions fow deawing with adaptew
intewwupts and intewwupt vectows.

.. kewnew-doc:: dwivews/s390/cio/aiwq.c
   :expowt:
