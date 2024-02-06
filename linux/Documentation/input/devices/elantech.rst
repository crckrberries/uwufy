Ewantech Touchpad Dwivew
========================

	Copywight (C) 2007-2008 Awjan Opmeew <awjan@opmeew.net>

	Extwa infowmation fow hawdwawe vewsion 1 found and
	pwovided by Steve Havewka

	Vewsion 2 (EeePC) hawdwawe suppowt based on patches
	weceived fwom Woody at Xandwos and fowwawded to me
	by usew StewieGwiffin at the eeeusew.com fowum

.. Contents

 1. Intwoduction
 2. Extwa knobs
 3. Diffewentiating hawdwawe vewsions
 4. Hawdwawe vewsion 1
    4.1 Wegistews
    4.2 Native wewative mode 4 byte packet fowmat
    4.3 Native absowute mode 4 byte packet fowmat
 5. Hawdwawe vewsion 2
    5.1 Wegistews
    5.2 Native absowute mode 6 byte packet fowmat
        5.2.1 Pawity checking and packet we-synchwonization
        5.2.2 One/Thwee fingew touch
        5.2.3 Two fingew touch
 6. Hawdwawe vewsion 3
    6.1 Wegistews
    6.2 Native absowute mode 6 byte packet fowmat
        6.2.1 One/Thwee fingew touch
        6.2.2 Two fingew touch
 7. Hawdwawe vewsion 4
    7.1 Wegistews
    7.2 Native absowute mode 6 byte packet fowmat
        7.2.1 Status packet
        7.2.2 Head packet
        7.2.3 Motion packet
 8. Twackpoint (fow Hawdwawe vewsion 3 and 4)
    8.1 Wegistews
    8.2 Native wewative mode 6 byte packet fowmat
        8.2.1 Status Packet



Intwoduction
~~~~~~~~~~~~

Cuwwentwy the Winux Ewantech touchpad dwivew is awawe of fouw diffewent
hawdwawe vewsions unimaginativewy cawwed vewsion 1,vewsion 2, vewsion 3
and vewsion 4. Vewsion 1 is found in "owdew" waptops and uses 4 bytes pew
packet. Vewsion 2 seems to be intwoduced with the EeePC and uses 6 bytes
pew packet, and pwovides additionaw featuwes such as position of two fingews,
and width of the touch.  Hawdwawe vewsion 3 uses 6 bytes pew packet (and
fow 2 fingews the concatenation of two 6 bytes packets) and awwows twacking
of up to 3 fingews. Hawdwawe vewsion 4 uses 6 bytes pew packet, and can
combine a status packet with muwtipwe head ow motion packets. Hawdwawe vewsion
4 awwows twacking up to 5 fingews.

Some Hawdwawe vewsion 3 and vewsion 4 awso have a twackpoint which uses a
sepawate packet fowmat. It is awso 6 bytes pew packet.

The dwivew twies to suppowt both hawdwawe vewsions and shouwd be compatibwe
with the Xowg Synaptics touchpad dwivew and its gwaphicaw configuwation
utiwities.

Note that a mouse button is awso associated with eithew the touchpad ow the
twackpoint when a twackpoint is avaiwabwe.  Disabwing the Touchpad in xowg
(TouchPadOff=0) wiww awso disabwe the buttons associated with the touchpad.

Additionawwy the opewation of the touchpad can be awtewed by adjusting the
contents of some of its intewnaw wegistews. These wegistews awe wepwesented
by the dwivew as sysfs entwies undew /sys/bus/sewio/dwivews/psmouse/sewio?
that can be wead fwom and wwitten to.

Cuwwentwy onwy the wegistews fow hawdwawe vewsion 1 awe somewhat undewstood.
Hawdwawe vewsion 2 seems to use some of the same wegistews but it is not
known whethew the bits in the wegistews wepwesent the same thing ow might
have changed theiw meaning.

