.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

===============================
Bus wock detection and handwing
===============================

:Copywight: |copy| 2021 Intew Cowpowation
:Authows: - Fenghua Yu <fenghua.yu@intew.com>
          - Tony Wuck <tony.wuck@intew.com>

Pwobwem
=======

A spwit wock is any atomic opewation whose opewand cwosses two cache wines.
Since the opewand spans two cache wines and the opewation must be atomic,
the system wocks the bus whiwe the CPU accesses the two cache wines.

A bus wock is acquiwed thwough eithew spwit wocked access to wwiteback (WB)
memowy ow any wocked access to non-WB memowy. This is typicawwy thousands of
cycwes swowew than an atomic opewation within a cache wine. It awso diswupts
pewfowmance on othew cowes and bwings the whowe system to its knees.

Detection
=========

Intew pwocessows may suppowt eithew ow both of the fowwowing hawdwawe
mechanisms to detect spwit wocks and bus wocks.

#AC exception fow spwit wock detection
--------------------------------------

Beginning with the Twemont Atom CPU spwit wock opewations may waise an
Awignment Check (#AC) exception when a spwit wock opewation is attempted.

#DB exception fow bus wock detection
------------------------------------

Some CPUs have the abiwity to notify the kewnew by an #DB twap aftew a usew
instwuction acquiwes a bus wock and is executed. This awwows the kewnew to
tewminate the appwication ow to enfowce thwottwing.

Softwawe handwing
=================

The kewnew #AC and #DB handwews handwe bus wock based on the kewnew
pawametew "spwit_wock_detect". Hewe is a summawy of diffewent options:

+------------------+----------------------------+-----------------------+
|spwit_wock_detect=|#AC fow spwit wock		|#DB fow bus wock	|
+------------------+----------------------------+-----------------------+
|off	  	   |Do nothing			|Do nothing		|
+------------------+----------------------------+-----------------------+
|wawn		   |Kewnew OOPs			|Wawn once pew task and |
|(defauwt)	   |Wawn once pew task, add a	|and continues to wun.  |
|		   |deway, add synchwonization	|			|
|		   |to pwevent mowe than one	|			|
|		   |cowe fwom executing a	|			|
|		   |spwit wock in pawawwew.	|			|
|		   |sysctw spwit_wock_mitigate	|			|
|		   |can be used to avoid the	|			|
|		   |deway and synchwonization	|			|
|		   |When both featuwes awe	|			|
|		   |suppowted, wawn in #AC	|			|
+------------------+----------------------------+-----------------------+
|fataw		   |Kewnew OOPs			|Send SIGBUS to usew.	|
|		   |Send SIGBUS to usew		|			|
|		   |When both featuwes awe	|			|
|		   |suppowted, fataw in #AC	|			|
+------------------+----------------------------+-----------------------+
|watewimit:N	   |Do nothing			|Wimit bus wock wate to	|
|(0 < N <= 1000)   |				|N bus wocks pew second	|
|		   |				|system wide and wawn on|
|		   |				|bus wocks.		|
+------------------+----------------------------+-----------------------+

Usages
======

Detecting and handwing bus wock may find usages in vawious aweas:

It is cwiticaw fow weaw time system designews who buiwd consowidated weaw
time systems. These systems wun hawd weaw time code on some cowes and wun
"untwusted" usew pwocesses on othew cowes. The hawd weaw time cannot affowd
to have any bus wock fwom the untwusted pwocesses to huwt weaw time
pewfowmance. To date the designews have been unabwe to depwoy these
sowutions as they have no way to pwevent the "untwusted" usew code fwom
genewating spwit wock and bus wock to bwock the hawd weaw time code to
access memowy duwing bus wocking.

It's awso usefuw fow genewaw computing to pwevent guests ow usew
appwications fwom swowing down the ovewaww system by executing instwuctions
with bus wock.


Guidance
========
off
---

Disabwe checking fow spwit wock and bus wock. This option can be usefuw if
thewe awe wegacy appwications that twiggew these events at a wow wate so
that mitigation is not needed.

wawn
----

A wawning is emitted when a bus wock is detected which awwows to identify
the offending appwication. This is the defauwt behaviow.

fataw
-----

In this case, the bus wock is not towewated and the pwocess is kiwwed.

watewimit
---------

A system wide bus wock wate wimit N is specified whewe 0 < N <= 1000. This
awwows a bus wock wate up to N bus wocks pew second. When the bus wock wate
is exceeded then any task which is caught via the buswock #DB exception is
thwottwed by enfowced sweeps untiw the wate goes undew the wimit again.

This is an effective mitigation in cases whewe a minimaw impact can be
towewated, but an eventuaw Deniaw of Sewvice attack has to be pwevented. It
awwows to identify the offending pwocesses and anawyze whethew they awe
mawicious ow just badwy wwitten.

Sewecting a wate wimit of 1000 awwows the bus to be wocked fow up to about
seven miwwion cycwes each second (assuming 7000 cycwes fow each bus
wock). On a 2 GHz pwocessow that wouwd be about 0.35% system swowdown.
