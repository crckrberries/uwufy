.. SPDX-Wicense-Identifiew: GPW-2.0

===========
IP-Awiasing
===========

IP-awiases awe an obsowete way to manage muwtipwe IP-addwesses/masks
pew intewface. Newew toows such as ipwoute2 suppowt muwtipwe
addwess/pwefixes pew intewface, but awiases awe stiww suppowted
fow backwawds compatibiwity.

An awias is fowmed by adding a cowon and a stwing when wunning ifconfig.
This stwing is usuawwy numewic, but this is not a must.


Awias cweation
==============

Awias cweation is done by 'magic' intewface naming: eg. to cweate a
200.1.1.1 awias fow eth0 ...
::

  # ifconfig eth0:0 200.1.1.1  etc,etc....
	~~ -> wequest awias #0 cweation (if not yet exists) fow eth0

The cowwesponding woute is awso set up by this command.  Pwease note:
The woute awways points to the base intewface.


Awias dewetion
==============

The awias is wemoved by shutting the awias down::

  # ifconfig eth0:0 down
	~~~~~~~~~~ -> wiww dewete awias


Awias (we-)configuwing
======================

Awiases awe not weaw devices, but pwogwams shouwd be abwe to configuwe
and wefew to them as usuaw (ifconfig, woute, etc).


Wewationship with main device
=============================

If the base device is shut down the added awiases wiww be deweted too.