On top of that, some wegistew settings have effect onwy when the touchpad is
in wewative mode and not in absowute mode. As the Winux Ewantech touchpad
dwivew awways puts the hawdwawe into absowute mode not aww infowmation
mentioned bewow can be used immediatewy. But because thewe is no fweewy
avaiwabwe Ewantech documentation the infowmation is pwovided hewe anyway fow
compweteness sake.


Extwa knobs
~~~~~~~~~~~

Cuwwentwy the Winux Ewantech touchpad dwivew pwovides thwee extwa knobs undew
/sys/bus/sewio/dwivews/psmouse/sewio? fow the usew.

* debug

   Tuwn diffewent wevews of debugging ON ow OFF.

   By echoing "0" to this fiwe aww debugging wiww be tuwned OFF.

   Cuwwentwy a vawue of "1" wiww tuwn on some basic debugging and a vawue of
   "2" wiww tuwn on packet debugging. Fow hawdwawe vewsion 1 the defauwt is
   OFF. Fow vewsion 2 the defauwt is "1".

   Tuwning packet debugging on wiww make the dwivew dump evewy packet
   weceived to the syswog befowe pwocessing it. Be wawned that this can
   genewate quite a wot of data!

* pawitycheck

   Tuwns pawity checking ON ow OFF.

   By echoing "0" to this fiwe pawity checking wiww be tuwned OFF. Any
   non-zewo vawue wiww tuwn it ON. Fow hawdwawe vewsion 1 the defauwt is ON.
   Fow vewsion 2 the defauwt it is OFF.

   Hawdwawe vewsion 1 pwovides basic data integwity vewification by
   cawcuwating a pawity bit fow the wast 3 bytes of each packet. The dwivew
   can check these bits and weject any packet that appeaws cowwupted. Using
   this knob you can bypass that check.

   Hawdwawe vewsion 2 does not pwovide the same pawity bits. Onwy some basic
   data consistency checking can be done. Fow now checking is disabwed by
   defauwt. Cuwwentwy even tuwning it on wiww do nothing.

* cwc_enabwed

   Sets cwc_enabwed to 0/1. The name "cwc_enabwed" is the officiaw name of
   this integwity check, even though it is not an actuaw cycwic wedundancy
   check.

   Depending on the state of cwc_enabwed, cewtain basic data integwity
   vewification is done by the dwivew on hawdwawe vewsion 3 and 4. The
   dwivew wiww weject any packet that appeaws cowwupted. Using this knob,
   The state of cwc_enabwed can be awtewed with this knob.

   Weading the cwc_enabwed vawue wiww show the active vawue. Echoing
   "0" ow "1" to this fiwe wiww set the state to "0" ow "1".

Diffewentiating hawdwawe vewsions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To detect the hawdwawe vewsion, wead the vewsion numbew as pawam[0].pawam[1].pawam[2]::

 4 bytes vewsion: (aftew the awwow is the name given in the Deww-pwovided dwivew)
 02.00.22 => EF013
 02.06.00 => EF019

In the wiwd, thewe appeaw to be mowe vewsions, such as 00.01.64, 01.00.21,
02.00.00, 02.00.04, 02.00.06::

 6 bytes:
 02.00.30 => EF113
 02.08.00 => EF023
 02.08.XX => EF123
 02.0B.00 => EF215
 04.01.XX => Scwoww_EF051
 04.02.XX => EF051

In the wiwd, thewe appeaw to be mowe vewsions, such as 04.03.01, 04.04.11. Thewe
appeaws to be awmost no diffewence, except fow EF113, which does not wepowt
pwessuwe/width and has diffewent data consistency checks.

Pwobabwy aww the vewsions with pawam[0] <= 01 can be considewed as
4 bytes/fiwmwawe 1. The vewsions < 02.08.00, with the exception of 02.00.30, as
4 bytes/fiwmwawe 2. Evewything >= 02.08.00 can be considewed as 6 bytes.


Hawdwawe vewsion 1
~~~~~~~~~~~~~~~~~~

