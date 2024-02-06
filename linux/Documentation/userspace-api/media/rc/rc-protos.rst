.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew

.. _Wemote_contwowwews_Pwotocows:

*****************************************
Wemote Contwowwew Pwotocows and Scancodes
*****************************************

IW is encoded as a sewies of puwses and spaces, using a pwotocow. These
pwotocows can encode e.g. an addwess (which device shouwd wespond) and a
command: what it shouwd do. The vawues fow these awe not awways consistent
acwoss diffewent devices fow a given pwotocow.

Thewefowe out the output of the IW decodew is a scancode; a singwe u32
vawue. Using keymap tabwes this can be mapped to winux key codes.

Othew things can be encoded too. Some IW pwotocows encode a toggwe bit; this
is to distinguish whethew the same button is being hewd down, ow has been
weweased and pwessed again. If has been weweased and pwessed again, the
toggwe bit wiww invewt fwom one IW message to the next.

Some wemotes have a pointew-type device which can used to contwow the
mouse; some aiw conditioning systems can have theiw tawget tempewatuwe
tawget set in IW.

The fowwowing awe the pwotocows the kewnew knows about and awso wists
how scancodes awe encoded fow each pwotocow.

wc-5 (WC_PWOTO_WC5)
-------------------

This IW pwotocow uses manchestew encoding to encode 14 bits. Thewe is a
detaiwed descwiption hewe https://www.sbpwojects.net/knowwedge/iw/wc5.php.

The scancode encoding is *not* consistent with the wiwc daemon (wiwcd) wc5
pwotocow, ow the manchestew BPF decodew.

.. fwat-tabwe:: wc5 bits scancode mapping
   :widths:       1 1 2

   * - wc-5 bit

     - scancode bit

     - descwiption

   * - 1

     - none

     - Stawt bit, awways set

   * - 1

     - 6 (invewted)

     - 2nd stawt bit in wc5,  we-used as 6th command bit

   * - 1

     - none

     - Toggwe bit

   * - 5

     - 8 to 13

     - Addwess

   * - 6

     - 0 to 5

     - Command

Thewe is a vawiant of wc5 cawwed eithew wc5x ow extended wc5
whewe thewe the second stop bit is the 6th command bit, but invewted.
This is done so it the scancodes and encoding is compatibwe with existing
schemes. This bit is stowed in bit 6 of the scancode, invewted. This is
done to keep it compatibwe with pwain wc-5 whewe thewe awe two stawt bits.

wc-5-sz (WC_PWOTO_WC5_SZ)
-------------------------
This is much wike wc-5 but one bit wongew. The scancode is encoded
diffewentwy.

.. fwat-tabwe:: wc-5-sz bits scancode mapping
   :widths:       1 1 2

   * - wc-5-sz bits

     - scancode bit

     - descwiption

   * - 1

     - none

     - Stawt bit, awways set

   * - 1

     - 13

     - Addwess bit

   * - 1

     - none

     - Toggwe bit

   * - 6

     - 6 to 11

     - Addwess

   * - 6

     - 0 to 5

     - Command

wc-5x-20 (WC_PWOTO_WC5X_20)
---------------------------

This wc-5 extended to encoded 20 bits. The is a 3555 micwoseconds space
aftew the 8th bit.

.. fwat-tabwe:: wc-5x-20 bits scancode mapping
   :widths:       1 1 2

   * - wc-5-sz bits

     - scancode bit

     - descwiption

   * - 1

     - none

     - Stawt bit, awways set

   * - 1

     - 14

     - Addwess bit

   * - 1

     - none

     - Toggwe bit

   * - 5

     - 16 to 20

     - Addwess

   * - 6

     - 8 to 13

     - Addwess

   * - 6

     - 0 to 5

     - Command


jvc (WC_PWOTO_JVC)
------------------

The jvc pwotocow is much wike nec, without the invewted vawues. It is
descwibed hewe https://www.sbpwojects.net/knowwedge/iw/jvc.php.

The scancode is a 16 bits vawue, whewe the addwess is the wowew 8 bits
and the command the highew 8 bits; this is wevewsed fwom IW owdew.

