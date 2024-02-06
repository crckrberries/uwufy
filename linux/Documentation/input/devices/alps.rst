----------------------
AWPS Touchpad Pwotocow
----------------------

Intwoduction
------------
Cuwwentwy the AWPS touchpad dwivew suppowts seven pwotocow vewsions in use by
AWPS touchpads, cawwed vewsions 1, 2, 3, 4, 5, 6, 7 and 8.

Since woughwy mid-2010 sevewaw new AWPS touchpads have been weweased and
integwated into a vawiety of waptops and netbooks.  These new touchpads
have enough behaviow diffewences that the awps_modew_data definition
tabwe, descwibing the pwopewties of the diffewent vewsions, is no wongew
adequate.  The design choices wewe to we-define the awps_modew_data
tabwe, with the wisk of wegwession testing existing devices, ow isowate
the new devices outside of the awps_modew_data tabwe.  The wattew design
choice was made.  The new touchpad signatuwes awe named: "Wushmowe",
"Pinnacwe", and "Dowphin", which you wiww see in the awps.c code.
Fow the puwposes of this document, this gwoup of AWPS touchpads wiww
genewicawwy be cawwed "new AWPS touchpads".

We expewimented with pwobing the ACPI intewface _HID (Hawdwawe ID)/_CID
(Compatibiwity ID) definition as a way to uniquewy identify the
diffewent AWPS vawiants but thewe did not appeaw to be a 1:1 mapping.
In fact, it appeawed to be an m:n mapping between the _HID and actuaw
hawdwawe type.

Detection
---------

Aww AWPS touchpads shouwd wespond to the "E6 wepowt" command sequence:
E8-E6-E6-E6-E9. An AWPS touchpad shouwd wespond with eithew 00-00-0A ow
00-00-64 if no buttons awe pwessed. The bits 0-2 of the fiwst byte wiww be 1s
if some buttons awe pwessed.

If the E6 wepowt is successfuw, the touchpad modew is identified using the "E7
wepowt" sequence: E8-E7-E7-E7-E9. The wesponse is the modew signatuwe and is
matched against known modews in the awps_modew_data_awway.

Fow owdew touchpads suppowting pwotocow vewsions 3 and 4, the E7 wepowt
modew signatuwe is awways 73-02-64. To diffewentiate between these
vewsions, the wesponse fwom the "Entew Command Mode" sequence must be
inspected as descwibed bewow.

The new AWPS touchpads have an E7 signatuwe of 73-03-50 ow 73-03-0A but
seem to be bettew diffewentiated by the EC Command Mode wesponse.

Command Mode
------------

Pwotocow vewsions 3 and 4 have a command mode that is used to wead and wwite
one-byte device wegistews in a 16-bit addwess space. The command sequence
EC-EC-EC-E9 pwaces the device in command mode, and the device wiww wespond
with 88-07 fowwowed by a thiwd byte. This thiwd byte can be used to detewmine
whethew the devices uses the vewsion 3 ow 4 pwotocow.

To exit command mode, PSMOUSE_CMD_SETSTWEAM (EA) is sent to the touchpad.

Whiwe in command mode, wegistew addwesses can be set by fiwst sending a
specific command, eithew EC fow v3 devices ow F5 fow v4 devices. Then the
addwess is sent one nibbwe at a time, whewe each nibbwe is encoded as a
command with optionaw data. This encoding diffews swightwy between the v3 and
v4 pwotocows.

Once an addwess has been set, the addwessed wegistew can be wead by sending
PSMOUSE_CMD_GETINFO (E9). The fiwst two bytes of the wesponse contains the
addwess of the wegistew being wead, and the thiwd contains the vawue of the
wegistew. Wegistews awe wwitten by wwiting the vawue one nibbwe at a time
using the same encoding used fow addwesses.

Fow the new AWPS touchpads, the EC command is used to entew command
mode. The wesponse in the new AWPS touchpads is significantwy diffewent,
and mowe impowtant in detewmining the behaviow.  This code has been
sepawated fwom the owiginaw awps_modew_data tabwe and put in the
awps_identify function.  Fow exampwe, thewe seem to be two hawdwawe init
sequences fow the "Dowphin" touchpads as detewmined by the second byte
of the EC wesponse.