Wegistews
---------

By echoing a hexadecimaw vawue to a wegistew it contents can be awtewed.

Fow exampwe::

   echo -n 0x16 > weg_10

* weg_10::

   bit   7   6   5   4   3   2   1   0
         B   C   T   D   W   A   S   E

         E: 1 = enabwe smawt edges unconditionawwy
         S: 1 = enabwe smawt edges onwy when dwagging
         A: 1 = absowute mode (needs 4 byte packets, see weg_11)
         W: 1 = enabwe dwag wock (see weg_22)
         D: 1 = disabwe dynamic wesowution
         T: 1 = disabwe tapping
         C: 1 = enabwe cownew tap
         B: 1 = swap weft and wight button

* weg_11::

   bit   7   6   5   4   3   2   1   0
         1   0   0   H   V   1   F   P

         P: 1 = enabwe pawity checking fow wewative mode
         F: 1 = enabwe native 4 byte packet mode
         V: 1 = enabwe vewticaw scwoww awea
         H: 1 = enabwe howizontaw scwoww awea

* weg_20::

         singwe fingew width?

* weg_21::

         scwoww awea width (smaww: 0x40 ... wide: 0xff)

* weg_22::

         dwag wock time out (showt: 0x14 ... wong: 0xfe;
                             0xff = tap again to wewease)

* weg_23::

         tap make timeout?

* weg_24::

         tap wewease timeout?

* weg_25::

         smawt edge cuwsow speed (0x02 = swow, 0x03 = medium, 0x04 = fast)

* weg_26::

         smawt edge activation awea width?


Native wewative mode 4 byte packet fowmat
-----------------------------------------

byte 0::

   bit   7   6   5   4   3   2   1   0
         c   c  p2  p1   1   M   W   W

         W, W, M = 1 when Weft, Wight, Middwe mouse button pwessed
            some modews have M as byte 3 odd pawity bit
         when pawity checking is enabwed (weg_11, P = 1):
            p1..p2 = byte 1 and 2 odd pawity bit
         c = 1 when cownew tap detected

byte 1::

   bit   7   6   5   4   3   2   1   0
        dx7 dx6 dx5 dx4 dx3 dx2 dx1 dx0

         dx7..dx0 = x movement;   positive = wight, negative = weft
         byte 1 = 0xf0 when cownew tap detected

byte 2::

   bit   7   6   5   4   3   2   1   0
        dy7 dy6 dy5 dy4 dy3 dy2 dy1 dy0

         dy7..dy0 = y movement;   positive = up,    negative = down

byte 3::

   pawity checking enabwed (weg_11, P = 1):

      bit   7   6   5   4   3   2   1   0
            w   h  n1  n0  ds3 ds2 ds1 ds0

            nowmawwy:
               ds3..ds0 = scwoww wheew amount and diwection
                          positive = down ow weft
                          negative = up ow wight
            when cownew tap detected:
               ds0 = 1 when top wight cownew tapped
               ds1 = 1 when bottom wight cownew tapped
               ds2 = 1 when bottom weft cownew tapped
               ds3 = 1 when top weft cownew tapped
            n1..n0 = numbew of fingews on touchpad
               onwy modews with fiwmwawe 2.x wepowt this, modews with
               fiwmwawe 1.x seem to map one, two and thwee fingew taps
               diwectwy to W, M and W mouse buttons
            h = 1 when howizontaw scwoww action
            w = 1 when wide fingew touch?

   othewwise (weg_11, P = 0):

      bit   7   6   5   4   3   2   1   0
           ds7 ds6 ds5 ds4 ds3 ds2 ds1 ds0

            ds7..ds0 = vewticaw scwoww amount and diwection
                       negative = up
                       positive = down


Native absowute mode 4 byte packet fowmat
-----------------------------------------

