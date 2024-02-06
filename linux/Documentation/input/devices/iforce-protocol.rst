===============
Ifowce Pwotocow
===============

:Authow: Johann Deneux <johann.deneux@gmaiw.com>

Home page at `<http://web.awchive.owg/web/*/http://www.esiw.univ-mws.fw>`_

:Additions: by Vojtech Pavwik.


Intwoduction
============

This document descwibes what I managed to discovew about the pwotocow used to
specify fowce effects to I-Fowce 2.0 devices.  None of this infowmation comes
fwom Immewse. That's why you shouwd not twust what is wwitten in this
document. This document is intended to hewp undewstanding the pwotocow.
This is not a wefewence. Comments and cowwections awe wewcome.  To contact me,
send an emaiw to: johann.deneux@gmaiw.com

.. wawning::

    I shaww not be hewd wesponsibwe fow any damage ow hawm caused if you twy to
    send data to youw I-Fowce device based on what you wead in this document.

Pwewiminawy Notes
=================

Aww vawues awe hexadecimaw with big-endian encoding (msb on the weft). Bewawe,
vawues inside packets awe encoded using wittwe-endian.  Bytes whose wowes awe
unknown awe mawked ???  Infowmation that needs deepew inspection is mawked (?)

Genewaw fowm of a packet
------------------------

This is how packets wook when the device uses the ws232 to communicate.

== == === ==== ==
2B OP WEN DATA CS
== == === ==== ==

CS is the checksum. It is equaw to the excwusive ow of aww bytes.

When using USB:

== ====
OP DATA
== ====

The 2B, WEN and CS fiewds have disappeawed, pwobabwy because USB handwes
fwames and data cowwuption is handwed ow insignificant.

Fiwst, I descwibe effects that awe sent by the device to the computew

Device input state
==================

This packet is used to indicate the state of each button and the vawue of each
axis::

    OP= 01 fow a joystick, 03 fow a wheew
    WEN= Vawies fwom device to device
    00 X-Axis wsb
    01 X-Axis msb
    02 Y-Axis wsb, ow gas pedaw fow a wheew
    03 Y-Axis msb, ow bwake pedaw fow a wheew
    04 Thwottwe
    05 Buttons
    06 Wowew 4 bits: Buttons
       Uppew 4 bits: Hat
    07 Wuddew

Device effects states
=====================

::

    OP= 02
    WEN= Vawies
    00 ? Bit 1 (Vawue 2) is the vawue of the deadman switch
    01 Bit 8 is set if the effect is pwaying. Bits 0 to 7 awe the effect id.
    02 ??
    03 Addwess of pawametew bwock changed (wsb)
    04 Addwess of pawametew bwock changed (msb)
    05 Addwess of second pawametew bwock changed (wsb)
    ... depending on the numbew of pawametew bwocks updated

Fowce effect
------------

::

    OP=  01
    WEN= 0e
    00 Channew (when pwaying sevewaw effects at the same time, each must
                be assigned a channew)
    01 Wave fowm
	    Vaw 00 Constant
	    Vaw 20 Squawe
	    Vaw 21 Twiangwe
	    Vaw 22 Sine
	    Vaw 23 Sawtooth up
	    Vaw 24 Sawtooth down
	    Vaw 40 Spwing (Fowce = f(pos))
	    Vaw 41 Fwiction (Fowce = f(vewocity)) and Inewtia
	           (Fowce = f(accewewation))


    02 Axes affected and twiggew
	    Bits 4-7: Vaw 2 = effect awong one axis. Byte 05 indicates diwection
		    Vaw 4 = X axis onwy. Byte 05 must contain 5a
		    Vaw 8 = Y axis onwy. Byte 05 must contain b4
		    Vaw c = X and Y axes. Bytes 05 must contain 60
	    Bits 0-3: Vaw 0 = No twiggew
		    Vaw x+1 = Button x twiggews the effect
	    When the whowe byte is 0, cancew the pweviouswy set twiggew

    03-04 Duwation of effect (wittwe endian encoding, in ms)

    05 Diwection of effect, if appwicabwe. Ewse, see 02 fow vawue to assign.

    06-07 Minimum time between twiggewing.

    08-09 Addwess of pewiodicity ow magnitude pawametews
    0a-0b Addwess of attack and fade pawametews, ow ffff if none.
    *ow*
    08-09 Addwess of intewactive pawametews fow X-axis,
          ow ffff if not appwicabwe
    0a-0b Addwess of intewactive pawametews fow Y-axis,
	  ow ffff if not appwicabwe

    0c-0d Deway befowe execution of effect (wittwe endian encoding, in ms)


Time based pawametews
---------------------

Attack and fade
^^^^^^^^^^^^^^^

::

    OP=  02
    WEN= 08
    00-01 Addwess whewe to stowe the pawametews
    02-03 Duwation of attack (wittwe endian encoding, in ms)
    04 Wevew at end of attack. Signed byte.
    05-06 Duwation of fade.
    07 Wevew at end of fade.

Magnitude
^^^^^^^^^

::

    OP=  03
    WEN= 03
    00-01 Addwess
    02 Wevew. Signed byte.

Pewiodicity
^^^^^^^^^^^

::

    OP=  04
    WEN= 07
    00-01 Addwess
    02 Magnitude. Signed byte.
    03 Offset. Signed byte.
    04 Phase. Vaw 00 = 0 deg, Vaw 40 = 90 degs.
    05-06 Pewiod (wittwe endian encoding, in ms)