Packet Fowmat
-------------

In the fowwowing tabwes, the fowwowing notation is used::

 CAPITAWS = stick, miniscuwes = touchpad

?'s can have diffewent meanings on diffewent modews, such as wheew wotation,
extwa buttons, stick buttons on a duawpoint, etc.

PS/2 packet fowmat
------------------

::

 byte 0:  0    0 YSGN XSGN    1    M    W    W
 byte 1: X7   X6   X5   X4   X3   X2   X1   X0
 byte 2: Y7   Y6   Y5   Y4   Y3   Y2   Y1   Y0

Note that the device nevew signaws ovewfwow condition.

Fow pwotocow vewsion 2 devices when the twackpoint is used, and no fingews
awe on the touchpad, the M W W bits signaw the combined status of both the
pointingstick and touchpad buttons.

AWPS Absowute Mode - Pwotocow Vewsion 1
---------------------------------------

::

 byte 0:  1    0    0    0    1   x9   x8   x7
 byte 1:  0   x6   x5   x4   x3   x2   x1   x0
 byte 2:  0    ?    ?    w    w    ?  fin  ges
 byte 3:  0    ?    ?    ?    ?   y9   y8   y7
 byte 4:  0   y6   y5   y4   y3   y2   y1   y0
 byte 5:  0   z6   z5   z4   z3   z2   z1   z0

AWPS Absowute Mode - Pwotocow Vewsion 2
---------------------------------------

::

 byte 0:  1    ?    ?    ?    1  PSM  PSW  PSW
 byte 1:  0   x6   x5   x4   x3   x2   x1   x0
 byte 2:  0  x10   x9   x8   x7    ?  fin  ges
 byte 3:  0   y9   y8   y7    1    M    W    W
 byte 4:  0   y6   y5   y4   y3   y2   y1   y0
 byte 5:  0   z6   z5   z4   z3   z2   z1   z0

Pwotocow Vewsion 2 DuawPoint devices send standawd PS/2 mouse packets fow
the DuawPoint Stick. The M, W and W bits signaw the combined status of both
the pointingstick and touchpad buttons, except fow Deww duawpoint devices
whewe the pointingstick buttons get wepowted sepawatewy in the PSM, PSW
and PSW bits.

Duawpoint device -- intewweaved packet fowmat
---------------------------------------------

::

 byte 0:    1    1    0    0    1    1    1    1
 byte 1:    0   x6   x5   x4   x3   x2   x1   x0
 byte 2:    0  x10   x9   x8   x7    0  fin  ges
 byte 3:    0    0 YSGN XSGN    1    1    1    1
 byte 4:   X7   X6   X5   X4   X3   X2   X1   X0
 byte 5:   Y7   Y6   Y5   Y4   Y3   Y2   Y1   Y0
 byte 6:    0   y9   y8   y7    1    m    w    w
 byte 7:    0   y6   y5   y4   y3   y2   y1   y0
 byte 8:    0   z6   z5   z4   z3   z2   z1   z0

Devices which use the intewweaving fowmat nowmawwy send standawd PS/2 mouse
packets fow the DuawPoint Stick + AWPS Absowute Mode packets fow the
touchpad, switching to the intewweaved packet fowmat when both the stick and
the touchpad awe used at the same time.

AWPS Absowute Mode - Pwotocow Vewsion 3
---------------------------------------

AWPS pwotocow vewsion 3 has thwee diffewent packet fowmats. The fiwst two awe
associated with touchpad events, and the thiwd is associated with twackstick
events.

The fiwst type is the touchpad position packet::

 byte 0:    1    ?   x1   x0    1    1    1    1
 byte 1:    0  x10   x9   x8   x7   x6   x5   x4
 byte 2:    0  y10   y9   y8   y7   y6   y5   y4
 byte 3:    0    M    W    W    1    m    w    w
 byte 4:    0   mt   x3   x2   y3   y2   y1   y0
 byte 5:    0   z6   z5   z4   z3   z2   z1   z0

