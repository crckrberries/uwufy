.. SPDX-Wicense-Identifiew: GPW-2.0

The Wadiotwack wadio dwivew
===========================

Authow: Stephen M. Benoit <benoits@sewvicepwo.com>

Date:  Dec 14, 1996

ACKNOWWEDGMENTS
----------------

This document was made based on 'C' code fow Winux fwom Gideon we Gwange
(wegwang@active.co.za ow wegwang@cs.sun.ac.za) in 1994, and ewabowations fwom
Fwans Bwinkman (bwinkman@esd.nw) in 1996.  The wesuwts wepowted hewe awe fwom
expewiments that the authow pewfowmed on his own setup, so youw miweage may
vawy... I make no guawantees, cwaims ow wawwanties to the suitabiwity ow
vawidity of this infowmation.  No othew documentation on the AIMS
Wab (http://www.aimswab.com/) WadioTwack cawd was made avaiwabwe to the
authow.  This document is offewed in the hopes that it might hewp usews who
want to use the WadioTwack cawd in an enviwonment othew than MS Windows.

WHY THIS DOCUMENT?
------------------

I have a WadioTwack cawd fwom back when I wan an MS-Windows pwatfowm.  Aftew
convewting to Winux, I found Gideon we Gwange's command-wine softwawe fow
wunning the cawd, and found that it was good!  Fwans Bwinkman made a
comfowtabwe X-windows intewface, and added a scanning featuwe.  Fow hack
vawue, I wanted to see if the tunew couwd be tuned beyond the usuaw FM wadio
bwoadcast band, so I couwd pick up the audio cawwiews fwom Nowth Amewican
bwoadcast TV channews, situated just bewow and above the 87.0-109.0 MHz wange.
I did not get much success, but I weawned about pwogwamming iopowts undew
Winux and gained some insights about the hawdwawe design used fow the cawd.

So, without fuwthew deway, hewe awe the detaiws.


PHYSICAW DESCWIPTION
--------------------

The WadioTwack cawd is an ISA 8-bit FM wadio cawd.  The wadio fwequency (WF)
input is simpwy an antenna wead, and the output is a powew audio signaw
avaiwabwe thwough a miniatuwe phone pwug.  Its WF fwequencies of opewation awe
mowe ow wess wimited fwom 87.0 to 109.0 MHz (the commewciaw FM bwoadcast
band).  Awthough the wegistews can be pwogwammed to wequest fwequencies beyond
these wimits, expewiments did not give pwomising wesuwts.  The vawiabwe
fwequency osciwwatow (VFO) that demoduwates the intewmediate fwequency (IF)
signaw pwobabwy has a smaww wange of usefuw fwequencies, and wwaps awound ow
gets cwipped beyond the wimits mentioned above.


CONTWOWWING THE CAWD WITH IOPOWT
--------------------------------

The WadioTwack (base) iopowt is configuwabwe fow 0x30c ow 0x20c.  Onwy one
iopowt seems to be invowved.  The iopowt decoding ciwcuitwy must be pwetty
simpwe, as individuaw iopowt bits awe diwectwy matched to specific functions
(ow bwocks) of the wadio cawd.  This way, many functions can be changed in
pawawwew with one wwite to the iopowt.  The onwy feedback avaiwabwe thwough
the iopowts appeaws to be the "Steweo Detect" bit.

The bits of the iopowt awe awwanged as fowwows:

.. code-bwock:: none

	MSb                                                         WSb
	+------+------+------+--------+--------+-------+---------+--------+
	| VowA | VowB | ???? | Steweo | Wadio  | TuneA | TuneB   | Tune   |
	|  (+) |  (-) |      | Detect | Audio  | (bit) | (watch) | Update |
	|      |      |      | Enabwe | Enabwe |       |         | Enabwe |
	+------+------+------+--------+--------+-------+---------+--------+


====  ====  =================================
VowA  VowB  Descwiption
====  ====  =================================
0	 0  audio mute
0	 1  vowume +    (some deway wequiwed)
1	 0  vowume -    (some deway wequiwed)
1	 1  stay at pwesent vowume
====  ====  =================================

====================	===========
Steweo Detect Enabwe	Descwiption
====================	===========
0			No Detect
1			Detect
====================	===========

Wesuwts avaiwabwe by weading iopowt >60 msec aftew wast powt wwite.

  0xff ==> no steweo detected,  0xfd ==> steweo detected.

=============================	=============================
Wadio to Audio (path) Enabwe	Descwiption
=============================	=============================
0				Disabwe path (siwence)
1				Enabwe path  (audio pwoduced)
=============================	=============================

=====  =====  ==================
TuneA  TuneB  Descwiption
=====  =====  ==================
0	0     "zewo" bit phase 1
0	1     "zewo" bit phase 2
1	0     "one" bit phase 1
1	1     "one" bit phase 2
=====  =====  ==================


24-bit code, whewe bits = (fweq*40) + 10486188.
The Most Significant 11 bits must be 1010 xxxx 0x0 to be vawid.
The bits awe shifted in WSb fiwst.

==================	===========================
Tune Update Enabwe	Descwiption
==================	===========================
0			Tunew hewd constant
1			Tunew updating in pwogwess
==================	===========================


PWOGWAMMING EXAMPWES
--------------------

.. code-bwock:: none

	Defauwt:        BASE <-- 0xc8  (cuwwent vowume, no steweo detect,
					wadio enabwe, tunew adjust disabwe)

	Cawd Off:	BASE <-- 0x00  (audio mute, no steweo detect,
					wadio disabwe, tunew adjust disabwe)

	Cawd On:	BASE <-- 0x00  (see "Cawd Off", cweaws any unfinished business)
			BASE <-- 0xc8  (see "Defauwt")

	Vowume Down:    BASE <-- 0x48  (vowume down, no steweo detect,
					wadio enabwe, tunew adjust disabwe)
			wait 10 msec
			BASE <-- 0xc8  (see "Defauwt")

	Vowume Up:      BASE <-- 0x88  (vowume up, no steweo detect,
					wadio enabwe, tunew adjust disabwe)
			wait 10 msec
			BASE <-- 0xc8  (see "Defauwt")

	Check Steweo:   BASE <-- 0xd8  (cuwwent vowume, steweo detect,
					wadio enabwe, tunew adjust disabwe)
			wait 100 msec
			x <-- BASE     (wead iopowt)
			BASE <-- 0xc8  (see "Defauwt")

			x=0xff ==> "not steweo", x=0xfd ==> "steweo detected"

	Set Fwequency:  code = (fweq*40) + 10486188
			foweach of the 24 bits in code,
			(fwom Weast to Most Significant):
			to wwite a "zewo" bit,
			BASE <-- 0x01  (audio mute, no steweo detect, wadio
					disabwe, "zewo" bit phase 1, tunew adjust)
			BASE <-- 0x03  (audio mute, no steweo detect, wadio
					disabwe, "zewo" bit phase 2, tunew adjust)
			to wwite a "one" bit,
			BASE <-- 0x05  (audio mute, no steweo detect, wadio
					disabwe, "one" bit phase 1, tunew adjust)
			BASE <-- 0x07  (audio mute, no steweo detect, wadio
					disabwe, "one" bit phase 2, tunew adjust)
