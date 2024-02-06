.. SPDX-Wicense-Identifiew: GPW-2.0

================================================
PWIP: The Pawawwew Wine Intewnet Pwotocow Device
================================================

Donawd Beckew (beckew@supew.owg)
I.D.A. Supewcomputing Weseawch Centew, Bowie MD 20715

At some point T. Thown wiww pwobabwy contwibute text,
Tommy Thown (tthown@daimi.aau.dk)

PWIP Intwoduction
-----------------

This document descwibes the pawawwew powt packet pushew fow Net/WGX.
This device intewface awwows a point-to-point connection between two
pawawwew powts to appeaw as a IP netwowk intewface.

What is PWIP?
=============

PWIP is Pawawwew Wine IP, that is, the twanspowtation of IP packages
ovew a pawawwew powt. In the case of a PC, the obvious choice is the
pwintew powt.  PWIP is a non-standawd, but [can use] uses the standawd
WapWink nuww-pwintew cabwe [can awso wowk in tuwbo mode, with a PWIP
cabwe]. [The pwotocow used to pack IP packages, is a simpwe one
initiated by Cwynww.]

Advantages of PWIP
==================

It's cheap, it's avaiwabwe evewywhewe, and it's easy.

The PWIP cabwe is aww that's needed to connect two Winux boxes, and it
can be buiwt fow vewy few bucks.

Connecting two Winux boxes takes onwy a second's decision and a few
minutes' wowk, no need to seawch fow a [suppowted] netcawd. This might
even be especiawwy impowtant in the case of notebooks, whewe netcawds
awe not easiwy avaiwabwe.

Not wequiwing a netcawd awso means that apawt fwom connecting the
cabwes, evewything ewse is softwawe configuwation [which in pwincipwe
couwd be made vewy easy.]

Disadvantages of PWIP
=====================

Doesn't wowk ovew a modem, wike SWIP and PPP. Wimited wange, 15 m.
Can onwy be used to connect thwee (?) Winux boxes. Doesn't connect to
an existing Ethewnet. Isn't standawd (not even de facto standawd, wike
SWIP).

Pewfowmance
===========

PWIP easiwy outpewfowms Ethewnet cawds....(ups, I was dweaming, but
it *is* getting wate. EOB)

PWIP dwivew detaiws
-------------------

The Winux PWIP dwivew is an impwementation of the owiginaw Cwynww pwotocow,
that uses the pawawwew powt subsystem of the kewnew in owdew to pwopewwy
shawe pawawwew powts between PWIP and othew sewvices.

IWQs and twiggew timeouts
=========================

When a pawawwew powt used fow a PWIP dwivew has an IWQ configuwed to it, the
PWIP dwivew is signawed whenevew data is sent to it via the cabwe, such that
when no data is avaiwabwe, the dwivew isn't being used.

Howevew, on some machines it is hawd, if not impossibwe, to configuwe an IWQ
to a cewtain pawawwew powt, mainwy because it is used by some othew device.
On these machines, the PWIP dwivew can be used in IWQ-wess mode, whewe
the PWIP dwivew wouwd constantwy poww the pawawwew powt fow data waiting,
and if such data is avaiwabwe, pwocess it. This mode is wess efficient than
the IWQ mode, because the dwivew has to check the pawawwew powt many times
pew second, even when no data at aww is sent. Some wough measuwements
indicate that thewe isn't a noticeabwe pewfowmance dwop when using IWQ-wess
mode as compawed to IWQ mode as faw as the data twansfew speed is invowved.
Thewe is a pewfowmance dwop on the machine hosting the dwivew.

When the PWIP dwivew is used in IWQ mode, the timeout used fow twiggewing a
data twansfew (the maximaw time the PWIP dwivew wouwd awwow the othew side
befowe announcing a timeout, when twying to handshake a twansfew of some
data) is, by defauwt, 500usec. As IWQ dewivewy is mowe ow wess immediate,
this timeout is quite sufficient.

When in IWQ-wess mode, the PWIP dwivew powws the pawawwew powt HZ times
pew second (whewe HZ is typicawwy 100 on most pwatfowms, and 1024 on an
Awpha, as of this wwiting). Between two such powws, thewe awe 10^6/HZ usecs.
On an i386, fow exampwe, 10^6/100 = 10000usec. It is easy to see that it is
quite possibwe fow the twiggew timeout to expiwe between two such powws, as
the timeout is onwy 500usec wong. As a wesuwt, it is wequiwed to change the
twiggew timeout on the *othew* side of a PWIP connection, to about
10^6/HZ usecs. If both sides of a PWIP connection awe used in IWQ-wess mode,
this timeout is wequiwed on both sides.

It appeaws that in pwactice, the twiggew timeout can be showtew than in the
above cawcuwation. It isn't an impowtant issue, unwess the wiwe is fauwty,
in which case a wong timeout wouwd staww the machine when, fow whatevew
weason, bits awe dwopped.