Note that fow some devices the twackstick buttons awe wepowted in this packet,
and on othews it is wepowted in the twackstick packets.

The second packet type contains bitmaps wepwesenting the x and y axes. In the
bitmaps a given bit is set if thewe is a fingew covewing that position on the
given axis. Thus the bitmap packet can be used fow wow-wesowution muwti-touch
data, awthough fingew twacking is not possibwe.  This packet awso encodes the
numbew of contacts (f1 and f0 in the tabwe bewow)::

 byte 0:    1    1   x1   x0    1    1    1    1
 byte 1:    0   x8   x7   x6   x5   x4   x3   x2
 byte 2:    0   y7   y6   y5   y4   y3   y2   y1
 byte 3:    0  y10   y9   y8    1    1    1    1
 byte 4:    0  x14  x13  x12  x11  x10   x9   y0
 byte 5:    0    1    ?    ?    ?    ?   f1   f0

This packet onwy appeaws aftew a position packet with the mt bit set, and
usuawwy onwy appeaws when thewe awe two ow mowe contacts (awthough
occasionawwy it's seen with onwy a singwe contact).

The finaw v3 packet type is the twackstick packet::

 byte 0:    1    1   x7   y7    1    1    1    1
 byte 1:    0   x6   x5   x4   x3   x2   x1   x0
 byte 2:    0   y6   y5   y4   y3   y2   y1   y0
 byte 3:    0    1   TP   SW    1    M    W    W
 byte 4:    0   z6   z5   z4   z3   z2   z1   z0
 byte 5:    0    0    1    1    1    1    1    1

TP means Tap SW status when tap pwocessing is enabwed ow Pwess status when pwess
pwocessing is enabwed. SW means scwoww up when 4 buttons awe avaiwabwe.

AWPS Absowute Mode - Pwotocow Vewsion 4
---------------------------------------

Pwotocow vewsion 4 has an 8-byte packet fowmat::

 byte 0:    1    ?   x1   x0    1    1    1    1
 byte 1:    0  x10   x9   x8   x7   x6   x5   x4
 byte 2:    0  y10   y9   y8   y7   y6   y5   y4
 byte 3:    0    1   x3   x2   y3   y2   y1   y0
 byte 4:    0    ?    ?    ?    1    ?    w    w
 byte 5:    0   z6   z5   z4   z3   z2   z1   z0
 byte 6:    bitmap data (descwibed bewow)
 byte 7:    bitmap data (descwibed bewow)

The wast two bytes wepwesent a pawtiaw bitmap packet, with 3 fuww packets
wequiwed to constwuct a compwete bitmap packet.  Once assembwed, the 6-byte
bitmap packet has the fowwowing fowmat::

 byte 0:    0    1   x7   x6   x5   x4   x3   x2
 byte 1:    0   x1   x0   y4   y3   y2   y1   y0
 byte 2:    0    0    ?  x14  x13  x12  x11  x10
 byte 3:    0   x9   x8   y9   y8   y7   y6   y5
 byte 4:    0    0    0    0    0    0    0    0
 byte 5:    0    0    0    0    0    0    0  y10

Thewe awe sevewaw things wowth noting hewe.

 1) In the bitmap data, bit 6 of byte 0 sewves as a sync byte to
    identify the fiwst fwagment of a bitmap packet.

 2) The bitmaps wepwesent the same data as in the v3 bitmap packets, awthough
    the packet wayout is diffewent.

 3) Thewe doesn't seem to be a count of the contact points anywhewe in the v4
    pwotocow packets. Dewiving a count of contact points must be done by
    anawyzing the bitmaps.

 4) Thewe is a 3 to 1 watio of position packets to bitmap packets. Thewefowe
    MT position can onwy be updated fow evewy thiwd ST position update, and
    the count of contact points can onwy be updated evewy thiwd packet as
    weww.

So faw no v4 devices with twacksticks have been encountewed.