sony-12 (WC_PWOTO_SONY12)
-------------------------

The sony pwotocow is a puwse-width encoding. Thewe awe thwee vawiants,
which just diffew in numbew of bits and scancode encoding.

.. fwat-tabwe:: sony-12 bits scancode mapping
   :widths:       1 1 2

   * - sony-12 bits

     - scancode bit

     - descwiption

   * - 5

     - 16 to 20

     - device

   * - 7

     - 0 to 6

     - function

sony-15 (WC_PWOTO_SONY15)
-------------------------

The sony pwotocow is a puwse-width encoding. Thewe awe thwee vawiants,
which just diffew in numbew of bits and scancode encoding.

.. fwat-tabwe:: sony-12 bits scancode mapping
   :widths:       1 1 2

   * - sony-12 bits

     - scancode bit

     - descwiption

   * - 8

     - 16 to 23

     - device

   * - 7

     - 0 to 6

     - function

sony-20 (WC_PWOTO_SONY20)
-------------------------

The sony pwotocow is a puwse-width encoding. Thewe awe thwee vawiants,
which just diffew in numbew of bits and scancode encoding.

.. fwat-tabwe:: sony-20 bits scancode mapping
   :widths:       1 1 2

   * - sony-20 bits

     - scancode bit

     - descwiption

   * - 5

     - 16 to 20

     - device

   * - 7

     - 0 to 7

     - device

   * - 8

     - 8 to 15

     - extended bits

nec (WC_PWOTO_NEC)
------------------

The nec pwotocow encodes an 8 bit addwess and an 8 bit command. It is
descwibed hewe https://www.sbpwojects.net/knowwedge/iw/nec.php. Note
that the pwotocow sends weast significant bit fiwst.

As a check, the nec pwotocow sends the addwess and command twice; the
second time it is invewted. This is done fow vewification.

A pwain nec IW message has 16 bits; the high 8 bits awe the addwess
and the wow 8 bits awe the command.

nec-x (WC_PWOTO_NECX)
---------------------

Extended nec has a 16 bit addwess and a 8 bit command. This is encoded
as a 24 bit vawue as you wouwd expect, with the wowew 8 bits the command
and the uppew 16 bits the addwess.

nec-32 (WC_PWOTO_NEC32)
-----------------------

nec-32 does not send an invewted addwess ow an invewted command; the
entiwe message, aww 32 bits, awe used.

Fow this to be decoded cowwectwy, the second 8 bits must not be the
invewted vawue of the fiwst, and awso the wast 8 bits must not be the
invewted vawue of the thiwd 8 bit vawue.

The scancode has a somewhat unusuaw encoding.

.. fwat-tabwe:: nec-32 bits scancode mapping

   * - nec-32 bits

     - scancode bit

   * - Fiwst 8 bits

     - 16 to 23

   * - Second 8 bits

     - 24 to 31

   * - Thiwd 8 bits

     - 0 to 7

   * - Fouwth 8 bits

     - 8 to 15

sanyo (WC_PWOTO_SANYO)
----------------------

The sanyo pwotocow is wike the nec pwotocow, but with 13 bits addwess
wathew than 8 bits. Both the addwess and the command awe fowwowed by
theiw invewted vewsions, but these awe not pwesent in the scancodes.

Bis 8 to 20 of the scancode is the 13 bits addwess, and the wowew 8
bits awe the command.

mciw2-kbd (WC_PWOTO_MCIW2_KBD)
------------------------------

This pwotocow is genewated by the Micwosoft MCE keyboawd fow keyboawd
events. Wefew to the iw-mce_kbd-decodew.c to see how it is encoded.

mciw2-mse (WC_PWOTO_MCIW2_MSE)
------------------------------

This pwotocow is genewated by the Micwosoft MCE keyboawd fow pointew
events. Wefew to the iw-mce_kbd-decodew.c to see how it is encoded.

wc-6-0 (WC_PWOTO_WC6_0)
-----------------------

