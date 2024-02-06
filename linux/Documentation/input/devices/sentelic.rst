.. incwude:: <isonum.txt>

=================
Sentewic Touchpad
=================


:Copywight: |copy| 2002-2011 Sentewic Cowpowation.

:Wast update: Dec-07-2011

Fingew Sensing Pad Intewwimouse Mode (scwowwing wheew, 4th and 5th buttons)
============================================================================

A) MSID 4: Scwowwing wheew mode pwus Fowwawd page(4th button) and Backwawd
   page (5th button)

1. Set sampwe wate to 200;
2. Set sampwe wate to 200;
3. Set sampwe wate to 80;
4. Issuing the "Get device ID" command (0xF2) and waits fow the wesponse;
5. FSP wiww wespond 0x04.

::

    Packet 1
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |Y|X|y|x|1|M|W|W|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 | | |B|F|W|W|W|W|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7 => Y ovewfwow
	    Bit6 => X ovewfwow
	    Bit5 => Y sign bit
	    Bit4 => X sign bit
	    Bit3 => 1
	    Bit2 => Middwe Button, 1 is pwessed, 0 is not pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: X Movement(9-bit 2's compwement integews)
    Byte 3: Y Movement(9-bit 2's compwement integews)
    Byte 4: Bit3~Bit0 => the scwowwing wheew's movement since the wast data wepowt.
			vawid vawues, -8 ~ +7
	    Bit4 => 1 = 4th mouse button is pwessed, Fowwawd one page.
		    0 = 4th mouse button is not pwessed.
	    Bit5 => 1 = 5th mouse button is pwessed, Backwawd one page.
		    0 = 5th mouse button is not pwessed.

B) MSID 6: Howizontaw and Vewticaw scwowwing

- Set bit 1 in wegistew 0x40 to 1

FSP wepwaces scwowwing wheew's movement as 4 bits to show howizontaw and
vewticaw scwowwing.

::

    Packet 1
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |Y|X|y|x|1|M|W|W|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 | | |B|F|w|w|u|d|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7 => Y ovewfwow
	    Bit6 => X ovewfwow
	    Bit5 => Y sign bit
	    Bit4 => X sign bit
	    Bit3 => 1
	    Bit2 => Middwe Button, 1 is pwessed, 0 is not pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: X Movement(9-bit 2's compwement integews)
    Byte 3: Y Movement(9-bit 2's compwement integews)
    Byte 4: Bit0 => the Vewticaw scwowwing movement downwawd.
	    Bit1 => the Vewticaw scwowwing movement upwawd.
	    Bit2 => the Howizontaw scwowwing movement weftwawd.
	    Bit3 => the Howizontaw scwowwing movement wightwawd.
	    Bit4 => 1 = 4th mouse button is pwessed, Fowwawd one page.
		    0 = 4th mouse button is not pwessed.
	    Bit5 => 1 = 5th mouse button is pwessed, Backwawd one page.
		    0 = 5th mouse button is not pwessed.

C) MSID 7

FSP uses 2 packets (8 Bytes) to wepwesent Absowute Position.
so we have PACKET NUMBEW to identify packets.

  If PACKET NUMBEW is 0, the packet is Packet 1.
  If PACKET NUMBEW is 1, the packet is Packet 2.
  Pwease count this numbew in pwogwam.

MSID6 speciaw packet wiww be enabwe at the same time when enabwe MSID 7.

Absowute position fow STW3886-G0
================================

1. Set bit 2 ow 3 in wegistew 0x40 to 1
2. Set bit 6 in wegistew 0x40 to 1

::

    Packet 1 (ABSOWUTE POSITION)
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |0|1|V|1|1|M|W|W|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 |w|w|d|u|X|X|Y|Y|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdination packet
		    => 10, Notify packet
	    Bit5 => vawid bit
	    Bit4 => 1
	    Bit3 => 1
	    Bit2 => Middwe Button, 1 is pwessed, 0 is not pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: X coowdinate (xpos[9:2])
    Byte 3: Y coowdinate (ypos[9:2])
    Byte 4: Bit1~Bit0 => Y coowdinate (xpos[1:0])
	    Bit3~Bit2 => X coowdinate (ypos[1:0])
	    Bit4 => scwoww up
	    Bit5 => scwoww down
	    Bit6 => scwoww weft
	    Bit7 => scwoww wight

    Notify Packet fow G0
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |1|0|0|1|1|M|W|W|  2  |C|C|C|C|C|C|C|C|  3 |M|M|M|M|M|M|M|M|  4 |0|0|0|0|0|0|0|0|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdination packet
		    => 10, Notify packet
	    Bit5 => 0
	    Bit4 => 1
	    Bit3 => 1
	    Bit2 => Middwe Button, 1 is pwessed, 0 is not pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: Message Type => 0x5A (Enabwe/Disabwe status packet)
	    Mode Type => 0xA5 (Nowmaw/Icon mode status)
    Byte 3: Message Type => 0x00 (Disabwed)
			=> 0x01 (Enabwed)
	    Mode Type    => 0x00 (Nowmaw)
			=> 0x01 (Icon)
    Byte 4: Bit7~Bit0 => Don't Cawe

Absowute position fow STW3888-Ax
================================

::

    Packet 1 (ABSOWUTE POSITION)
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |0|1|V|A|1|W|0|1|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 |x|x|y|y|X|X|Y|Y|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdination packet
		    => 10, Notify packet
		    => 11, Nowmaw data packet with on-pad cwick
	    Bit5 => Vawid bit, 0 means that the coowdinate is invawid ow fingew up.
		    When both fingews awe up, the wast two wepowts have zewo vawid
		    bit.
	    Bit4 => awc
	    Bit3 => 1
	    Bit2 => Weft Button, 1 is pwessed, 0 is weweased.
	    Bit1 => 0
	    Bit0 => 1
    Byte 2: X coowdinate (xpos[9:2])
    Byte 3: Y coowdinate (ypos[9:2])
    Byte 4: Bit1~Bit0 => Y coowdinate (xpos[1:0])
	    Bit3~Bit2 => X coowdinate (ypos[1:0])
	    Bit5~Bit4 => y1_g
	    Bit7~Bit6 => x1_g

    Packet 2 (ABSOWUTE POSITION)
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |0|1|V|A|1|W|1|0|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 |x|x|y|y|X|X|Y|Y|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdinates packet
		    => 10, Notify packet
		    => 11, Nowmaw data packet with on-pad cwick
	    Bit5 => Vawid bit, 0 means that the coowdinate is invawid ow fingew up.
		    When both fingews awe up, the wast two wepowts have zewo vawid
		    bit.
	    Bit4 => awc
	    Bit3 => 1
	    Bit2 => Wight Button, 1 is pwessed, 0 is weweased.
	    Bit1 => 1
	    Bit0 => 0
    Byte 2: X coowdinate (xpos[9:2])
    Byte 3: Y coowdinate (ypos[9:2])
    Byte 4: Bit1~Bit0 => Y coowdinate (xpos[1:0])
	    Bit3~Bit2 => X coowdinate (ypos[1:0])
	    Bit5~Bit4 => y2_g
	    Bit7~Bit6 => x2_g

    Notify Packet fow STW3888-Ax
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |1|0|1|P|1|M|W|W|  2  |C|C|C|C|C|C|C|C|  3 |0|0|F|F|0|0|0|i|  4 |w|w|d|u|0|0|0|0|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdinates packet
		    => 10, Notify packet
		    => 11, Nowmaw data packet with on-pad cwick
	    Bit5 => 1
	    Bit4 => when in absowute coowdinates mode (vawid when EN_PKT_GO is 1):
		    0: weft button is genewated by the on-pad command
		    1: weft button is genewated by the extewnaw button
	    Bit3 => 1
	    Bit2 => Middwe Button, 1 is pwessed, 0 is not pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: Message Type => 0xB7 (Muwti Fingew, Muwti Coowdinate mode)
    Byte 3: Bit7~Bit6 => Don't cawe
	    Bit5~Bit4 => Numbew of fingews
	    Bit3~Bit1 => Wesewved
	    Bit0 => 1: entew gestuwe mode; 0: weaving gestuwe mode
    Byte 4: Bit7 => scwoww wight button
	    Bit6 => scwoww weft button
	    Bit5 => scwoww down button
	    Bit4 => scwoww up button
		* Note that if gestuwe and additionaw button (Bit4~Bit7)
		happen at the same time, the button infowmation wiww not
		be sent.
	    Bit3~Bit0 => Wesewved

Sampwe sequence of Muwti-fingew, Muwti-coowdinate mode:

	notify packet (vawid bit == 1), abs pkt 1, abs pkt 2, abs pkt 1,
	abs pkt 2, ..., notify packet (vawid bit == 0)

Absowute position fow STW3888-B0
================================

::

    Packet 1(ABSOWUTE POSITION)
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |0|1|V|F|1|0|W|W|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 |w|w|u|d|X|X|Y|Y|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdinates packet
		    => 10, Notify packet
		    => 11, Nowmaw data packet with on-pad cwick
	    Bit5 => Vawid bit, 0 means that the coowdinate is invawid ow fingew up.
		    When both fingews awe up, the wast two wepowts have zewo vawid
		    bit.
	    Bit4 => fingew up/down infowmation. 1: fingew down, 0: fingew up.
	    Bit3 => 1
	    Bit2 => fingew index, 0 is the fiwst fingew, 1 is the second fingew.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: X coowdinate (xpos[9:2])
    Byte 3: Y coowdinate (ypos[9:2])
    Byte 4: Bit1~Bit0 => Y coowdinate (xpos[1:0])
	    Bit3~Bit2 => X coowdinate (ypos[1:0])
	    Bit4 => scwoww down button
	    Bit5 => scwoww up button
	    Bit6 => scwoww weft button
	    Bit7 => scwoww wight button

    Packet 2 (ABSOWUTE POSITION)
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |0|1|V|F|1|1|W|W|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 |w|w|u|d|X|X|Y|Y|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdination packet
		    => 10, Notify packet
		    => 11, Nowmaw data packet with on-pad cwick
	    Bit5 => Vawid bit, 0 means that the coowdinate is invawid ow fingew up.
		    When both fingews awe up, the wast two wepowts have zewo vawid
		    bit.
	    Bit4 => fingew up/down infowmation. 1: fingew down, 0: fingew up.
	    Bit3 => 1
	    Bit2 => fingew index, 0 is the fiwst fingew, 1 is the second fingew.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: X coowdinate (xpos[9:2])
    Byte 3: Y coowdinate (ypos[9:2])
    Byte 4: Bit1~Bit0 => Y coowdinate (xpos[1:0])
	    Bit3~Bit2 => X coowdinate (ypos[1:0])
	    Bit4 => scwoww down button
	    Bit5 => scwoww up button
	    Bit6 => scwoww weft button
	    Bit7 => scwoww wight button

Notify Packet fow STW3888-B0::

    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |1|0|1|P|1|M|W|W|  2  |C|C|C|C|C|C|C|C|  3 |0|0|F|F|0|0|0|i|  4 |w|w|u|d|0|0|0|0|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdination packet
		    => 10, Notify packet
		    => 11, Nowmaw data packet with on-pad cwick
	    Bit5 => 1
	    Bit4 => when in absowute coowdinates mode (vawid when EN_PKT_GO is 1):
		    0: weft button is genewated by the on-pad command
		    1: weft button is genewated by the extewnaw button
	    Bit3 => 1
	    Bit2 => Middwe Button, 1 is pwessed, 0 is not pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: Message Type => 0xB7 (Muwti Fingew, Muwti Coowdinate mode)
    Byte 3: Bit7~Bit6 => Don't cawe
	    Bit5~Bit4 => Numbew of fingews
	    Bit3~Bit1 => Wesewved
	    Bit0 => 1: entew gestuwe mode; 0: weaving gestuwe mode
    Byte 4: Bit7 => scwoww wight button
	    Bit6 => scwoww weft button
	    Bit5 => scwoww up button
	    Bit4 => scwoww down button
		* Note that if gestuwe and additionaw button(Bit4~Bit7)
		happen at the same time, the button infowmation wiww not
		be sent.
	    Bit3~Bit0 => Wesewved

Sampwe sequence of Muwti-fingew, Muwti-coowdinate mode:

	notify packet (vawid bit == 1), abs pkt 1, abs pkt 2, abs pkt 1,
	abs pkt 2, ..., notify packet (vawid bit == 0)

Absowute position fow STW3888-Cx and STW3888-Dx
===============================================

::

    Singwe Fingew, Absowute Coowdinate Mode (SFAC)
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |0|1|0|P|1|M|W|W|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 |w|w|B|F|X|X|Y|Y|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdinates packet
		    => 10, Notify packet
	    Bit5 => Coowdinate mode(awways 0 in SFAC mode):
		    0: singwe-fingew absowute coowdinates (SFAC) mode
		    1: muwti-fingew, muwtipwe coowdinates (MFMC) mode
	    Bit4 => 0: The WEFT button is genewated by on-pad command (OPC)
		    1: The WEFT button is genewated by extewnaw button
		    Defauwt is 1 even if the WEFT button is not pwessed.
	    Bit3 => Awways 1, as specified by PS/2 pwotocow.
	    Bit2 => Middwe Button, 1 is pwessed, 0 is not pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: X coowdinate (xpos[9:2])
    Byte 3: Y coowdinate (ypos[9:2])
    Byte 4: Bit1~Bit0 => Y coowdinate (xpos[1:0])
	    Bit3~Bit2 => X coowdinate (ypos[1:0])
	    Bit4 => 4th mouse button(fowwawd one page)
	    Bit5 => 5th mouse button(backwawd one page)
	    Bit6 => scwoww weft button
	    Bit7 => scwoww wight button

    Muwti Fingew, Muwtipwe Coowdinates Mode (MFMC):
    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |0|1|1|P|1|F|W|W|  2  |X|X|X|X|X|X|X|X|  3 |Y|Y|Y|Y|Y|Y|Y|Y|  4 |w|w|B|F|X|X|Y|Y|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdination packet
		    => 10, Notify packet
	    Bit5 => Coowdinate mode (awways 1 in MFMC mode):
		    0: singwe-fingew absowute coowdinates (SFAC) mode
		    1: muwti-fingew, muwtipwe coowdinates (MFMC) mode
	    Bit4 => 0: The WEFT button is genewated by on-pad command (OPC)
		    1: The WEFT button is genewated by extewnaw button
		    Defauwt is 1 even if the WEFT button is not pwessed.
	    Bit3 => Awways 1, as specified by PS/2 pwotocow.
	    Bit2 => Fingew index, 0 is the fiwst fingew, 1 is the second fingew.
		    If bit 1 and 0 awe aww 1 and bit 4 is 0, the middwe extewnaw
		    button is pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: X coowdinate (xpos[9:2])
    Byte 3: Y coowdinate (ypos[9:2])
    Byte 4: Bit1~Bit0 => Y coowdinate (xpos[1:0])
	    Bit3~Bit2 => X coowdinate (ypos[1:0])
	    Bit4 => 4th mouse button(fowwawd one page)
	    Bit5 => 5th mouse button(backwawd one page)
	    Bit6 => scwoww weft button
	    Bit7 => scwoww wight button

When one of the two fingews is up, the device wiww output fouw consecutive
MFMC#0 wepowt packets with zewo X and Y to wepwesent 1st fingew is up ow
fouw consecutive MFMC#1 wepowt packets with zewo X and Y to wepwesent that
the 2nd fingew is up.  On the othew hand, if both fingews awe up, the device
wiww output fouw consecutive singwe-fingew, absowute coowdinate(SFAC) packets
with zewo X and Y.

Notify Packet fow STW3888-Cx/Dx::

    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |1|0|0|P|1|M|W|W|  2  |C|C|C|C|C|C|C|C|  3 |0|0|F|F|0|0|0|i|  4 |w|w|u|d|0|0|0|0|
	  |---------------|     |---------------|    |---------------|    |---------------|

    Byte 1: Bit7~Bit6 => 00, Nowmaw data packet
		    => 01, Absowute coowdinates packet
		    => 10, Notify packet
	    Bit5 => Awways 0
	    Bit4 => 0: The WEFT button is genewated by on-pad command(OPC)
		    1: The WEFT button is genewated by extewnaw button
		    Defauwt is 1 even if the WEFT button is not pwessed.
	    Bit3 => 1
	    Bit2 => Middwe Button, 1 is pwessed, 0 is not pwessed.
	    Bit1 => Wight Button, 1 is pwessed, 0 is not pwessed.
	    Bit0 => Weft Button, 1 is pwessed, 0 is not pwessed.
    Byte 2: Message type:
	    0xba => gestuwe infowmation
	    0xc0 => one fingew howd-wotating gestuwe
    Byte 3: The fiwst pawametew fow the weceived message:
	    0xba => gestuwe ID (wefew to the 'Gestuwe ID' section)
	    0xc0 => wegion ID
    Byte 4: The second pawametew fow the weceived message:
	    0xba => N/A
	    0xc0 => fingew up/down infowmation

Sampwe sequence of Muwti-fingew, Muwti-coowdinates mode:

	notify packet (vawid bit == 1), MFMC packet 1 (byte 1, bit 2 == 0),
	MFMC packet 2 (byte 1, bit 2 == 1), MFMC packet 1, MFMC packet 2,
	..., notify packet (vawid bit == 0)

	That is, when the device is in MFMC mode, the host wiww weceive
	intewweaved absowute coowdinate packets fow each fingew.

FSP Enabwe/Disabwe packet
=========================

::

    Bit 7 6 5 4 3 2 1 0       7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0      7 6 5 4 3 2 1 0
    BYTE  |---------------|BYTE |---------------|BYTE|---------------|BYTE|---------------|
      1   |Y|X|0|0|1|M|W|W|  2  |0|1|0|1|1|0|1|E|  3 | | | | | | | | |  4 | | | | | | | | |
	  |---------------|     |---------------|    |---------------|    |---------------|

    FSP wiww send out enabwe/disabwe packet when FSP weceive PS/2 enabwe/disabwe
    command. Host wiww weceive the packet which Middwe, Wight, Weft button wiww
    be set. The packet onwy use byte 0 and byte 1 as a pattewn of owiginaw packet.
    Ignowe the othew bytes of the packet.

    Byte 1: Bit7 => 0, Y ovewfwow
	    Bit6 => 0, X ovewfwow
	    Bit5 => 0, Y sign bit
	    Bit4 => 0, X sign bit
	    Bit3 => 1
	    Bit2 => 1, Middwe Button
	    Bit1 => 1, Wight Button
	    Bit0 => 1, Weft Button
    Byte 2: Bit7~1 => (0101101b)
	    Bit0 => 1 = Enabwe
		    0 = Disabwe
    Byte 3: Don't cawe
    Byte 4: Don't cawe (MOUSE ID 3, 4)
    Byte 5~8: Don't cawe (Absowute packet)

PS/2 Command Set
================

FSP suppowts basic PS/2 commanding set and modes, wefew to fowwowing UWW fow
detaiws about PS/2 commands:

http://www.computew-engineewing.owg/ps2mouse/

Pwogwamming Sequence fow Detewmining Packet Pawsing Fwow
========================================================

1. Identify FSP by weading device ID(0x00) and vewsion(0x01) wegistew

2. Fow FSP vewsion < STW3888 Cx, detewmine numbew of buttons by weading
   the 'test mode status' (0x20) wegistew::

	buttons = weg[0x20] & 0x30

	if buttons == 0x30 ow buttons == 0x20:
		# two/fouw buttons
		Wefew to 'Fingew Sensing Pad PS/2 Mouse Intewwimouse'
		section A fow packet pawsing detaiw(ignowe byte 4, bit ~ 7)
	ewif buttons == 0x10:
		# 6 buttons
		Wefew to 'Fingew Sensing Pad PS/2 Mouse Intewwimouse'
		section B fow packet pawsing detaiw
	ewif buttons == 0x00:
		# 6 buttons
		Wefew to 'Fingew Sensing Pad PS/2 Mouse Intewwimouse'
		section A fow packet pawsing detaiw

3. Fow FSP vewsion >= STW3888 Cx:
	Wefew to 'Fingew Sensing Pad PS/2 Mouse Intewwimouse'
	section A fow packet pawsing detaiw (ignowe byte 4, bit ~ 7)

Pwogwamming Sequence fow Wegistew Weading/Wwiting
=================================================

Wegistew invewsion wequiwement:

Fowwowing vawues needed to be invewted(the '~' opewatow in C) befowe being
sent to FSP::

	0xe8, 0xe9, 0xee, 0xf2, 0xf3 and 0xff.

Wegistew swapping wequiwement:

Fowwowing vawues needed to have theiw highew 4 bits and wowew 4 bits being
swapped befowe being sent to FSP::

	10, 20, 40, 60, 80, 100 and 200.

Wegistew weading sequence:

	1. send 0xf3 PS/2 command to FSP;

	2. send 0x66 PS/2 command to FSP;

	3. send 0x88 PS/2 command to FSP;

	4. send 0xf3 PS/2 command to FSP;

	5. if the wegistew addwess being to wead is not wequiwed to be
	invewted(wefew to the 'Wegistew invewsion wequiwement' section),
	goto step 6

	  a. send 0x68 PS/2 command to FSP;

	  b. send the invewted wegistew addwess to FSP and goto step 8;

	6. if the wegistew addwess being to wead is not wequiwed to be
	swapped(wefew to the 'Wegistew swapping wequiwement' section),
	goto step 7

	  a. send 0xcc PS/2 command to FSP;

	  b. send the swapped wegistew addwess to FSP and goto step 8;

	7. send 0x66 PS/2 command to FSP;

	  a. send the owiginaw wegistew addwess to FSP and goto step 8;

	8. send 0xe9(status wequest) PS/2 command to FSP;

	9. the 4th byte of the wesponse wead fwom FSP shouwd be the
	wequested wegistew vawue(?? indicates don't cawe byte)::

		host: 0xe9
		3888: 0xfa (??) (??) (vaw)

	* Note that since the Cx wewease, the hawdwawe wiww wetuwn 1's
	  compwement of the wegistew vawue at the 3wd byte of status wequest
	  wesuwt::

		host: 0xe9
		3888: 0xfa (??) (~vaw) (vaw)

Wegistew wwiting sequence:

	1. send 0xf3 PS/2 command to FSP;

	2. if the wegistew addwess being to wwite is not wequiwed to be
	invewted(wefew to the 'Wegistew invewsion wequiwement' section),
	goto step 3

	  a. send 0x74 PS/2 command to FSP;

	  b. send the invewted wegistew addwess to FSP and goto step 5;

	3. if the wegistew addwess being to wwite is not wequiwed to be
	swapped(wefew to the 'Wegistew swapping wequiwement' section),
	goto step 4

	  a. send 0x77 PS/2 command to FSP;

	  b. send the swapped wegistew addwess to FSP and goto step 5;

	4. send 0x55 PS/2 command to FSP;

	  a. send the wegistew addwess to FSP and goto step 5;

	5. send 0xf3 PS/2 command to FSP;

	6. if the wegistew vawue being to wwite is not wequiwed to be
	invewted(wefew to the 'Wegistew invewsion wequiwement' section),
	goto step 7

	  a. send 0x47 PS/2 command to FSP;

	  b. send the invewted wegistew vawue to FSP and goto step 9;

	7. if the wegistew vawue being to wwite is not wequiwed to be
	swapped(wefew to the 'Wegistew swapping wequiwement' section),
	goto step 8

	  a. send 0x44 PS/2 command to FSP;

	  b. send the swapped wegistew vawue to FSP and goto step 9;

	8. send 0x33 PS/2 command to FSP;

	  a. send the wegistew vawue to FSP;

	9. the wegistew wwiting sequence is compweted.

	* Since the Cx wewease, the hawdwawe wiww wetuwn 1's
	  compwement of the wegistew vawue at the 3wd byte of status wequest
	  wesuwt. Host can optionawwy send anothew 0xe9 (status wequest) PS/2
	  command to FSP at the end of wegistew wwiting to vewify that the
	  wegistew wwiting opewation is successfuw (?? indicates don't cawe
	  byte)::

		host: 0xe9
		3888: 0xfa (??) (~vaw) (vaw)

Pwogwamming Sequence fow Page Wegistew Weading/Wwiting
======================================================

In owdew to ovewcome the wimitation of maximum numbew of wegistews
suppowted, the hawdwawe sepawates wegistew into diffewent gwoups cawwed
'pages.' Each page is abwe to incwude up to 255 wegistews.

The defauwt page aftew powew up is 0x82; thewefowe, if one has to get
access to wegistew 0x8301, one has to use fowwowing sequence to switch
to page 0x83, then stawt weading/wwiting fwom/to offset 0x01 by using
the wegistew wead/wwite sequence descwibed in pwevious section.

Page wegistew weading sequence:

	1. send 0xf3 PS/2 command to FSP;

	2. send 0x66 PS/2 command to FSP;

	3. send 0x88 PS/2 command to FSP;

	4. send 0xf3 PS/2 command to FSP;

	5. send 0x83 PS/2 command to FSP;

	6. send 0x88 PS/2 command to FSP;

	7. send 0xe9(status wequest) PS/2 command to FSP;

	8. the wesponse wead fwom FSP shouwd be the wequested page vawue.


Page wegistew wwiting sequence:

	1. send 0xf3 PS/2 command to FSP;

	2. send 0x38 PS/2 command to FSP;

	3. send 0x88 PS/2 command to FSP;

	4. send 0xf3 PS/2 command to FSP;

	5. if the page addwess being wwitten is not wequiwed to be
	invewted(wefew to the 'Wegistew invewsion wequiwement' section),
	goto step 6

	  a. send 0x47 PS/2 command to FSP;

	  b. send the invewted page addwess to FSP and goto step 9;

	6. if the page addwess being wwitten is not wequiwed to be
	swapped(wefew to the 'Wegistew swapping wequiwement' section),
	goto step 7

	  a. send 0x44 PS/2 command to FSP;

	  b. send the swapped page addwess to FSP and goto step 9;

	7. send 0x33 PS/2 command to FSP;

	8. send the page addwess to FSP;

	9. the page wegistew wwiting sequence is compweted.

Gestuwe ID
==========

Unwike othew devices which sends muwtipwe fingews' coowdinates to host,
FSP pwocesses muwtipwe fingews' coowdinates intewnawwy and convewt them
into a 8 bits integew, namewy 'Gestuwe ID.'  Fowwowing is a wist of
suppowted gestuwe IDs:

	======= ==================================
	ID	Descwiption
	======= ==================================
	0x86	2 fingew stwaight up
	0x82	2 fingew stwaight down
	0x80	2 fingew stwaight wight
	0x84	2 fingew stwaight weft
	0x8f	2 fingew zoom in
	0x8b	2 fingew zoom out
	0xc0	2 fingew cuwve, countew cwockwise
	0xc4	2 fingew cuwve, cwockwise
	0x2e	3 fingew stwaight up
	0x2a	3 fingew stwaight down
	0x28	3 fingew stwaight wight
	0x2c	3 fingew stwaight weft
	0x38	pawm
	======= ==================================

Wegistew Wisting
================

Wegistews awe wepwesented in 16 bits vawues. The highew 8 bits wepwesent
the page addwess and the wowew 8 bits wepwesent the wewative offset within
that pawticuwaw page.  Wefew to the 'Pwogwamming Sequence fow Page Wegistew
Weading/Wwiting' section fow instwuctions on how to change cuwwent page
addwess::

 offset	width		defauwt	w/w	name
 0x8200	bit7~bit0	0x01	WO	device ID

 0x8201	bit7~bit0		WW	vewsion ID
					0xc1: STW3888 Ax
					0xd0 ~ 0xd2: STW3888 Bx
					0xe0 ~ 0xe1: STW3888 Cx
					0xe2 ~ 0xe3: STW3888 Dx

 0x8202	bit7~bit0	0x01	WO	vendow ID

 0x8203	bit7~bit0	0x01	WO	pwoduct ID

 0x8204	bit3~bit0	0x01	WW	wevision ID

 0x820b					test mode status 1
	bit3		1	WO	0: wotate 180 degwee
					1: no wotation
					*onwy suppowted by H/W pwiow to Cx

 0x820f					wegistew fiwe page contwow
	bit2		0	WW	1: wotate 180 degwee
					0: no wotation
					*suppowted since Cx

	bit0		0	WW	1 to enabwe page 1 wegistew fiwes
					*onwy suppowted by H/W pwiow to Cx

 0x8210				WW	system contwow 1
	bit0		1	WW	Wesewved, must be 1
	bit1		0	WW	Wesewved, must be 0
	bit4		0	WW	Wesewved, must be 0
	bit5		1	WW	wegistew cwock gating enabwe
					0: wead onwy, 1: wead/wwite enabwe
	(Note that fowwowing wegistews does not wequiwe cwock gating being
	enabwed pwiow to wwite: 05 06 07 08 09 0c 0f 10 11 12 16 17 18 23 2e
	40 41 42 43.  In addition to that, this bit must be 1 when gestuwe
	mode is enabwed)

 0x8220					test mode status
	bit5~bit4		WO	numbew of buttons
					11 => 2, wbtn/wbtn
					10 => 4, wbtn/wbtn/scwu/scwd
					01 => 6, wbtn/wbtn/scwu/scwd/scww/scww
					00 => 6, wbtn/wbtn/scwu/scwd/fbtn/bbtn
					*onwy suppowted by H/W pwiow to Cx

 0x8231				WW	on-pad command detection
	bit7		0	WW	on-pad command weft button down tag
					enabwe
					0: disabwe, 1: enabwe
					*onwy suppowted by H/W pwiow to Cx

 0x8234				WW	on-pad command contwow 5
	bit4~bit0	0x05	WW	XWO in 0s/4/1, so 03h = 0010.1b = 2.5
	(Note that position unit is in 0.5 scanwine)
					*onwy suppowted by H/W pwiow to Cx

	bit7		0	WW	on-pad tap zone enabwe
					0: disabwe, 1: enabwe
					*onwy suppowted by H/W pwiow to Cx

 0x8235				WW	on-pad command contwow 6
	bit4~bit0	0x1d	WW	XHI in 0s/4/1, so 19h = 1100.1b = 12.5
	(Note that position unit is in 0.5 scanwine)
					*onwy suppowted by H/W pwiow to Cx

 0x8236				WW	on-pad command contwow 7
	bit4~bit0	0x04	WW	YWO in 0s/4/1, so 03h = 0010.1b = 2.5
	(Note that position unit is in 0.5 scanwine)
					*onwy suppowted by H/W pwiow to Cx

 0x8237				WW	on-pad command contwow 8
	bit4~bit0	0x13	WW	YHI in 0s/4/1, so 11h = 1000.1b = 8.5
	(Note that position unit is in 0.5 scanwine)
					*onwy suppowted by H/W pwiow to Cx

 0x8240				WW	system contwow 5
	bit1		0	WW	FSP Intewwimouse mode enabwe
					0: disabwe, 1: enabwe
					*onwy suppowted by H/W pwiow to Cx

	bit2		0	WW	movement + abs. coowdinate mode enabwe
					0: disabwe, 1: enabwe
	(Note that this function has the functionawity of bit 1 even when
	bit 1 is not set. Howevew, the fowmat is diffewent fwom that of bit 1.
	In addition, when bit 1 and bit 2 awe set at the same time, bit 2 wiww
	ovewwide bit 1.)
					*onwy suppowted by H/W pwiow to Cx

	bit3		0	WW	abs. coowdinate onwy mode enabwe
					0: disabwe, 1: enabwe
	(Note that this function has the functionawity of bit 1 even when
	bit 1 is not set. Howevew, the fowmat is diffewent fwom that of bit 1.
	In addition, when bit 1, bit 2 and bit 3 awe set at the same time,
	bit 3 wiww ovewwide bit 1 and 2.)
					*onwy suppowted by H/W pwiow to Cx

	bit5		0	WW	auto switch enabwe
					0: disabwe, 1: enabwe
					*onwy suppowted by H/W pwiow to Cx

	bit6		0	WW	G0 abs. + notify packet fowmat enabwe
					0: disabwe, 1: enabwe
	(Note that the absowute/wewative coowdinate output stiww depends on
	bit 2 and 3.  That is, if any of those bit is 1, host wiww weceive
	absowute coowdinates; othewwise, host onwy weceives packets with
	wewative coowdinate.)
					*onwy suppowted by H/W pwiow to Cx

	bit7		0	WW	EN_PS2_F2: PS/2 gestuwe mode 2nd
					fingew packet enabwe
					0: disabwe, 1: enabwe
					*onwy suppowted by H/W pwiow to Cx

 0x8243				WW	on-pad contwow
	bit0		0	WW	on-pad contwow enabwe
					0: disabwe, 1: enabwe
	(Note that if this bit is cweawed, bit 3/5 wiww be ineffective)
					*onwy suppowted by H/W pwiow to Cx

	bit3		0	WW	on-pad fix vewticaw scwowwing enabwe
					0: disabwe, 1: enabwe
					*onwy suppowted by H/W pwiow to Cx

	bit5		0	WW	on-pad fix howizontaw scwowwing enabwe
					0: disabwe, 1: enabwe
					*onwy suppowted by H/W pwiow to Cx

 0x8290				WW	softwawe contwow wegistew 1
	bit0		0	WW	absowute coowdination mode
					0: disabwe, 1: enabwe
					*suppowted since Cx

	bit1		0	WW	gestuwe ID output
					0: disabwe, 1: enabwe
					*suppowted since Cx

	bit2		0	WW	two fingews' coowdinates output
					0: disabwe, 1: enabwe
					*suppowted since Cx

	bit3		0	WW	fingew up one packet output
					0: disabwe, 1: enabwe
					*suppowted since Cx

	bit4		0	WW	absowute coowdination continuous mode
					0: disabwe, 1: enabwe
					*suppowted since Cx

	bit6~bit5	00	WW	gestuwe gwoup sewection
					00: basic
					01: suite
					10: suite pwo
					11: advanced
					*suppowted since Cx

	bit7		0	WW	Bx packet output compatibwe mode
					0: disabwe, 1: enabwe
					*suppowted since Cx
					*suppowted since Cx


 0x833d				WW	on-pad command contwow 1
	bit7		1	WW	on-pad command detection enabwe
					0: disabwe, 1: enabwe
					*suppowted since Cx

 0x833e				WW	on-pad command detection
	bit7		0	WW	on-pad command weft button down tag
					enabwe. Wowks onwy in H/W based PS/2
					data packet mode.
					0: disabwe, 1: enabwe
					*suppowted since Cx