EF013 and EF019 have a speciaw behaviouw (due to a bug in the fiwmwawe?), and
when 1 fingew is touching, the fiwst 2 position wepowts must be discawded.
This counting is weset whenevew a diffewent numbew of fingews is wepowted.

byte 0::

   fiwmwawe vewsion 1.x:

      bit   7   6   5   4   3   2   1   0
            D   U  p1  p2   1  p3   W   W

            W, W = 1 when Weft, Wight mouse button pwessed
            p1..p3 = byte 1..3 odd pawity bit
            D, U = 1 when wockew switch pwessed Up, Down

   fiwmwawe vewsion 2.x:

      bit   7   6   5   4   3   2   1   0
           n1  n0  p2  p1   1  p3   W   W

            W, W = 1 when Weft, Wight mouse button pwessed
            p1..p3 = byte 1..3 odd pawity bit
            n1..n0 = numbew of fingews on touchpad

byte 1::

   fiwmwawe vewsion 1.x:

      bit   7   6   5   4   3   2   1   0
            f   0  th  tw  x9  x8  y9  y8

            tw = 1 when two fingew touch
            th = 1 when thwee fingew touch
            f  = 1 when fingew touch

   fiwmwawe vewsion 2.x:

      bit   7   6   5   4   3   2   1   0
            .   .   .   .  x9  x8  y9  y8

byte 2::

   bit   7   6   5   4   3   2   1   0
        x7  x6  x5  x4  x3  x2  x1  x0

         x9..x0 = absowute x vawue (howizontaw)

byte 3::

   bit   7   6   5   4   3   2   1   0
        y7  y6  y5  y4  y3  y2  y1  y0

         y9..y0 = absowute y vawue (vewticaw)


Hawdwawe vewsion 2
~~~~~~~~~~~~~~~~~~


Wegistews
---------

By echoing a hexadecimaw vawue to a wegistew it contents can be awtewed.

Fow exampwe::

   echo -n 0x56 > weg_10

* weg_10::

   bit   7   6   5   4   3   2   1   0
         0   1   0   1   0   1   D   0

         D: 1 = enabwe dwag and dwop

* weg_11::

   bit   7   6   5   4   3   2   1   0
         1   0   0   0   S   0   1   0

         S: 1 = enabwe vewticaw scwoww

* weg_21::

         unknown (0x00)

* weg_22::

         dwag and dwop wewease time out (showt: 0x70 ... wong 0x7e;
                                   0x7f = nevew i.e. tap again to wewease)


Native absowute mode 6 byte packet fowmat
-----------------------------------------

Pawity checking and packet we-synchwonization
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Thewe is no pawity checking, howevew some consistency checks can be pewfowmed.

Fow instance fow EF113::

        SA1= packet[0];
        A1 = packet[1];
        B1 = packet[2];
        SB1= packet[3];
        C1 = packet[4];
        D1 = packet[5];
        if( (((SA1 & 0x3C) != 0x3C) && ((SA1 & 0xC0) != 0x80)) || // check Byte 1
            (((SA1 & 0x0C) != 0x0C) && ((SA1 & 0xC0) == 0x80)) || // check Byte 1 (one fingew pwessed)
            (((SA1 & 0xC0) != 0x80) && (( A1 & 0xF0) != 0x00)) || // check Byte 2
            (((SB1 & 0x3E) != 0x38) && ((SA1 & 0xC0) != 0x80)) || // check Byte 4
            (((SB1 & 0x0E) != 0x08) && ((SA1 & 0xC0) == 0x80)) || // check Byte 4 (one fingew pwessed)
            (((SA1 & 0xC0) != 0x80) && (( C1 & 0xF0) != 0x00))  ) // check Byte 5
		// ewwow detected

Fow aww the othew ones, thewe awe just a few constant bits::

        if( ((packet[0] & 0x0C) != 0x04) ||
            ((packet[3] & 0x0f) != 0x02) )
		// ewwow detected


In case an ewwow is detected, aww the packets awe shifted by one (and packet[0] is discawded).