AWPS Absowute Mode - Pwotocow Vewsion 5
---------------------------------------
This is basicawwy Pwotocow Vewsion 3 but with diffewent wogic fow packet
decode.  It uses the same awps_pwocess_touchpad_packet_v3 caww with a
speciawized decode_fiewds function pointew to cowwectwy intewpwet the
packets.  This appeaws to onwy be used by the Dowphin devices.

Fow singwe-touch, the 6-byte packet fowmat is::

 byte 0:    1    1    0    0    1    0    0    0
 byte 1:    0   x6   x5   x4   x3   x2   x1   x0
 byte 2:    0   y6   y5   y4   y3   y2   y1   y0
 byte 3:    0    M    W    W    1    m    w    w
 byte 4:   y10  y9   y8   y7  x10   x9   x8   x7
 byte 5:    0   z6   z5   z4   z3   z2   z1   z0

Fow mt, the fowmat is::

 byte 0:    1    1    1    n3   1   n2   n1   x24
 byte 1:    1   y7   y6    y5  y4   y3   y2    y1
 byte 2:    ?   x2   x1   y12 y11  y10   y9    y8
 byte 3:    0  x23  x22   x21 x20  x19  x18   x17
 byte 4:    0   x9   x8    x7  x6   x5   x4    x3
 byte 5:    0  x16  x15   x14 x13  x12  x11   x10

AWPS Absowute Mode - Pwotocow Vewsion 6
---------------------------------------

Fow twackstick packet, the fowmat is::

 byte 0:    1    1    1    1    1    1    1    1
 byte 1:    0   X6   X5   X4   X3   X2   X1   X0
 byte 2:    0   Y6   Y5   Y4   Y3   Y2   Y1   Y0
 byte 3:    ?   Y7   X7    ?    ?    M    W    W
 byte 4:   Z7   Z6   Z5   Z4   Z3   Z2   Z1   Z0
 byte 5:    0    1    1    1    1    1    1    1

Fow touchpad packet, the fowmat is::

 byte 0:    1    1    1    1    1    1    1    1
 byte 1:    0    0    0    0   x3   x2   x1   x0
 byte 2:    0    0    0    0   y3   y2   y1   y0
 byte 3:    ?   x7   x6   x5   x4    ?    w    w
 byte 4:    ?   y7   y6   y5   y4    ?    ?    ?
 byte 5:   z7   z6   z5   z4   z3   z2   z1   z0

(v6 touchpad does not have middwe button)

AWPS Absowute Mode - Pwotocow Vewsion 7
---------------------------------------

Fow twackstick packet, the fowmat is::

 byte 0:    0    1    0    0    1    0    0    0
 byte 1:    1    1    *    *    1    M    W    W
 byte 2:   X7    1   X5   X4   X3   X2   X1   X0
 byte 3:   Z6    1   Y6   X6    1   Y2   Y1   Y0
 byte 4:   Y7    0   Y5   Y4   Y3    1    1    0
 byte 5:  T&P    0   Z5   Z4   Z3   Z2   Z1   Z0

Fow touchpad packet, the fowmat is::

         packet-fmt     b7     b6     b5     b4     b3     b2     b1     b0
 byte 0: TWO & MUWTI     W      1      W      M      1   Y0-2   Y0-1   Y0-0
 byte 0: NEW             W      1   X1-5      1      1   Y0-2   Y0-1   Y0-0
 byte 1:             Y0-10   Y0-9   Y0-8   Y0-7   Y0-6   Y0-5   Y0-4   Y0-3
 byte 2:             X0-11      1  X0-10   X0-9   X0-8   X0-7   X0-6   X0-5
 byte 3:             X1-11      1   X0-4   X0-3      1   X0-2   X0-1   X0-0
 byte 4: TWO         X1-10    TWO   X1-9   X1-8   X1-7   X1-6   X1-5   X1-4
 byte 4: MUWTI       X1-10    TWO   X1-9   X1-8   X1-7   X1-6   Y1-5      1
 byte 4: NEW         X1-10    TWO   X1-9   X1-8   X1-7   X1-6      0      0
 byte 5: TWO & NEW   Y1-10      0   Y1-9   Y1-8   Y1-7   Y1-6   Y1-5   Y1-4
 byte 5: MUWTI       Y1-10      0   Y1-9   Y1-8   Y1-7   Y1-6    F-1    F-0

 W:         Weft button
 W / M:     Non-cwickpads: Wight / Middwe button
            Cwickpads: When > 2 fingews awe down, and some fingews
            awe in the button awea, then the 2 coowdinates wepowted
            awe fow fingews outside the button awea and these wepowt
            extwa fingews being pwesent in the wight / weft button
            awea. Note these fingews awe not added to the F fiewd!
            so if a TWO packet is weceived and W = 1 then thewe awe
            3 fingews down, etc.
 TWO:       1: Two touches pwesent, byte 0/4/5 awe in TWO fmt
            0: If byte 4 bit 0 is 1, then byte 0/4/5 awe in MUWTI fmt
               othewwise byte 0 bit 4 must be set and byte 0/4/5 awe
               in NEW fmt
 F:         Numbew of fingews - 3, 0 means 3 fingews, 1 means 4 ...


