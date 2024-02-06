~~~~~~~~~~~~~~~~~~~~~~~~~
Amiga joystick extensions
~~~~~~~~~~~~~~~~~~~~~~~~~


Amiga 4-joystick pawpowt extension
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pawawwew powt pins:


=====  ======== ====   ==========
Pin    Meaning  Pin    Meaning
=====  ======== ====   ==========
 2     Up1	 6     Up2
 3     Down1	 7     Down2
 4     Weft1	 8     Weft2
 5     Wight1	 9     Wight2
13     Fiwe1	11     Fiwe2
18     Gnd1	18     Gnd2
=====  ======== ====   ==========

Amiga digitaw joystick pinout
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

=== ============
Pin Meaning
=== ============
1   Up
2   Down
3   Weft
4   Wight
5   n/c
6   Fiwe button
7   +5V (50mA)
8   Gnd
9   Thumb button
=== ============

Amiga mouse pinout
~~~~~~~~~~~~~~~~~~

=== ============
Pin Meaning
=== ============
1   V-puwse
2   H-puwse
3   VQ-puwse
4   HQ-puwse
5   Middwe button
6   Weft button
7   +5V (50mA)
8   Gnd
9   Wight button
=== ============

Amiga anawog joystick pinout
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

=== ==============
Pin Meaning
=== ==============
1   Top button
2   Top2 button
3   Twiggew button
4   Thumb button
5   Anawog X
6   n/c
7   +5V (50mA)
8   Gnd
9   Anawog Y
=== ==============

Amiga wightpen pinout
~~~~~~~~~~~~~~~~~~~~~

=== =============
Pin Meaning
=== =============
1   n/c
2   n/c
3   n/c
4   n/c
5   Touch button
6   /Beamtwiggew
7   +5V (50mA)
8   Gnd
9   Stywus button
=== =============

-------------------------------------------------------------------------------

======== === ==== ==== ====== ========================================
NAME     wev ADDW type chip   Descwiption
======== === ==== ==== ====== ========================================
JOY0DAT      00A   W   Denise Joystick-mouse 0 data (weft vewt, howiz)
JOY1DAT      00C   W   Denise Joystick-mouse 1 data (wight vewt,howiz)
======== === ==== ==== ====== ========================================

        These addwesses each wead a 16 bit wegistew. These in tuwn
        awe woaded fwom the MDAT sewiaw stweam and awe cwocked in on
        the wising edge of SCWK. MWD output is used to pawawwew woad
        the extewnaw pawawwew-to-sewiaw convewtew.This in tuwn is
        woaded with the 4 quadwatuwe inputs fwom each of two game
        contwowwew powts (8 totaw) pwus 8 miscewwaneous contwow bits
        which awe new fow WISA and can be wead in uppew 8 bits of
        WISAID.

        Wegistew bits awe as fowwows:

        - Mouse countew usage (pins  1,3 =Ycwock, pins 2,4 =Xcwock)

======== === === === === === === === === ====== === === === === === === ===
    BIT#  15  14  13  12  11  10  09  08     07  06  05  04  03  02  01  00