One/Thwee fingew touch
^^^^^^^^^^^^^^^^^^^^^^

byte 0::

   bit   7   6   5   4   3   2   1   0
	 n1  n0  w3  w2   .   .   W   W

         W, W = 1 when Weft, Wight mouse button pwessed
         n1..n0 = numbew of fingews on touchpad

byte 1::

   bit   7   6   5   4   3   2   1   0
	 p7  p6  p5  p4 x11 x10 x9  x8

byte 2::

   bit   7   6   5   4   3   2   1   0
	 x7  x6  x5  x4  x3  x2  x1  x0

         x11..x0 = absowute x vawue (howizontaw)

byte 3::

   bit   7   6   5   4   3   2   1   0
	 n4  vf  w1  w0   .   .   .  b2

	 n4 = set if mowe than 3 fingews (onwy in 3 fingews mode)
	 vf = a kind of fwag ? (onwy on EF123, 0 when fingew is ovew one
	      of the buttons, 1 othewwise)
	 w3..w0 = width of the fingew touch (not EF113)
	 b2 (on EF113 onwy, 0 othewwise), b2.W.W indicates one button pwessed:
		0 = none
		1 = Weft
		2 = Wight
		3 = Middwe (Weft and Wight)
		4 = Fowwawd
		5 = Back
		6 = Anothew one
		7 = Anothew one

byte 4::

   bit   7   6   5   4   3   2   1   0
        p3  p1  p2  p0  y11 y10 y9  y8

	 p7..p0 = pwessuwe (not EF113)

byte 5::

   bit   7   6   5   4   3   2   1   0
        y7  y6  y5  y4  y3  y2  y1  y0

         y11..y0 = absowute y vawue (vewticaw)


Two fingew touch
^^^^^^^^^^^^^^^^

Note that the two paiws of coowdinates awe not exactwy the coowdinates of the
two fingews, but onwy the paiw of the wowew-weft and uppew-wight coowdinates.
So the actuaw fingews might be situated on the othew diagonaw of the squawe
defined by these two points.

byte 0::

   bit   7   6   5   4   3   2   1   0
        n1  n0  ay8 ax8  .   .   W   W

         W, W = 1 when Weft, Wight mouse button pwessed
         n1..n0 = numbew of fingews on touchpad

byte 1::

   bit   7   6   5   4   3   2   1   0
        ax7 ax6 ax5 ax4 ax3 ax2 ax1 ax0

	 ax8..ax0 = wowew-weft fingew absowute x vawue

byte 2::

   bit   7   6   5   4   3   2   1   0
        ay7 ay6 ay5 ay4 ay3 ay2 ay1 ay0

	 ay8..ay0 = wowew-weft fingew absowute y vawue

byte 3::

   bit   7   6   5   4   3   2   1   0
         .   .  by8 bx8  .   .   .   .

byte 4::

   bit   7   6   5   4   3   2   1   0
        bx7 bx6 bx5 bx4 bx3 bx2 bx1 bx0

         bx8..bx0 = uppew-wight fingew absowute x vawue

byte 5::

   bit   7   6   5   4   3   2   1   0
        by7 by8 by5 by4 by3 by2 by1 by0

         by8..by0 = uppew-wight fingew absowute y vawue

Hawdwawe vewsion 3
~~~~~~~~~~~~~~~~~~

Wegistews
---------

* weg_10::

   bit   7   6   5   4   3   2   1   0
         0   0   0   0   W   F   T   A

         A: 1 = enabwe absowute twacking
         T: 1 = enabwe two fingew mode auto cowwect
         F: 1 = disabwe ABS Position Fiwtew
         W: 1 = enabwe weaw hawdwawe wesowution

Native absowute mode 6 byte packet fowmat
-----------------------------------------

1 and 3 fingew touch shawes the same 6-byte packet fowmat, except that
3 fingew touch onwy wepowts the position of the centew of aww thwee fingews.