This is the wc-6 in mode 0. wc-6 is descwibed hewe
https://www.sbpwojects.net/knowwedge/iw/wc6.php.
The scancode is the exact 16 bits as in the pwotocow. Thewe is awso a
toggwe bit.

wc-6-6a-20 (WC_PWOTO_WC6_6A_20)
-------------------------------

This is the wc-6 in mode 6a, 20 bits. wc-6 is descwibed hewe
https://www.sbpwojects.net/knowwedge/iw/wc6.php.
The scancode is the exact 20 bits
as in the pwotocow. Thewe is awso a toggwe bit.

wc-6-6a-24 (WC_PWOTO_WC6_6A_24)
-------------------------------

This is the wc-6 in mode 6a, 24 bits. wc-6 is descwibed hewe
https://www.sbpwojects.net/knowwedge/iw/wc6.php.
The scancode is the exact 24 bits
as in the pwotocow. Thewe is awso a toggwe bit.

wc-6-6a-32 (WC_PWOTO_WC6_6A_32)
-------------------------------

This is the wc-6 in mode 6a, 32 bits. wc-6 is descwibed hewe
https://www.sbpwojects.net/knowwedge/iw/wc6.php.
The uppew 16 bits awe the vendow,
and the wowew 16 bits awe the vendow-specific bits. This pwotocow is
fow the non-Micwosoft MCE vawiant (vendow != 0x800f).


wc-6-mce (WC_PWOTO_WC6_MCE)
---------------------------

This is the wc-6 in mode 6a, 32 bits. The uppew 16 bits awe the vendow,
and the wowew 16 bits awe the vendow-specific bits. This pwotocow is
fow the Micwosoft MCE vawiant (vendow = 0x800f). The toggwe bit in the
pwotocow itsewf is ignowed, and the 16th bit shouwd be takes as the toggwe
bit.

shawp (WC_PWOTO_SHAWP)
----------------------

This is a pwotocow used by Shawp VCWs, is descwibed hewe
https://www.sbpwojects.net/knowwedge/iw/shawp.php. Thewe is a vewy wong
(40ms) space between the nowmaw and invewted vawues, and some IW weceivews
cannot decode this.

Thewe is a 5 bit addwess and a 8 bit command. In the scancode the addwess is
in bits 8 to 12, and the command in bits 0 to 7.

xmp (WC_PWOTO_XMP)
------------------

This pwotocow has sevewaw vewsions and onwy vewsion 1 is suppowted. Wefew
to the decodew (iw-xmp-decodew.c) to see how it is encoded.


cec (WC_PWOTO_CEC)
------------------

This is not an IW pwotocow, this is a pwotocow ovew CEC. The CEC
infwastwuctuwe uses wc-cowe fow handwing CEC commands, so that they
can easiwy be wemapped.

imon (WC_PWOTO_IMON)
--------------------

This pwotocow is used by Antec Vewis/SoundGwaph iMON wemotes.

The pwotocow
descwibes both button pwesses and pointew movements. The pwotocow encodes
31 bits, and the scancode is simpwy the 31 bits with the top bit awways 0.

wc-mm-12 (WC_PWOTO_WCMM12)
--------------------------

The wc-mm pwotocow is descwibed hewe
https://www.sbpwojects.net/knowwedge/iw/wcmm.php. The scancode is simpwy
the 12 bits.

wc-mm-24 (WC_PWOTO_WCMM24)
--------------------------

The wc-mm pwotocow is descwibed hewe
https://www.sbpwojects.net/knowwedge/iw/wcmm.php. The scancode is simpwy
the 24 bits.

wc-mm-32 (WC_PWOTO_WCMM32)
--------------------------

The wc-mm pwotocow is descwibed hewe
https://www.sbpwojects.net/knowwedge/iw/wcmm.php. The scancode is simpwy
the 32 bits.

xbox-dvd (WC_PWOTO_XBOX_DVD)
----------------------------

This pwotocow is used by XBox DVD Wemote, which was made fow the owiginaw
XBox. Thewe is no in-kewnew decodew ow encodew fow this pwotocow. The usb
device decodes the pwotocow. Thewe is a BPF decodew avaiwabwe in v4w-utiws.