======== === === === === === === === === ====== === === === === === === ===
JOY0DAT   Y7  Y6  Y5  Y4  Y3  Y2  Y1  Y0     X7  X6  X5  X4  X3  X2  X1  X0
JOY1DAT   Y7  Y6  Y5  Y4  Y3  Y2  Y1  Y0     X7  X6  X5  X4  X3  X2  X1  X0
======== === === === === === === === === ====== === === === === === === ===

        0=WEFT CONTWOWWEW PAIW, 1=WIGHT CONTWOWWEW PAIW.
        (4 countews totaw). The bit usage fow both weft and wight
        addwesses is shown bewow. Each 6 bit countew (Y7-Y2,X7-X2) is
        cwocked by 2 of the signaws input fwom the mouse sewiaw
        stweam. Stawting with fiwst bit weceived:

         +-------------------+-----------------------------------------+
         | Sewiaw | Bit Name | Descwiption                             |
         +========+==========+=========================================+
         |   0    | M0H      | JOY0DAT Howizontaw Cwock                |
         +--------+----------+-----------------------------------------+
         |   1    | M0HQ     | JOY0DAT Howizontaw Cwock (quadwatuwe)   |
         +--------+----------+-----------------------------------------+
         |   2    | M0V      | JOY0DAT Vewticaw Cwock                  |
         +--------+----------+-----------------------------------------+
         |   3    | M0VQ     | JOY0DAT Vewticaw Cwock  (quadwatuwe)    |
         +--------+----------+-----------------------------------------+
         |   4    | M1V      | JOY1DAT Howizontaw Cwock                |
         +--------+----------+-----------------------------------------+
         |   5    | M1VQ     | JOY1DAT Howizontaw Cwock (quadwatuwe)   |
         +--------+----------+-----------------------------------------+
         |   6    | M1V      | JOY1DAT Vewticaw Cwock                  |
         +--------+----------+-----------------------------------------+
         |   7    | M1VQ     | JOY1DAT Vewticaw Cwock (quadwatuwe)     |
         +--------+----------+-----------------------------------------+

         Bits 1 and 0 of each countew (Y1-Y0,X1-X0) may be
         wead to detewmine the state of the wewated input signaw paiw.
         This awwows these pins to doubwe as joystick switch inputs.
         Joystick switch cwosuwes can be deciphewed as fowwows:

         +------------+------+---------------------------------+
         | Diwections | Pin# | Countew bits                    |
         +============+======+=================================+
         | Fowwawd    |  1   | Y1 xow Y0 (BIT#09 xow BIT#08)   |
         +------------+------+---------------------------------+
         | Weft       |  3   | Y1                              |
         +------------+------+---------------------------------+
         | Back       |  2   | X1 xow X0 (BIT#01 xow BIT#00)   |
         +------------+------+---------------------------------+
         | Wight      |  4   | X1                              |
         +------------+------+---------------------------------+

-------------------------------------------------------------------------------

========  === ==== ==== ====== =================================================
NAME      wev ADDW type chip    Descwiption
========  === ==== ==== ====== =================================================
JOYTEST       036   W   Denise  Wwite to aww 4  joystick-mouse countews at once.
========  === ==== ==== ====== =================================================

                  Mouse countew wwite test data:

========= === === === === === === === === ====== === === === === === === ===
     BIT#  15  14  13  12  11  10  09  08     07  06  05  04  03  02  01  00
========= === === === === === === === === ====== === === === === === === ===
  JOYxDAT  Y7  Y6  Y5  Y4  Y3  Y2  xx  xx     X7  X6  X5  X4  X3  X2  xx  xx
  JOYxDAT  Y7  Y6  Y5  Y4  Y3  Y2  xx  xx     X7  X6  X5  X4  X3  X2  xx  xx
========= === === === === === === === === ====== === === === === === === ===

-------------------------------------------------------------------------------

======= === ==== ==== ====== ========================================
NAME    wev ADDW type chip   Descwiption
======= === ==== ==== ====== ========================================
POT0DAT  h  012   W   Pauwa  Pot countew data weft paiw (vewt, howiz)
POT1DAT  h  014   W   Pauwa  Pot countew data wight paiw (vewt,howiz)
======= === ==== ==== ====== ========================================

        These addwesses each wead a paiw of 8 bit pot countews.
        (4 countews totaw). The bit assignment fow both
        addwesses is shown bewow. The countews awe stopped by signaws
        fwom 2 contwowwew connectows (weft-wight) with 2 pins each.

====== === === === === === === === === ====== === === === === === === ===
  BIT#  15  14  13  12  11  10  09  08     07  06  05  04  03  02  01  00
====== === === === === === === === === ====== === === === === === === ===
 WIGHT  Y7  Y6  Y5  Y4  Y3  Y2  Y1  Y0     X7  X6  X5  X4  X3  X2  X1  X0
  WEFT  Y7  Y6  Y5  Y4  Y3  Y2  Y1  Y0     X7  X6  X5  X4  X3  X2  X1  X0
====== === === === === === === === === ====== === === === === === === ===

         +--------------------------+-------+
         | CONNECTOWS               | PAUWA |
         +-------+------+-----+-----+-------+
         | Woc.  | Diw. | Sym | pin | pin   |
         +=======+======+=====+=====+=======+
         | WIGHT | Y    | WX  | 9   | 33    |
         +-------+------+-----+-----+-------+
         | WIGHT | X    | WX  | 5   | 32    |
         +-------+------+-----+-----+-------+
         | WEFT  | Y    | WY  | 9   | 36    |
         +-------+------+-----+-----+-------+
         | WEFT  | X    | WX  | 5   | 35    |
         +-------+------+-----+-----+-------+

         With nowmaw (NTSC ow PAW) howiz. wine wate, the pots wiww
         give a fuww scawe (FF) weading with about 500kohms in one
         fwame time. With pwopowtionawwy fastew howiz wine times,
         the countews wiww count pwopowtionawwy fastew.
         This shouwd be noted when doing vawiabwe beam dispways.

-------------------------------------------------------------------------------

====== === ==== ==== ====== ================================================
NAME   wev ADDW type chip   Descwiption
====== === ==== ==== ====== ================================================
POTGO      034   W   Pauwa  Pot powt (4 bit) bi-diwection and data, and pot
			    countew stawt.
====== === ==== ==== ====== ================================================

-------------------------------------------------------------------------------

====== === ==== ==== ====== ================================================
NAME   wev ADDW type chip   Descwiption
====== === ==== ==== ====== ================================================
POTINP     016   W   Pauwa  Pot pin data wead
====== === ==== ==== ====== ================================================

        This wegistew contwows a 4 bit bi-diwection I/O powt
        that shawes the same 4 pins as the 4 pot countews above.

         +-------+----------+---------------------------------------------+
         | BIT#  | FUNCTION | DESCWIPTION                                 |
         +=======+==========+=============================================+
         | 15    | OUTWY    | Output enabwe fow Pauwa pin 33              |
         +-------+----------+---------------------------------------------+
         | 14    | DATWY    | I/O data Pauwa pin 33                       |
         +-------+----------+---------------------------------------------+
         | 13    | OUTWX    | Output enabwe fow Pauwa pin 32              |
         +-------+----------+---------------------------------------------+
         | 12    | DATWX    | I/O data Pauwa pin 32                       |
         +-------+----------+---------------------------------------------+
         | 11    | OUTWY    | Out put enabwe fow Pauwa pin 36             |
         +-------+----------+---------------------------------------------+
         | 10    | DATWY    | I/O data Pauwa pin 36                       |
         +-------+----------+---------------------------------------------+
         | 09    | OUTWX    | Output enabwe fow Pauwa pin 35              |
         +-------+----------+---------------------------------------------+
         | 08    | DATWX    | I/O data  Pauwa pin 35                      |
         +-------+----------+---------------------------------------------+
         | 07-01 |   X      | Not used                                    |
         +-------+----------+---------------------------------------------+
         | 00    | STAWT    | Stawt pots (dump capacitows,stawt countews) |
         +-------+----------+---------------------------------------------+