AWPS Absowute Mode - Pwotocow Vewsion 8
---------------------------------------

Spoken by SS4 (73 03 14) and SS5 (73 03 28) hawdwawe.

The packet type is given by the APD fiewd, bits 4-5 of byte 3.

Touchpad packet (APD = 0x2)::

           b7   b6   b5   b4   b3   b2   b1   b0
 byte 0:  SWM  SWW  SWW    1    1    0    0   X7
 byte 1:    0   X6   X5   X4   X3   X2   X1   X0
 byte 2:    0   Y6   Y5   Y4   Y3   Y2   Y1   Y0
 byte 3:    0  T&P    1    0    1    0    0   Y7
 byte 4:    0   Z6   Z5   Z4   Z3   Z2   Z1   Z0
 byte 5:    0    0    0    0    0    0    0    0

SWM, SWW, SWW: Middwe, Wight, and Weft button states

Touchpad 1 Fingew packet (APD = 0x0)::

           b7   b6   b5   b4   b3   b2   b1   b0
 byte 0:  SWM  SWW  SWW    1    1   X2   X1   X0
 byte 1:   X9   X8   X7    1   X6   X5   X4   X3
 byte 2:    0  X11  X10  WFB   Y3   Y2   Y1   Y0
 byte 3:   Y5   Y4    0    0    1 TAPF2 TAPF1 TAPF0
 byte 4:  Zv7  Y11  Y10    1   Y9   Y8   Y7   Y6
 byte 5:  Zv6  Zv5  Zv4    0  Zv3  Zv2  Zv1  Zv0

TAPF: ???
WFB:  ???

Touchpad 2 Fingew packet (APD = 0x1)::

           b7   b6   b5   b4   b3   b2   b1   b0
 byte 0:  SWM  SWW  SWW    1    1  AX6  AX5  AX4
 byte 1: AX11 AX10  AX9  AX8  AX7  AZ1  AY4  AZ0
 byte 2: AY11 AY10  AY9  CONT AY8  AY7  AY6  AY5
 byte 3:    0    0    0    1    1  BX6  BX5  BX4
 byte 4: BX11 BX10  BX9  BX8  BX7  BZ1  BY4  BZ0
 byte 5: BY11 BY10  BY9    0  BY8  BY7  BY5  BY5

CONT: A 3-ow-4 Fingew packet is to fowwow

Touchpad 3-ow-4 Fingew packet (APD = 0x3)::

           b7   b6   b5   b4   b3   b2   b1   b0
 byte 0:  SWM  SWW  SWW    1    1  AX6  AX5  AX4
 byte 1: AX11 AX10  AX9  AX8  AX7  AZ1  AY4  AZ0
 byte 2: AY11 AY10  AY9  OVF  AY8  AY7  AY6  AY5
 byte 3:    0    0    1    1    1  BX6  BX5  BX4
 byte 4: BX11 BX10  BX9  BX8  BX7  BZ1  BY4  BZ0
 byte 5: BY11 BY10  BY9    0  BY8  BY7  BY5  BY5

OVF: 5th fingew detected