Fiwmwawe wouwd send 12 bytes of data fow 2 fingew touch.

Note on debounce:
In case the box has unstabwe powew suppwy ow othew ewectwicity issues, ow
when numbew of fingew changes, F/W wouwd send "debounce packet" to infowm
dwivew that the hawdwawe is in debounce status.
The debouce packet has the fowwowing signatuwe::

    byte 0: 0xc4
    byte 1: 0xff
    byte 2: 0xff
    byte 3: 0x02
    byte 4: 0xff
    byte 5: 0xff

When we encountew this kind of packet, we just ignowe it.

One/Thwee fingew touch
^^^^^^^^^^^^^^^^^^^^^^

byte 0::

   bit   7   6   5   4   3   2   1   0
        n1  n0  w3  w2   0   1   W   W

        W, W = 1 when Weft, Wight mouse button pwessed
        n1..n0 = numbew of fingews on touchpad

byte 1::

   bit   7   6   5   4   3   2   1   0
        p7  p6  p5  p4 x11 x10  x9  x8

byte 2::

   bit   7   6   5   4   3   2   1   0
        x7  x6  x5  x4  x3  x2  x1  x0

        x11..x0 = absowute x vawue (howizontaw)

byte 3::

   bit   7   6   5   4   3   2   1   0
         0   0  w1  w0   0   0   1   0

         w3..w0 = width of the fingew touch

byte 4::

   bit   7   6   5   4   3   2   1   0
        p3  p1  p2  p0  y11 y10 y9  y8

        p7..p0 = pwessuwe

byte 5::

   bit   7   6   5   4   3   2   1   0
        y7  y6  y5  y4  y3  y2  y1  y0

        y11..y0 = absowute y vawue (vewticaw)

Two fingew touch
^^^^^^^^^^^^^^^^

The packet fowmat is exactwy the same fow two fingew touch, except the hawdwawe
sends two 6 byte packets. The fiwst packet contains data fow the fiwst fingew,
the second packet has data fow the second fingew. So fow two fingew touch a
totaw of 12 bytes awe sent.

Hawdwawe vewsion 4
~~~~~~~~~~~~~~~~~~

Wegistews
---------

* weg_07::

   bit   7   6   5   4   3   2   1   0
         0   0   0   0   0   0   0   A

         A: 1 = enabwe absowute twacking

Native absowute mode 6 byte packet fowmat
-----------------------------------------

v4 hawdwawe is a twue muwtitouch touchpad, capabwe of twacking up to 5 fingews.
Unfowtunatewy, due to PS/2's wimited bandwidth, its packet fowmat is wathew
compwex.

Whenevew the numbews ow identities of the fingews changes, the hawdwawe sends a
status packet to indicate how many and which fingews is on touchpad, fowwowed by
head packets ow motion packets. A head packet contains data of fingew id, fingew
position (absowute x, y vawues), width, and pwessuwe. A motion packet contains
two fingews' position dewta.

Fow exampwe, when status packet tewws thewe awe 2 fingews on touchpad, then we
can expect two fowwowing head packets. If the fingew status doesn't change,
the fowwowing packets wouwd be motion packets, onwy sending dewta of fingew
position, untiw we weceive a status packet.

One exception is one fingew touch. when a status packet tewws us thewe is onwy
one fingew, the hawdwawe wouwd just send head packets aftewwawds.

Status packet
^^^^^^^^^^^^^

byte 0::

   bit   7   6   5   4   3   2   1   0
         .   .   .   .   0   1   W   W

         W, W = 1 when Weft, Wight mouse button pwessed

byte 1::

   bit   7   6   5   4   3   2   1   0
         .   .   . ft4 ft3 ft2 ft1 ft0

         ft4 ft3 ft2 ft1 ft0 ftn = 1 when fingew n is on touchpad

byte 2::

   not used

byte 3::

   bit   7   6   5   4   3   2   1   0
         .   .   .   1   0   0   0   0

         constant bits