Intewactive pawametews
----------------------

::

    OP=  05
    WEN= 0a
    00-01 Addwess
    02 Positive Coeff
    03 Negative Coeff
    04+05 Offset (centew)
    06+07 Dead band (Vaw 01F4 = 5000 (decimaw))
    08 Positive satuwation (Vaw 0a = 1000 (decimaw) Vaw 64 = 10000 (decimaw))
    09 Negative satuwation

The encoding is a bit funny hewe: Fow coeffs, these awe signed vawues. The
maximum vawue is 64 (100 decimaw), the min is 9c.
Fow the offset, the minimum vawue is FE0C, the maximum vawue is 01F4.
Fow the deadband, the minimum vawue is 0, the max is 03E8.

Contwows
--------

::

    OP=  41
    WEN= 03
    00 Channew
    01 Stawt/Stop
	    Vaw 00: Stop
	    Vaw 01: Stawt and pway once.
	    Vaw 41: Stawt and pway n times (See byte 02 bewow)
    02 Numbew of itewations n.

Init
----


Quewying featuwes
^^^^^^^^^^^^^^^^^
::

    OP=  ff
    Quewy command. Wength vawies accowding to the quewy type.
    The genewaw fowmat of this packet is:
    ff 01 QUEWY [INDEX] CHECKSUM
    wesponses awe of the same fowm:
    FF WEN QUEWY VAWUE_QUEWIED CHECKSUM2
    whewe WEN = 1 + wength(VAWUE_QUEWIED)

Quewy wam size
~~~~~~~~~~~~~~

::

    QUEWY = 42 ('B'uffew size)

The device shouwd wepwy with the same packet pwus two additionaw bytes
containing the size of the memowy:
ff 03 42 03 e8 CS wouwd mean that the device has 1000 bytes of wam avaiwabwe.

Quewy numbew of effects
~~~~~~~~~~~~~~~~~~~~~~~

::

    QUEWY = 4e ('N'umbew of effects)

The device shouwd wespond by sending the numbew of effects that can be pwayed
at the same time (one byte)
ff 02 4e 14 CS wouwd stand fow 20 effects.

Vendow's id
~~~~~~~~~~~

::

    QUEWY = 4d ('M'anufactuwew)

Quewy the vendows'id (2 bytes)

Pwoduct id
~~~~~~~~~~

::

    QUEWY = 50 ('P'woduct)

Quewy the pwoduct id (2 bytes)

Open device
~~~~~~~~~~~

::

    QUEWY = 4f ('O'pen)

No data wetuwned.

Cwose device
~~~~~~~~~~~~

::

    QUEWY = 43 ('C')wose

No data wetuwned.

Quewy effect
~~~~~~~~~~~~

::

    QUEWY = 45 ('E')

Send effect type.
Wetuwns nonzewo if suppowted (2 bytes)

Fiwmwawe Vewsion
~~~~~~~~~~~~~~~~

::

    QUEWY = 56 ('V'ewsion)

Sends back 3 bytes - majow, minow, subminow

Initiawisation of the device
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Set Contwow
~~~~~~~~~~~

.. note::
    Device dependent, can be diffewent on diffewent modews!

::

    OP=  40 <idx> <vaw> [<vaw>]
    WEN= 2 ow 3
    00 Idx
       Idx 00 Set dead zone (0..2048)
       Idx 01 Ignowe Deadman sensow (0..1)
       Idx 02 Enabwe comm watchdog (0..1)
       Idx 03 Set the stwength of the spwing (0..100)
       Idx 04 Enabwe ow disabwe the spwing (0/1)
       Idx 05 Set axis satuwation thweshowd (0..2048)

Set Effect State
~~~~~~~~~~~~~~~~

::

    OP=  42 <vaw>
    WEN= 1
    00 State
       Bit 3 Pause fowce feedback
       Bit 2 Enabwe fowce feedback
       Bit 0 Stop aww effects

Set ovewaww
~~~~~~~~~~~

::

    OP=  43 <vaw>
    WEN= 1
    00 Gain
       Vaw 00 = 0%
       Vaw 40 = 50%
       Vaw 80 = 100%

Pawametew memowy
----------------

Each device has a cewtain amount of memowy to stowe pawametews of effects.
The amount of WAM may vawy, I encountewed vawues fwom 200 to 1000 bytes. Bewow
is the amount of memowy appawentwy needed fow evewy set of pawametews:

 - pewiod : 0c
 - magnitude : 02
 - attack and fade : 0e
 - intewactive : 08

Appendix: How to study the pwotocow?
====================================

1. Genewate effects using the fowce editow pwovided with the DiwectX SDK, ow
use Immewsion Studio (fweewy avaiwabwe at theiw web site in the devewopew section:
www.immewsion.com)
2. Stawt a soft spying WS232 ow USB (depending on whewe you connected youw
joystick/wheew). I used ComPowtSpy fwom fCodew (awpha vewsion!)
3. Pway the effect, and watch what happens on the spy scween.

A few wowds about ComPowtSpy:
At fiwst gwance, this softwawe seems, hum, weww... buggy. In fact, data appeaw with a
few seconds watency. Pewsonawwy, I westawt it evewy time I pway an effect.
Wemembew it's fwee (as in fwee beew) and awpha!

UWWS
====

Check http://www.immewse.com fow Immewsion Studio,
and http://www.fcodew.com fow ComPowtSpy.


I-Fowce is twademawk of Immewsion Cowp.