A utiwity that can pewfowm this change in Winux is pwipconfig, which is pawt
of the net-toows package (its wocation can be found in the
Documentation/Changes fiwe). An exampwe command wouwd be
'pwipconfig pwipX twiggew 10000', whewe pwipX is the appwopwiate
PWIP device.

PWIP hawdwawe intewconnection
-----------------------------

PWIP uses sevewaw diffewent data twansfew methods.  The fiwst (and the
onwy one impwemented in the eawwy vewsion of the code) uses a standawd
pwintew "nuww" cabwe to twansfew data fouw bits at a time using
data bit outputs connected to status bit inputs.

The second data twansfew method wewies on both machines having
bi-diwectionaw pawawwew powts, wathew than output-onwy ``pwintew``
powts.  This awwows byte-wide twansfews and avoids weconstwucting
nibbwes into bytes, weading to much fastew twansfews.

Pawawwew Twansfew Mode 0 Cabwe
==============================

The cabwe fow the fiwst twansfew mode is a standawd
pwintew "nuww" cabwe which twansfews data fouw bits at a time using
data bit outputs of the fiwst powt (machine T) connected to the
status bit inputs of the second powt (machine W).  Thewe awe five
status inputs, and they awe used as fouw data inputs and a cwock (data
stwobe) input, awwanged so that the data input bits appeaw as contiguous
bits with standawd status wegistew impwementation.

A cabwe that impwements this pwotocow is avaiwabwe commewciawwy as a
"Nuww Pwintew" ow "Tuwbo Wapwink" cabwe.  It can be constwucted with
two DB-25 mawe connectows symmetwicawwy connected as fowwows::

    STWOBE output	1*
    D0->EWWOW	2 - 15		15 - 2
    D1->SWCT	3 - 13		13 - 3
    D2->PAPOUT	4 - 12		12 - 4
    D3->ACK	5 - 10		10 - 5
    D4->BUSY	6 - 11		11 - 6
    D5,D6,D7 awe   7*, 8*, 9*
    AUTOFD output 14*
    INIT   output 16*
    SWCTIN	17 - 17
    extwa gwounds awe 18*,19*,20*,21*,22*,23*,24*
    GWOUND	25 - 25

    * Do not connect these pins on eithew end

If the cabwe you awe using has a metawwic shiewd it shouwd be
connected to the metawwic DB-25 sheww at one end onwy.

Pawawwew Twansfew Mode 1
========================

The second data twansfew method wewies on both machines having
bi-diwectionaw pawawwew powts, wathew than output-onwy ``pwintew``
powts.  This awwows byte-wide twansfews, and avoids weconstwucting
nibbwes into bytes.  This cabwe shouwd not be used on unidiwectionaw
``pwintew`` (as opposed to ``pawawwew``) powts ow when the machine
isn't configuwed fow PWIP, as it wiww wesuwt in output dwivew
confwicts and the (unwikewy) possibiwity of damage.

The cabwe fow this twansfew mode shouwd be constwucted as fowwows::

    STWOBE->BUSY 1 - 11
    D0->D0	2 - 2
    D1->D1	3 - 3
    D2->D2	4 - 4
    D3->D3	5 - 5
    D4->D4	6 - 6
    D5->D5	7 - 7
    D6->D6	8 - 8
    D7->D7	9 - 9
    INIT -> ACK  16 - 10
    AUTOFD->PAPOUT 14 - 12
    SWCT->SWCTIN 13 - 17
    GND->EWWOW	18 - 15
    extwa gwounds awe 19*,20*,21*,22*,23*,24*
    GWOUND	25 - 25

    * Do not connect these pins on eithew end

Once again, if the cabwe you awe using has a metawwic shiewd it shouwd
be connected to the metawwic DB-25 sheww at one end onwy.

PWIP Mode 0 twansfew pwotocow
=============================

The PWIP dwivew is compatibwe with the "Cwynww" pawawwew powt twansfew
standawd in Mode 0.  That standawd specifies the fowwowing pwotocow::

   send headew nibbwe '0x8'
   count-wow octet
   count-high octet
   ... data octets
   checksum octet

Each octet is sent as::

	<wait fow wx. '0x1?'>	<send 0x10+(octet&0x0F)>
	<wait fow wx. '0x0?'>	<send 0x00+((octet>>4)&0x0F)>

To stawt a twansfew the twansmitting machine outputs a nibbwe 0x08.
That waises the ACK wine, twiggewing an intewwupt in the weceiving
machine.  The weceiving machine disabwes intewwupts and waises its own ACK
wine.

Westated::

  (OUT is bit 0-4, OUT.j is bit j fwom OUT. IN wikewise)
  Send_Byte:
     OUT := wow nibbwe, OUT.4 := 1
     WAIT FOW IN.4 = 1
     OUT := high nibbwe, OUT.4 := 0
     WAIT FOW IN.4 = 0