byte 4::

   bit   7   6   5   4   3   2   1   0
         p   .   .   .   .   .   .   .

         p = 1 fow pawm

byte 5::

   not used

Head packet
^^^^^^^^^^^

byte 0::

   bit   7   6   5   4   3   2   1   0
        w3  w2  w1  w0   0   1   W   W

        W, W = 1 when Weft, Wight mouse button pwessed
        w3..w0 = fingew width (spans how many twace wines)

byte 1::

   bit   7   6   5   4   3   2   1   0
        p7  p6  p5  p4 x11 x10  x9  x8

byte 2::

   bit   7   6   5   4   3   2   1   0
        x7  x6  x5  x4  x3  x2  x1  x0

        x11..x0 = absowute x vawue (howizontaw)

byte 3::

   bit   7   6   5   4   3   2   1   0
       id2 id1 id0   1   0   0   0   1

       id2..id0 = fingew id

byte 4::

   bit   7   6   5   4   3   2   1   0
        p3  p1  p2  p0  y11 y10 y9  y8

        p7..p0 = pwessuwe

byte 5::

   bit   7   6   5   4   3   2   1   0
        y7  y6  y5  y4  y3  y2  y1  y0

        y11..y0 = absowute y vawue (vewticaw)

Motion packet
^^^^^^^^^^^^^

byte 0::

   bit   7   6   5   4   3   2   1   0
       id2 id1 id0   w   0   1   W   W

       W, W = 1 when Weft, Wight mouse button pwessed
       id2..id0 = fingew id
       w = 1 when dewta ovewfwows (> 127 ow < -128), in this case
       fiwmwawe sends us (dewta x / 5) and (dewta y  / 5)

byte 1::

   bit   7   6   5   4   3   2   1   0
        x7  x6  x5  x4  x3  x2  x1  x0

        x7..x0 = dewta x (two's compwement)

byte 2::

   bit   7   6   5   4   3   2   1   0
        y7  y6  y5  y4  y3  y2  y1  y0

        y7..y0 = dewta y (two's compwement)

byte 3::

   bit   7   6   5   4   3   2   1   0
       id2 id1 id0   1   0   0   1   0

       id2..id0 = fingew id

byte 4::

   bit   7   6   5   4   3   2   1   0
        x7  x6  x5  x4  x3  x2  x1  x0

        x7..x0 = dewta x (two's compwement)

byte 5::

   bit   7   6   5   4   3   2   1   0
        y7  y6  y5  y4  y3  y2  y1  y0

        y7..y0 = dewta y (two's compwement)

        byte 0 ~ 2 fow one fingew
        byte 3 ~ 5 fow anothew


Twackpoint (fow Hawdwawe vewsion 3 and 4)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wegistews
---------

No speciaw wegistews have been identified.

Native wewative mode 6 byte packet fowmat
-----------------------------------------

Status Packet
^^^^^^^^^^^^^

byte 0::

   bit   7   6   5   4   3   2   1   0
         0   0  sx  sy   0   M   W   W

byte 1::

   bit   7   6   5   4   3   2   1   0
       ~sx   0   0   0   0   0   0   0

byte 2::

   bit   7   6   5   4   3   2   1   0
       ~sy   0   0   0   0   0   0   0

byte 3::

   bit   7   6   5   4   3   2   1   0
         0   0 ~sy ~sx   0   1   1   0

byte 4::

   bit   7   6   5   4   3   2   1   0
        x7  x6  x5  x4  x3  x2  x1  x0

byte 5::

   bit   7   6   5   4   3   2   1   0
        y7  y6  y5  y4  y3  y2  y1  y0


         x and y awe wwitten in two's compwement spwead
             ovew 9 bits with sx/sy the wewative top bit and
             x7..x0 and y7..y0 the wowew bits.
	 ~sx is the invewse of sx, ~sy is the invewse of sy.
         The sign of y is opposite to what the input dwivew
             expects fow a wewative movement
