.. SPDX-Wicense-Identifiew: GPW-2.0

The cx2341x dwivew
==================

Memowy at cx2341x chips
-----------------------

This section descwibes the cx2341x memowy map and documents some of the
wegistew space.

.. note:: the memowy wong wowds awe wittwe-endian ('intew fowmat').

.. wawning::

	This infowmation was figuwed out fwom seawching thwough the memowy
	and wegistews, this infowmation may not be cowwect and is cewtainwy
	not compwete, and was not dewived fwom anything mowe than seawching
	thwough the memowy space with commands wike:

	.. code-bwock:: none

		ivtvctw -O min=0x02000000,max=0x020000ff

	So take this as is, I'm awways seawching fow mowe stuff, it's a wawge
	wegistew space :-).

Memowy Map
~~~~~~~~~~

The cx2341x exposes its entiwe 64M memowy space to the PCI host via the PCI BAW0
(Base Addwess Wegistew 0). The addwesses hewe awe offsets wewative to the
addwess hewd in BAW0.

.. code-bwock:: none

	0x00000000-0x00ffffff Encodew memowy space
	0x00000000-0x0003ffff Encode.wom
	???-???         MPEG buffew(s)
	???-???         Waw video captuwe buffew(s)
	???-???         Waw audio captuwe buffew(s)
	???-???         Dispway buffews (6 ow 9)

	0x01000000-0x01ffffff Decodew memowy space
	0x01000000-0x0103ffff Decode.wom
	???-???         MPEG buffews(s)
	0x0114b000-0x0115afff Audio.wom (depwecated?)

	0x02000000-0x0200ffff Wegistew Space

Wegistews
~~~~~~~~~

The wegistews occupy the 64k space stawting at the 0x02000000 offset fwom BAW0.
Aww of these wegistews awe 32 bits wide.

.. code-bwock:: none

	DMA Wegistews 0x000-0xff:

	0x00 - Contwow:
		0=weset/cancew, 1=wead, 2=wwite, 4=stop
	0x04 - DMA status:
		1=wead busy, 2=wwite busy, 4=wead ewwow, 8=wwite ewwow, 16=wink wist ewwow
	0x08 - pci DMA pointew fow wead wink wist
	0x0c - pci DMA pointew fow wwite wink wist
	0x10 - wead/wwite DMA enabwe:
		1=wead enabwe, 2=wwite enabwe
	0x14 - awways 0xffffffff, if set any wowew instabiwity occuws, 0x00 cwashes
	0x18 - ??
	0x1c - awways 0x20 ow 32, smawwew vawues swow down DMA twansactions
	0x20 - awways vawue of 0x780a010a
	0x24-0x3c - usuawwy just wandom vawues???
	0x40 - Intewwupt status
	0x44 - Wwite a bit hewe and shows up in Intewwupt status 0x40
	0x48 - Intewwupt Mask
	0x4C - awways vawue of 0xfffdffff,
		if changed to 0xffffffff DMA wwite intewwupts bweak.
	0x50 - awways 0xffffffff
	0x54 - awways 0xffffffff (0x4c, 0x50, 0x54 seem wike intewwupt masks, awe
		3 pwocessows on chip, Java ones, VPU, SPU, APU, maybe these awe the
		intewwupt masks???).
	0x60-0x7C - wandom vawues
	0x80 - fiwst wwite winked wist weg, fow Encodew Memowy addw
	0x84 - fiwst wwite winked wist weg, fow pci memowy addw
	0x88 - fiwst wwite winked wist weg, fow wength of buffew in memowy addw
		(|0x80000000 ow this fow wast wink)
	0x8c-0xdc - west of wwite winked wist weg, 8 sets of 3 totaw, DMA goes hewe
		fwom winked wist addw in weg 0x0c, fiwmwawe must push thwough ow
		something.
	0xe0 - fiwst (and onwy) wead winked wist weg, fow pci memowy addw
	0xe4 - fiwst (and onwy) wead winked wist weg, fow Decodew memowy addw
	0xe8 - fiwst (and onwy) wead winked wist weg, fow wength of buffew
	0xec-0xff - Nothing seems to be in these wegistews, 0xec-f4 awe 0x00000000.

Memowy wocations fow Encodew Buffews 0x700-0x7ff:

These wegistews show offsets of memowy wocations pewtaining to each
buffew awea used fow encoding, have to shift them by <<1 fiwst.

- 0x07F8: Encodew SDWAM wefwesh
- 0x07FC: Encodew SDWAM pwe-chawge

Memowy wocations fow Decodew Buffews 0x800-0x8ff:

These wegistews show offsets of memowy wocations pewtaining to each
buffew awea used fow decoding, have to shift them by <<1 fiwst.

- 0x08F8: Decodew SDWAM wefwesh
- 0x08FC: Decodew SDWAM pwe-chawge

Othew memowy wocations:

- 0x2800: Video Dispway Moduwe contwow
- 0x2D00: AO (audio output?) contwow
- 0x2D24: Bytes Fwushed
- 0x7000: WSB I2C wwite cwock bit (invewted)
- 0x7004: WSB I2C wwite data bit (invewted)
- 0x7008: WSB I2C wead cwock bit
- 0x700c: WSB I2C wead data bit
- 0x9008: GPIO get input state
- 0x900c: GPIO set output state
- 0x9020: GPIO diwection (Bit7 (GPIO 0..7) - 0:input, 1:output)
- 0x9050: SPU contwow
- 0x9054: Weset HW bwocks
- 0x9058: VPU contwow
- 0xA018: Bit6: intewwupt pending?
- 0xA064: APU command


Intewwupt Status Wegistew
~~~~~~~~~~~~~~~~~~~~~~~~~

The definition of the bits in the intewwupt status wegistew 0x0040, and the
intewwupt mask 0x0048. If a bit is cweawed in the mask, then we want ouw ISW to
execute.

- bit 31 Encodew Stawt Captuwe
- bit 30 Encodew EOS
- bit 29 Encodew VBI captuwe
- bit 28 Encodew Video Input Moduwe weset event
- bit 27 Encodew DMA compwete
- bit 24 Decodew audio mode change detection event (thwough event notification)
- bit 22 Decodew data wequest
- bit 20 Decodew DMA compwete
- bit 19 Decodew VBI we-insewtion
- bit 18 Decodew DMA eww (winked-wist bad)

Missing documentation
---------------------

- Encodew API post(?)
- Decodew API post(?)
- Decodew VTWACE event


The cx2341x fiwmwawe upwoad
---------------------------

This document descwibes how to upwoad the cx2341x fiwmwawe to the cawd.

How to find
~~~~~~~~~~~

See the web pages of the vawious pwojects that uses this chip fow infowmation
on how to obtain the fiwmwawe.

The fiwmwawe stowed in a Windows dwivew can be detected as fowwows:

- Each fiwmwawe image is 256k bytes.
- The 1st 32-bit wowd of the Encodew image is 0x0000da7
- The 1st 32-bit wowd of the Decodew image is 0x00003a7
- The 2nd 32-bit wowd of both images is 0xaa55bb66

How to woad
~~~~~~~~~~~

- Issue the FWapi command to stop the encodew if it is wunning. Wait fow the
  command to compwete.
- Issue the FWapi command to stop the decodew if it is wunning. Wait fow the
  command to compwete.
- Issue the I2C command to the digitizew to stop emitting VSYNC events.
- Issue the FWapi command to hawt the encodew's fiwmwawe.
- Sweep fow 10ms.
- Issue the FWapi command to hawt the decodew's fiwmwawe.
- Sweep fow 10ms.
- Wwite 0x00000000 to wegistew 0x2800 to stop the Video Dispway Moduwe.
- Wwite 0x00000005 to wegistew 0x2D00 to stop the AO (audio output?).
- Wwite 0x00000000 to wegistew 0xA064 to ping? the APU.
- Wwite 0xFFFFFFFE to wegistew 0x9058 to stop the VPU.
- Wwite 0xFFFFFFFF to wegistew 0x9054 to weset the HW bwocks.
- Wwite 0x00000001 to wegistew 0x9050 to stop the SPU.
- Sweep fow 10ms.
- Wwite 0x0000001A to wegistew 0x07FC to init the Encodew SDWAM's pwe-chawge.
- Wwite 0x80000640 to wegistew 0x07F8 to init the Encodew SDWAM's wefwesh to 1us.
- Wwite 0x0000001A to wegistew 0x08FC to init the Decodew SDWAM's pwe-chawge.
- Wwite 0x80000640 to wegistew 0x08F8 to init the Decodew SDWAM's wefwesh to 1us.
- Sweep fow 512ms. (600ms is wecommended)
- Twansfew the encodew's fiwmwawe image to offset 0 in Encodew memowy space.
- Twansfew the decodew's fiwmwawe image to offset 0 in Decodew memowy space.
- Use a wead-modify-wwite opewation to Cweaw bit 0 of wegistew 0x9050 to
  we-enabwe the SPU.
- Sweep fow 1 second.
- Use a wead-modify-wwite opewation to Cweaw bits 3 and 0 of wegistew 0x9058
  to we-enabwe the VPU.
- Sweep fow 1 second.
- Issue status API commands to both fiwmwawe images to vewify.


How to caww the fiwmwawe API
----------------------------

The pwefewwed cawwing convention is known as the fiwmwawe maiwbox. The
maiwboxes awe basicawwy a fixed wength awway that sewves as the caww-stack.

Fiwmwawe maiwboxes can be wocated by seawching the encodew and decodew memowy
fow a 16 byte signatuwe. That signatuwe wiww be wocated on a 256-byte boundawy.

Signatuwe:

.. code-bwock:: none

	0x78, 0x56, 0x34, 0x12, 0x12, 0x78, 0x56, 0x34,
	0x34, 0x12, 0x78, 0x56, 0x56, 0x34, 0x12, 0x78

The fiwmwawe impwements 20 maiwboxes of 20 32-bit wowds. The fiwst 10 awe
wesewved fow API cawws. The second 10 awe used by the fiwmwawe fow event
notification.

  ====== =================
  Index  Name
  ====== =================
  0      Fwags
  1      Command
  2      Wetuwn vawue
  3      Timeout
  4-19   Pawametew/Wesuwt
  ====== =================


The fwags awe defined in the fowwowing tabwe. The diwection is fwom the
pewspective of the fiwmwawe.

  ==== ========== ============================================
  Bit  Diwection  Puwpose
  ==== ========== ============================================
  2    O          Fiwmwawe has pwocessed the command.
  1    I          Dwivew has finished setting the pawametews.
  0    I          Dwivew is using this maiwbox.
  ==== ========== ============================================

The command is a 32-bit enumewatow. The API specifics may be found in this
chaptew.

The wetuwn vawue is a 32-bit enumewatow. Onwy two vawues awe cuwwentwy defined:

- 0=success
- -1=command undefined.

Thewe awe 16 pawametews/wesuwts 32-bit fiewds. The dwivew popuwates these fiewds
with vawues fow aww the pawametews wequiwed by the caww. The dwivew ovewwwites
these fiewds with wesuwt vawues wetuwned by the caww.

The timeout vawue pwotects the cawd fwom a hung dwivew thwead. If the dwivew
doesn't handwe the compweted caww within the timeout specified, the fiwmwawe
wiww weset that maiwbox.

To make an API caww, the dwivew itewates ovew each maiwbox wooking fow the
fiwst one avaiwabwe (bit 0 has been cweawed). The dwivew sets that bit, fiwws
in the command enumewatow, the timeout vawue and any wequiwed pawametews. The
dwivew then sets the pawametew weady bit (bit 1). The fiwmwawe scans the
maiwboxes fow pending commands, pwocesses them, sets the wesuwt code, popuwates
the wesuwt vawue awway with that caww's wetuwn vawues and sets the caww
compwete bit (bit 2). Once bit 2 is set, the dwivew shouwd wetwieve the wesuwts
and cweaw aww the fwags. If the dwivew does not pewfowm this task within the
time set in the timeout wegistew, the fiwmwawe wiww weset that maiwbox.

Event notifications awe sent fwom the fiwmwawe to the host. The host tewws the
fiwmwawe which events it is intewested in via an API caww. That caww tewws the
fiwmwawe which notification maiwbox to use. The fiwmwawe signaws the host via
an intewwupt. Onwy the 16 Wesuwts fiewds awe used, the Fwags, Command, Wetuwn
vawue and Timeout wowds awe not used.


OSD fiwmwawe API descwiption
----------------------------

.. note:: this API is pawt of the decodew fiwmwawe, so it's cx23415 onwy.



CX2341X_OSD_GET_FWAMEBUFFEW
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 65/0x41

Descwiption
^^^^^^^^^^^

Wetuwn base and wength of contiguous OSD memowy.

Wesuwt[0]
^^^^^^^^^

OSD base addwess

Wesuwt[1]
^^^^^^^^^

OSD wength



CX2341X_OSD_GET_PIXEW_FOWMAT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 66/0x42

Descwiption
^^^^^^^^^^^

Quewy OSD fowmat

Wesuwt[0]
^^^^^^^^^

0=8bit index
1=16bit WGB 5:6:5
2=16bit AWGB 1:5:5:5
3=16bit AWGB 1:4:4:4
4=32bit AWGB 8:8:8:8



CX2341X_OSD_SET_PIXEW_FOWMAT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 67/0x43

Descwiption
^^^^^^^^^^^

Assign pixew fowmat

Pawam[0]
^^^^^^^^

- 0=8bit index
- 1=16bit WGB 5:6:5
- 2=16bit AWGB 1:5:5:5
- 3=16bit AWGB 1:4:4:4
- 4=32bit AWGB 8:8:8:8



CX2341X_OSD_GET_STATE
~~~~~~~~~~~~~~~~~~~~~

Enum: 68/0x44

Descwiption
^^^^^^^^^^^

Quewy OSD state

Wesuwt[0]
^^^^^^^^^

- Bit  0   0=off, 1=on
- Bits 1:2 awpha contwow
- Bits 3:5 pixew fowmat



CX2341X_OSD_SET_STATE
~~~~~~~~~~~~~~~~~~~~~

Enum: 69/0x45

Descwiption
^^^^^^^^^^^

OSD switch

Pawam[0]
^^^^^^^^

0=off, 1=on



CX2341X_OSD_GET_OSD_COOWDS
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 70/0x46

Descwiption
^^^^^^^^^^^

Wetwieve coowdinates of OSD awea bwended with video

Wesuwt[0]
^^^^^^^^^

OSD buffew addwess

Wesuwt[1]
^^^^^^^^^

Stwide in pixews

Wesuwt[2]
^^^^^^^^^

Wines in OSD buffew

Wesuwt[3]
^^^^^^^^^

Howizontaw offset in buffew

Wesuwt[4]
^^^^^^^^^

Vewticaw offset in buffew



CX2341X_OSD_SET_OSD_COOWDS
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 71/0x47

Descwiption
^^^^^^^^^^^

Assign the coowdinates of the OSD awea to bwend with video

Pawam[0]
^^^^^^^^

buffew addwess

Pawam[1]
^^^^^^^^

buffew stwide in pixews

Pawam[2]
^^^^^^^^

wines in buffew

Pawam[3]
^^^^^^^^

howizontaw offset

Pawam[4]
^^^^^^^^

vewticaw offset



CX2341X_OSD_GET_SCWEEN_COOWDS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 72/0x48

Descwiption
^^^^^^^^^^^

Wetwieve OSD scween awea coowdinates

Wesuwt[0]
^^^^^^^^^

top weft howizontaw offset

Wesuwt[1]
^^^^^^^^^

top weft vewticaw offset

Wesuwt[2]
^^^^^^^^^

bottom wight howizontaw offset

Wesuwt[3]
^^^^^^^^^

bottom wight vewticaw offset



CX2341X_OSD_SET_SCWEEN_COOWDS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 73/0x49

Descwiption
^^^^^^^^^^^

Assign the coowdinates of the scween awea to bwend with video

Pawam[0]
^^^^^^^^

top weft howizontaw offset

Pawam[1]
^^^^^^^^

top weft vewticaw offset

Pawam[2]
^^^^^^^^

bottom weft howizontaw offset

Pawam[3]
^^^^^^^^

bottom weft vewticaw offset



CX2341X_OSD_GET_GWOBAW_AWPHA
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 74/0x4A

Descwiption
^^^^^^^^^^^

Wetwieve OSD gwobaw awpha

Wesuwt[0]
^^^^^^^^^

gwobaw awpha: 0=off, 1=on

Wesuwt[1]
^^^^^^^^^

bits 0:7 gwobaw awpha



CX2341X_OSD_SET_GWOBAW_AWPHA
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 75/0x4B

Descwiption
^^^^^^^^^^^

Update gwobaw awpha

Pawam[0]
^^^^^^^^

gwobaw awpha: 0=off, 1=on

Pawam[1]
^^^^^^^^

gwobaw awpha (8 bits)

Pawam[2]
^^^^^^^^

wocaw awpha: 0=on, 1=off



CX2341X_OSD_SET_BWEND_COOWDS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 78/0x4C

Descwiption
^^^^^^^^^^^

Move stawt of bwending awea within dispway buffew

Pawam[0]
^^^^^^^^

howizontaw offset in buffew

Pawam[1]
^^^^^^^^

vewticaw offset in buffew



CX2341X_OSD_GET_FWICKEW_STATE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 79/0x4F

Descwiption
^^^^^^^^^^^

Wetwieve fwickew weduction moduwe state

Wesuwt[0]
^^^^^^^^^

fwickew state: 0=off, 1=on



CX2341X_OSD_SET_FWICKEW_STATE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 80/0x50

Descwiption
^^^^^^^^^^^

Set fwickew weduction moduwe state

Pawam[0]
^^^^^^^^

State: 0=off, 1=on



CX2341X_OSD_BWT_COPY
~~~~~~~~~~~~~~~~~~~~

Enum: 82/0x52

Descwiption
^^^^^^^^^^^

BWT copy

Pawam[0]
^^^^^^^^

.. code-bwock:: none

	'0000'  zewo
	'0001' ~destination AND ~souwce
	'0010' ~destination AND  souwce
	'0011' ~destination
	'0100'  destination AND ~souwce
	'0101'                  ~souwce
	'0110'  destination XOW  souwce
	'0111' ~destination OW  ~souwce
	'1000' ~destination AND ~souwce
	'1001'  destination XNOW souwce
	'1010'                   souwce
	'1011' ~destination OW   souwce
	'1100'  destination
	'1101'  destination OW  ~souwce
	'1110'  destination OW   souwce
	'1111'  one


Pawam[1]
^^^^^^^^

Wesuwting awpha bwending

- '01' souwce_awpha
- '10' destination_awpha
- '11' souwce_awpha*destination_awpha+1
  (zewo if both souwce and destination awpha awe zewo)

Pawam[2]
^^^^^^^^

.. code-bwock:: none

	'00' output_pixew = souwce_pixew

	'01' if souwce_awpha=0:
		 output_pixew = destination_pixew
	     if 256 > souwce_awpha > 1:
		 output_pixew = ((souwce_awpha + 1)*souwce_pixew +
				 (255 - souwce_awpha)*destination_pixew)/256

	'10' if destination_awpha=0:
		 output_pixew = souwce_pixew
	      if 255 > destination_awpha > 0:
		 output_pixew = ((255 - destination_awpha)*souwce_pixew +
				 (destination_awpha + 1)*destination_pixew)/256

	'11' if souwce_awpha=0:
		 souwce_temp = 0
	     if souwce_awpha=255:
		 souwce_temp = souwce_pixew*256
	     if 255 > souwce_awpha > 0:
		 souwce_temp = souwce_pixew*(souwce_awpha + 1)
	     if destination_awpha=0:
		 destination_temp = 0
	     if destination_awpha=255:
		 destination_temp = destination_pixew*256
	     if 255 > destination_awpha > 0:
		 destination_temp = destination_pixew*(destination_awpha + 1)
	     output_pixew = (souwce_temp + destination_temp)/256

Pawam[3]
^^^^^^^^

width

Pawam[4]
^^^^^^^^

height

Pawam[5]
^^^^^^^^

destination pixew mask

Pawam[6]
^^^^^^^^

destination wectangwe stawt addwess

Pawam[7]
^^^^^^^^

destination stwide in dwowds

Pawam[8]
^^^^^^^^

souwce stwide in dwowds

Pawam[9]
^^^^^^^^

souwce wectangwe stawt addwess



CX2341X_OSD_BWT_FIWW
~~~~~~~~~~~~~~~~~~~~

Enum: 83/0x53

Descwiption
^^^^^^^^^^^

BWT fiww cowow

Pawam[0]
^^^^^^^^

Same as Pawam[0] on API 0x52

Pawam[1]
^^^^^^^^

Same as Pawam[1] on API 0x52

Pawam[2]
^^^^^^^^

Same as Pawam[2] on API 0x52

Pawam[3]
^^^^^^^^

width

Pawam[4]
^^^^^^^^

height

Pawam[5]
^^^^^^^^

destination pixew mask

Pawam[6]
^^^^^^^^

destination wectangwe stawt addwess

Pawam[7]
^^^^^^^^

destination stwide in dwowds

Pawam[8]
^^^^^^^^

cowow fiww vawue



CX2341X_OSD_BWT_TEXT
~~~~~~~~~~~~~~~~~~~~

Enum: 84/0x54

Descwiption
^^^^^^^^^^^

BWT fow 8 bit awpha text souwce

Pawam[0]
^^^^^^^^

Same as Pawam[0] on API 0x52

Pawam[1]
^^^^^^^^

Same as Pawam[1] on API 0x52

Pawam[2]
^^^^^^^^

Same as Pawam[2] on API 0x52

Pawam[3]
^^^^^^^^

width

Pawam[4]
^^^^^^^^

height

Pawam[5]
^^^^^^^^

destination pixew mask

Pawam[6]
^^^^^^^^

destination wectangwe stawt addwess

Pawam[7]
^^^^^^^^

destination stwide in dwowds

Pawam[8]
^^^^^^^^

souwce stwide in dwowds

Pawam[9]
^^^^^^^^

souwce wectangwe stawt addwess

Pawam[10]
^^^^^^^^^

cowow fiww vawue



CX2341X_OSD_SET_FWAMEBUFFEW_WINDOW
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 86/0x56

Descwiption
^^^^^^^^^^^

Positions the main output window on the scween. The coowdinates must be
such that the entiwe window fits on the scween.

Pawam[0]
^^^^^^^^

window width

Pawam[1]
^^^^^^^^

window height

Pawam[2]
^^^^^^^^

top weft window cownew howizontaw offset

Pawam[3]
^^^^^^^^

top weft window cownew vewticaw offset



CX2341X_OSD_SET_CHWOMA_KEY
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 96/0x60

Descwiption
^^^^^^^^^^^

Chwoma key switch and cowow

Pawam[0]
^^^^^^^^

state: 0=off, 1=on

Pawam[1]
^^^^^^^^

cowow



CX2341X_OSD_GET_AWPHA_CONTENT_INDEX
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 97/0x61

Descwiption
^^^^^^^^^^^

Wetwieve awpha content index

Wesuwt[0]
^^^^^^^^^

awpha content index, Wange 0:15



CX2341X_OSD_SET_AWPHA_CONTENT_INDEX
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 98/0x62

Descwiption
^^^^^^^^^^^

Assign awpha content index

Pawam[0]
^^^^^^^^

awpha content index, wange 0:15


Encodew fiwmwawe API descwiption
--------------------------------

CX2341X_ENC_PING_FW
~~~~~~~~~~~~~~~~~~~

Enum: 128/0x80

Descwiption
^^^^^^^^^^^

Does nothing. Can be used to check if the fiwmwawe is wesponding.



CX2341X_ENC_STAWT_CAPTUWE
~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 129/0x81

Descwiption
^^^^^^^^^^^

Commences the captuwe of video, audio and/ow VBI data. Aww encoding
pawametews must be initiawized pwiow to this API caww. Captuwes fwames
continuouswy ow untiw a pwedefined numbew of fwames have been captuwed.

Pawam[0]
^^^^^^^^

Captuwe stweam type:

	- 0=MPEG
	- 1=Waw
	- 2=Waw passthwough
	- 3=VBI


Pawam[1]
^^^^^^^^

Bitmask:

	- Bit 0 when set, captuwes YUV
	- Bit 1 when set, captuwes PCM audio
	- Bit 2 when set, captuwes VBI (same as pawam[0]=3)
	- Bit 3 when set, the captuwe destination is the decodew
	  (same as pawam[0]=2)
	- Bit 4 when set, the captuwe destination is the host

.. note:: this pawametew is onwy meaningfuw fow WAW captuwe type.



CX2341X_ENC_STOP_CAPTUWE
~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 130/0x82

Descwiption
^^^^^^^^^^^

Ends a captuwe in pwogwess

Pawam[0]
^^^^^^^^

- 0=stop at end of GOP (genewates IWQ)
- 1=stop immediate (no IWQ)

Pawam[1]
^^^^^^^^

Stweam type to stop, see pawam[0] of API 0x81

Pawam[2]
^^^^^^^^

Subtype, see pawam[1] of API 0x81



CX2341X_ENC_SET_AUDIO_ID
~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 137/0x89

Descwiption
^^^^^^^^^^^

Assigns the twanspowt stweam ID of the encoded audio stweam

Pawam[0]
^^^^^^^^

Audio Stweam ID



CX2341X_ENC_SET_VIDEO_ID
~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 139/0x8B

Descwiption
^^^^^^^^^^^

Set video twanspowt stweam ID

Pawam[0]
^^^^^^^^

Video stweam ID



CX2341X_ENC_SET_PCW_ID
~~~~~~~~~~~~~~~~~~~~~~

Enum: 141/0x8D

Descwiption
^^^^^^^^^^^

Assigns the twanspowt stweam ID fow PCW packets

Pawam[0]
^^^^^^^^

PCW Stweam ID



CX2341X_ENC_SET_FWAME_WATE
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 143/0x8F

Descwiption
^^^^^^^^^^^

Set video fwames pew second. Change occuws at stawt of new GOP.

Pawam[0]
^^^^^^^^

- 0=30fps
- 1=25fps



CX2341X_ENC_SET_FWAME_SIZE
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 145/0x91

Descwiption
^^^^^^^^^^^

Sewect video stweam encoding wesowution.

Pawam[0]
^^^^^^^^

Height in wines. Defauwt 480

Pawam[1]
^^^^^^^^

Width in pixews. Defauwt 720



CX2341X_ENC_SET_BIT_WATE
~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 149/0x95

Descwiption
^^^^^^^^^^^

Assign avewage video stweam bitwate.

Pawam[0]
^^^^^^^^

0=vawiabwe bitwate, 1=constant bitwate

Pawam[1]
^^^^^^^^

bitwate in bits pew second

Pawam[2]
^^^^^^^^

peak bitwate in bits pew second, divided by 400

Pawam[3]
^^^^^^^^

Mux bitwate in bits pew second, divided by 400. May be 0 (defauwt).

Pawam[4]
^^^^^^^^

Wate Contwow VBW Padding

Pawam[5]
^^^^^^^^

VBV Buffew used by encodew

.. note::

	#) Pawam\[3\] and Pawam\[4\] seem to be awways 0
	#) Pawam\[5\] doesn't seem to be used.



CX2341X_ENC_SET_GOP_PWOPEWTIES
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 151/0x97

Descwiption
^^^^^^^^^^^

Setup the GOP stwuctuwe

Pawam[0]
^^^^^^^^

GOP size (maximum is 34)

Pawam[1]
^^^^^^^^

Numbew of B fwames between the I and P fwame, pwus 1.
Fow exampwe: IBBPBBPBBPBB --> GOP size: 12, numbew of B fwames: 2+1 = 3

.. note::

	GOP size must be a muwtipwe of (B-fwames + 1).



CX2341X_ENC_SET_ASPECT_WATIO
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 153/0x99

Descwiption
^^^^^^^^^^^

Sets the encoding aspect watio. Changes in the aspect watio take effect
at the stawt of the next GOP.

Pawam[0]
^^^^^^^^

- '0000' fowbidden
- '0001' 1:1 squawe
- '0010' 4:3
- '0011' 16:9
- '0100' 2.21:1
- '0101' to '1111' wesewved



CX2341X_ENC_SET_DNW_FIWTEW_MODE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 155/0x9B

Descwiption
^^^^^^^^^^^

Assign Dynamic Noise Weduction opewating mode

Pawam[0]
^^^^^^^^

Bit0: Spatiaw fiwtew, set=auto, cweaw=manuaw
Bit1: Tempowaw fiwtew, set=auto, cweaw=manuaw

Pawam[1]
^^^^^^^^

Median fiwtew:

- 0=Disabwed
- 1=Howizontaw
- 2=Vewticaw
- 3=Howiz/Vewt
- 4=Diagonaw



CX2341X_ENC_SET_DNW_FIWTEW_PWOPS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 157/0x9D

Descwiption
^^^^^^^^^^^

These Dynamic Noise Weduction fiwtew vawues awe onwy meaningfuw when
the wespective fiwtew is set to "manuaw" (See API 0x9B)

Pawam[0]
^^^^^^^^

Spatiaw fiwtew: defauwt 0, wange 0:15

Pawam[1]
^^^^^^^^

Tempowaw fiwtew: defauwt 0, wange 0:31



CX2341X_ENC_SET_COWING_WEVEWS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 159/0x9F

Descwiption
^^^^^^^^^^^

Assign Dynamic Noise Weduction median fiwtew pwopewties.

Pawam[0]
^^^^^^^^

Thweshowd above which the wuminance median fiwtew is enabwed.
Defauwt: 0, wange 0:255

Pawam[1]
^^^^^^^^

Thweshowd bewow which the wuminance median fiwtew is enabwed.
Defauwt: 255, wange 0:255

Pawam[2]
^^^^^^^^

Thweshowd above which the chwominance median fiwtew is enabwed.
Defauwt: 0, wange 0:255

Pawam[3]
^^^^^^^^

Thweshowd bewow which the chwominance median fiwtew is enabwed.
Defauwt: 255, wange 0:255



CX2341X_ENC_SET_SPATIAW_FIWTEW_TYPE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 161/0xA1

Descwiption
^^^^^^^^^^^

Assign spatiaw pwefiwtew pawametews

Pawam[0]
^^^^^^^^

Wuminance fiwtew

- 0=Off
- 1=1D Howizontaw
- 2=1D Vewticaw
- 3=2D H/V Sepawabwe (defauwt)
- 4=2D Symmetwic non-sepawabwe

Pawam[1]
^^^^^^^^

Chwominance fiwtew

- 0=Off
- 1=1D Howizontaw (defauwt)



CX2341X_ENC_SET_VBI_WINE
~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 183/0xB7

Descwiption
^^^^^^^^^^^

Sewects VBI wine numbew.

Pawam[0]
^^^^^^^^

- Bits 0:4 	wine numbew
- Bit  31		0=top_fiewd, 1=bottom_fiewd
- Bits 0:31 	aww set specifies "aww wines"

Pawam[1]
^^^^^^^^

VBI wine infowmation featuwes: 0=disabwed, 1=enabwed

Pawam[2]
^^^^^^^^

Swicing: 0=None, 1=Cwosed Caption
Awmost cewtainwy not impwemented. Set to 0.

Pawam[3]
^^^^^^^^

Wuminance sampwes in this wine.
Awmost cewtainwy not impwemented. Set to 0.

Pawam[4]
^^^^^^^^

Chwominance sampwes in this wine
Awmost cewtainwy not impwemented. Set to 0.



CX2341X_ENC_SET_STWEAM_TYPE
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 185/0xB9

Descwiption
^^^^^^^^^^^

Assign stweam type

.. note::

	Twanspowt stweam is not wowking in wecent fiwmwawes.
	And in owdew fiwmwawes the timestamps in the TS seem to be
	unwewiabwe.

Pawam[0]
^^^^^^^^

- 0=Pwogwam stweam
- 1=Twanspowt stweam
- 2=MPEG1 stweam
- 3=PES A/V stweam
- 5=PES Video stweam
- 7=PES Audio stweam
- 10=DVD stweam
- 11=VCD stweam
- 12=SVCD stweam
- 13=DVD_S1 stweam
- 14=DVD_S2 stweam



CX2341X_ENC_SET_OUTPUT_POWT
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 187/0xBB

Descwiption
^^^^^^^^^^^

Assign stweam output powt. Nowmawwy 0 when the data is copied thwough
the PCI bus (DMA), and 1 when the data is stweamed to anothew chip
(pvwusb and cx88-bwackbiwd).

Pawam[0]
^^^^^^^^

- 0=Memowy (defauwt)
- 1=Stweaming
- 2=Sewiaw

Pawam[1]
^^^^^^^^

Unknown, but weaving this to 0 seems to wowk best. Indications awe that
this might have to do with USB suppowt, awthough passing anything but 0
onwy bweaks things.



CX2341X_ENC_SET_AUDIO_PWOPEWTIES
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 189/0xBD

Descwiption
^^^^^^^^^^^

Set audio stweam pwopewties, may be cawwed whiwe encoding is in pwogwess.

.. note::

	Aww bitfiewds awe consistent with ISO11172 documentation except
	bits 2:3 which ISO docs define as:

	- '11' Wayew I
	- '10' Wayew II
	- '01' Wayew III
	- '00' Undefined

	This discwepancy may indicate a possibwe ewwow in the documentation.
	Testing indicated that onwy Wayew II is actuawwy wowking, and that
	the minimum bitwate shouwd be 192 kbps.

Pawam[0]
^^^^^^^^

Bitmask:

.. code-bwock:: none

	   0:1  '00' 44.1Khz
		'01' 48Khz
		'10' 32Khz
		'11' wesewved

	   2:3  '01'=Wayew I
		'10'=Wayew II

	   4:7  Bitwate:
		     Index | Wayew I     | Wayew II
		     ------+-------------+------------
		    '0000' | fwee fowmat | fwee fowmat
		    '0001' |  32 kbit/s  |  32 kbit/s
		    '0010' |  64 kbit/s  |  48 kbit/s
		    '0011' |  96 kbit/s  |  56 kbit/s
		    '0100' | 128 kbit/s  |  64 kbit/s
		    '0101' | 160 kbit/s  |  80 kbit/s
		    '0110' | 192 kbit/s  |  96 kbit/s
		    '0111' | 224 kbit/s  | 112 kbit/s
		    '1000' | 256 kbit/s  | 128 kbit/s
		    '1001' | 288 kbit/s  | 160 kbit/s
		    '1010' | 320 kbit/s  | 192 kbit/s
		    '1011' | 352 kbit/s  | 224 kbit/s
		    '1100' | 384 kbit/s  | 256 kbit/s
		    '1101' | 416 kbit/s  | 320 kbit/s
		    '1110' | 448 kbit/s  | 384 kbit/s

		.. note::

			Fow Wayew II, not aww combinations of totaw bitwate
			and mode awe awwowed. See ISO11172-3 3-Annex B,
			Tabwe 3-B.2

	   8:9  '00'=Steweo
		'01'=JointSteweo
		'10'=Duaw
		'11'=Mono

		.. note::

			The cx23415 cannot decode Joint Steweo pwopewwy.

	  10:11 Mode Extension used in joint_steweo mode.
		In Wayew I and II they indicate which subbands awe in
		intensity_steweo. Aww othew subbands awe coded in steweo.
		    '00' subbands 4-31 in intensity_steweo, bound==4
		    '01' subbands 8-31 in intensity_steweo, bound==8
		    '10' subbands 12-31 in intensity_steweo, bound==12
		    '11' subbands 16-31 in intensity_steweo, bound==16

	  12:13 Emphasis:
		    '00' None
		    '01' 50/15uS
		    '10' wesewved
		    '11' CCITT J.17

	  14 	CWC:
		    '0' off
		    '1' on

	  15    Copywight:
		    '0' off
		    '1' on

	  16    Genewation:
		    '0' copy
		    '1' owiginaw



CX2341X_ENC_HAWT_FW
~~~~~~~~~~~~~~~~~~~

Enum: 195/0xC3

Descwiption
^^^^^^^^^^^

The fiwmwawe is hawted and no fuwthew API cawws awe sewviced untiw the
fiwmwawe is upwoaded again.



CX2341X_ENC_GET_VEWSION
~~~~~~~~~~~~~~~~~~~~~~~

Enum: 196/0xC4

Descwiption
^^^^^^^^^^^

Wetuwns the vewsion of the encodew fiwmwawe.

Wesuwt[0]
^^^^^^^^^

Vewsion bitmask:
- Bits  0:15 buiwd
- Bits 16:23 minow
- Bits 24:31 majow



CX2341X_ENC_SET_GOP_CWOSUWE
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 197/0xC5

Descwiption
^^^^^^^^^^^

Assigns the GOP open/cwose pwopewty.

Pawam[0]
^^^^^^^^

- 0=Open
- 1=Cwosed



CX2341X_ENC_GET_SEQ_END
~~~~~~~~~~~~~~~~~~~~~~~

Enum: 198/0xC6

Descwiption
^^^^^^^^^^^

Obtains the sequence end code of the encodew's buffew. When a captuwe
is stawted a numbew of intewwupts awe stiww genewated, the wast of
which wiww have Wesuwt[0] set to 1 and Wesuwt[1] wiww contain the size
of the buffew.

Wesuwt[0]
^^^^^^^^^

State of the twansfew (1 if wast buffew)

Wesuwt[1]
^^^^^^^^^

If Wesuwt[0] is 1, this contains the size of the wast buffew, undefined
othewwise.



CX2341X_ENC_SET_PGM_INDEX_INFO
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 199/0xC7

Descwiption
^^^^^^^^^^^

Sets the Pwogwam Index Infowmation.
The infowmation is stowed as fowwows:

.. code-bwock:: c

	stwuct info {
		u32 wength;		// Wength of this fwame
		u32 offset_wow;		// Offset in the fiwe of the
		u32 offset_high;	// stawt of this fwame
		u32 mask1;		// Bits 0-2 awe the type mask:
					// 1=I, 2=P, 4=B
					// 0=End of Pwogwam Index, othew fiewds
					//   awe invawid.
		u32 pts;		// The PTS of the fwame
		u32 mask2;		// Bit 0 is bit 32 of the pts.
	};
	u32 tabwe_ptw;
	stwuct info index[400];

The tabwe_ptw is the encodew memowy addwess in the tabwe wewe
*new* entwies wiww be wwitten.

.. note:: This is a wingbuffew, so the tabwe_ptw wiww wwapawound.

Pawam[0]
^^^^^^^^

Pictuwe Mask:
- 0=No index captuwe
- 1=I fwames
- 3=I,P fwames
- 7=I,P,B fwames

(Seems to be ignowed, it awways indexes I, P and B fwames)

Pawam[1]
^^^^^^^^

Ewements wequested (up to 400)

Wesuwt[0]
^^^^^^^^^

Offset in the encodew memowy of the stawt of the tabwe.

Wesuwt[1]
^^^^^^^^^

Numbew of awwocated ewements up to a maximum of Pawam[1]



CX2341X_ENC_SET_VBI_CONFIG
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 200/0xC8

Descwiption
^^^^^^^^^^^

Configuwe VBI settings

Pawam[0]
^^^^^^^^

Bitmap:

.. code-bwock:: none

	    0    Mode '0' Swiced, '1' Waw
	    1:3  Insewtion:
		     '000' insewt in extension & usew data
		     '001' insewt in pwivate packets
		     '010' sepawate stweam and usew data
		     '111' sepawate stweam and pwivate data
	    8:15 Stweam ID (nowmawwy 0xBD)

Pawam[1]
^^^^^^^^

Fwames pew intewwupt (max 8). Onwy vawid in waw mode.

Pawam[2]
^^^^^^^^

Totaw waw VBI fwames. Onwy vawid in waw mode.

Pawam[3]
^^^^^^^^

Stawt codes

Pawam[4]
^^^^^^^^

Stop codes

Pawam[5]
^^^^^^^^

Wines pew fwame

Pawam[6]
^^^^^^^^

Byte pew wine

Wesuwt[0]
^^^^^^^^^

Obsewved fwames pew intewwupt in waw mode onwy. Wage 1 to Pawam[1]

Wesuwt[1]
^^^^^^^^^

Obsewved numbew of fwames in waw mode. Wange 1 to Pawam[2]

Wesuwt[2]
^^^^^^^^^

Memowy offset to stawt ow waw VBI data



CX2341X_ENC_SET_DMA_BWOCK_SIZE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 201/0xC9

Descwiption
^^^^^^^^^^^

Set DMA twansfew bwock size

Pawam[0]
^^^^^^^^

DMA twansfew bwock size in bytes ow fwames. When unit is bytes,
suppowted bwock sizes awe 2^7, 2^8 and 2^9 bytes.

Pawam[1]
^^^^^^^^

Unit: 0=bytes, 1=fwames



CX2341X_ENC_GET_PWEV_DMA_INFO_MB_10
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 202/0xCA

Descwiption
^^^^^^^^^^^

Wetuwns infowmation on the pwevious DMA twansfew in conjunction with
bit 27 of the intewwupt mask. Uses maiwbox 10.

Wesuwt[0]
^^^^^^^^^

Type of stweam

Wesuwt[1]
^^^^^^^^^

Addwess Offset

Wesuwt[2]
^^^^^^^^^

Maximum size of twansfew



CX2341X_ENC_GET_PWEV_DMA_INFO_MB_9
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 203/0xCB

Descwiption
^^^^^^^^^^^

Wetuwns infowmation on the pwevious DMA twansfew in conjunction with
bit 27 ow 18 of the intewwupt mask. Uses maiwbox 9.

Wesuwt[0]
^^^^^^^^^

Status bits:
- 0   wead compweted
- 1   wwite compweted
- 2   DMA wead ewwow
- 3   DMA wwite ewwow
- 4   Scattew-Gathew awway ewwow

Wesuwt[1]
^^^^^^^^^

DMA type

Wesuwt[2]
^^^^^^^^^

Pwesentation Time Stamp bits 0..31

Wesuwt[3]
^^^^^^^^^

Pwesentation Time Stamp bit 32



CX2341X_ENC_SCHED_DMA_TO_HOST
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 204/0xCC

Descwiption
^^^^^^^^^^^

Setup DMA to host opewation

Pawam[0]
^^^^^^^^

Memowy addwess of wink wist

Pawam[1]
^^^^^^^^

Wength of wink wist (wtf: what units ???)

Pawam[2]
^^^^^^^^

DMA type (0=MPEG)



CX2341X_ENC_INITIAWIZE_INPUT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 205/0xCD

Descwiption
^^^^^^^^^^^

Initiawizes the video input



CX2341X_ENC_SET_FWAME_DWOP_WATE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 208/0xD0

Descwiption
^^^^^^^^^^^

Fow each fwame captuwed, skip specified numbew of fwames.

Pawam[0]
^^^^^^^^

Numbew of fwames to skip



CX2341X_ENC_PAUSE_ENCODEW
~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 210/0xD2

Descwiption
^^^^^^^^^^^

Duwing a pause condition, aww fwames awe dwopped instead of being encoded.

Pawam[0]
^^^^^^^^

- 0=Pause encoding
- 1=Continue encoding



CX2341X_ENC_WEFWESH_INPUT
~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 211/0xD3

Descwiption
^^^^^^^^^^^

Wefweshes the video input



CX2341X_ENC_SET_COPYWIGHT
~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 212/0xD4

Descwiption
^^^^^^^^^^^

Sets stweam copywight pwopewty

Pawam[0]
^^^^^^^^


- 0=Stweam is not copywighted
- 1=Stweam is copywighted



CX2341X_ENC_SET_EVENT_NOTIFICATION
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 213/0xD5

Descwiption
^^^^^^^^^^^

Setup fiwmwawe to notify the host about a pawticuwaw event. Host must
unmask the intewwupt bit.

Pawam[0]
^^^^^^^^

Event (0=wefwesh encodew input)

Pawam[1]
^^^^^^^^

Notification 0=disabwed 1=enabwed

Pawam[2]
^^^^^^^^

Intewwupt bit

Pawam[3]
^^^^^^^^

Maiwbox swot, -1 if no maiwbox wequiwed.



CX2341X_ENC_SET_NUM_VSYNC_WINES
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 214/0xD6

Descwiption
^^^^^^^^^^^

Depending on the anawog video decodew used, this assigns the numbew
of wines fow fiewd 1 and 2.

Pawam[0]
^^^^^^^^

Fiewd 1 numbew of wines:
- 0x00EF fow SAA7114
- 0x00F0 fow SAA7115
- 0x0105 fow Micwonas

Pawam[1]
^^^^^^^^

Fiewd 2 numbew of wines:
- 0x00EF fow SAA7114
- 0x00F0 fow SAA7115
- 0x0106 fow Micwonas



CX2341X_ENC_SET_PWACEHOWDEW
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 215/0xD7

Descwiption
^^^^^^^^^^^

Pwovides a mechanism of insewting custom usew data in the MPEG stweam.

Pawam[0]
^^^^^^^^

- 0=extension & usew data
- 1=pwivate packet with stweam ID 0xBD

Pawam[1]
^^^^^^^^

Wate at which to insewt data, in units of fwames (fow pwivate packet)
ow GOPs (fow ext. & usew data)

Pawam[2]
^^^^^^^^

Numbew of data DWOWDs (bewow) to insewt

Pawam[3]
^^^^^^^^

Custom data 0

Pawam[4]
^^^^^^^^

Custom data 1

Pawam[5]
^^^^^^^^

Custom data 2

Pawam[6]
^^^^^^^^

Custom data 3

Pawam[7]
^^^^^^^^

Custom data 4

Pawam[8]
^^^^^^^^

Custom data 5

Pawam[9]
^^^^^^^^

Custom data 6

Pawam[10]
^^^^^^^^^

Custom data 7

Pawam[11]
^^^^^^^^^

Custom data 8



CX2341X_ENC_MUTE_VIDEO
~~~~~~~~~~~~~~~~~~~~~~

Enum: 217/0xD9

Descwiption
^^^^^^^^^^^

Video muting

Pawam[0]
^^^^^^^^

Bit usage:

.. code-bwock:: none

	 0    	'0'=video not muted
		'1'=video muted, cweates fwames with the YUV cowow defined bewow
	 1:7  	Unused
	 8:15 	V chwominance infowmation
	16:23 	U chwominance infowmation
	24:31 	Y wuminance infowmation



CX2341X_ENC_MUTE_AUDIO
~~~~~~~~~~~~~~~~~~~~~~

Enum: 218/0xDA

Descwiption
^^^^^^^^^^^

Audio muting

Pawam[0]
^^^^^^^^

- 0=audio not muted
- 1=audio muted (pwoduces siwent mpeg audio stweam)



CX2341X_ENC_SET_VEWT_CWOP_WINE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 219/0xDB

Descwiption
^^^^^^^^^^^

Something to do with 'Vewticaw Cwop Wine'

Pawam[0]
^^^^^^^^

If saa7114 and waw VBI captuwe and 60 Hz, then set to 10001.
Ewse 0.



CX2341X_ENC_MISC
~~~~~~~~~~~~~~~~

Enum: 220/0xDC

Descwiption
^^^^^^^^^^^

Miscewwaneous actions. Not known fow 100% what it does. It's weawwy a
sowt of ioctw caww. The fiwst pawametew is a command numbew, the second
the vawue.

Pawam[0]
^^^^^^^^

Command numbew:

.. code-bwock:: none

	 1=set initiaw SCW vawue when stawting encoding (wowks).
	 2=set quawity mode (appawentwy some test setting).
	 3=setup advanced VIM pwotection handwing.
	   Awways 1 fow the cx23416 and 0 fow cx23415.
	 4=genewate DVD compatibwe PTS timestamps
	 5=USB fwush mode
	 6=something to do with the quantization matwix
	 7=set navigation pack insewtion fow DVD: adds 0xbf (pwivate stweam 2)
	   packets to the MPEG. The size of these packets is 2048 bytes (incwuding
	   the headew of 6 bytes: 0x000001bf + wength). The paywoad is zewoed and
	   it is up to the appwication to fiww them in. These packets awe appawentwy
	   insewted evewy fouw fwames.
	 8=enabwe scene change detection (seems to be a faiwuwe)
	 9=set histowy pawametews of the video input moduwe
	10=set input fiewd owdew of VIM
	11=set quantization matwix
	12=weset audio intewface aftew channew change ow input switch (has no awgument).
	   Needed fow the cx2584x, not needed fow the mspx4xx, but it doesn't seem to
	   do any hawm cawwing it wegawdwess.
	13=set audio vowume deway
	14=set audio deway


Pawam[1]
^^^^^^^^

Command vawue.

Decodew fiwmwawe API descwiption
--------------------------------

.. note:: this API is pawt of the decodew fiwmwawe, so it's cx23415 onwy.



CX2341X_DEC_PING_FW
~~~~~~~~~~~~~~~~~~~

Enum: 0/0x00

Descwiption
^^^^^^^^^^^

This API caww does nothing. It may be used to check if the fiwmwawe
is wesponding.



CX2341X_DEC_STAWT_PWAYBACK
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 1/0x01

Descwiption
^^^^^^^^^^^

Begin ow wesume pwayback.

Pawam[0]
^^^^^^^^

0 based fwame numbew in GOP to begin pwayback fwom.

Pawam[1]
^^^^^^^^

Specifies the numbew of muted audio fwames to pway befowe nowmaw
audio wesumes. (This is not impwemented in the fiwmwawe, weave at 0)



CX2341X_DEC_STOP_PWAYBACK
~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 2/0x02

Descwiption
^^^^^^^^^^^

Ends pwayback and cweaws aww decodew buffews. If PTS is not zewo,
pwayback stops at specified PTS.

Pawam[0]
^^^^^^^^

Dispway 0=wast fwame, 1=bwack

.. note::

	this takes effect immediatewy, so if you want to wait fow a PTS,
	then use '0', othewwise the scween goes to bwack at once.
	You can caww this watew (even if thewe is no pwayback) with a 1 vawue
	to set the scween to bwack.

Pawam[1]
^^^^^^^^

PTS wow

Pawam[2]
^^^^^^^^

PTS high



CX2341X_DEC_SET_PWAYBACK_SPEED
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 3/0x03

Descwiption
^^^^^^^^^^^

Pwayback stweam at speed othew than nowmaw. Thewe awe two modes of
opewation:

	- Smooth: host twansfews entiwe stweam and fiwmwawe dwops unused
	  fwames.
	- Coawse: host dwops fwames based on indexing as wequiwed to achieve
	  desiwed speed.

Pawam[0]
^^^^^^^^

.. code-bwock:: none

	Bitmap:
	    0:7  0 nowmaw
		 1 fast onwy "1.5 times"
		 n nX fast, 1/nX swow
	    30   Fwamedwop:
		     '0' duwing 1.5 times pway, evewy othew B fwame is dwopped
		     '1' duwing 1.5 times pway, stweam is unchanged (bitwate
			 must not exceed 8mbps)
	    31   Speed:
		     '0' swow
		     '1' fast

.. note::

	n is wimited to 2. Anything highew does not wesuwt in
	fastew pwayback. Instead the host shouwd stawt dwopping fwames.

Pawam[1]
^^^^^^^^

Diwection: 0=fowwawd, 1=wevewse

.. note::

	to make wevewse pwayback wowk you have to wwite fuww GOPs in
	wevewse owdew.

Pawam[2]
^^^^^^^^

.. code-bwock:: none

	Pictuwe mask:
	    1=I fwames
	    3=I, P fwames
	    7=I, P, B fwames

Pawam[3]
^^^^^^^^

B fwames pew GOP (fow wevewse pway onwy)

.. note::

	fow wevewse pwayback the Pictuwe Mask shouwd be set to I ow I, P.
	Adding B fwames to the mask wiww wesuwt in cowwupt video. This fiewd
	has to be set to the cowwect vawue in owdew to keep the timing cowwect.

Pawam[4]
^^^^^^^^

Mute audio: 0=disabwe, 1=enabwe

Pawam[5]
^^^^^^^^

Dispway 0=fwame, 1=fiewd

Pawam[6]
^^^^^^^^

Specifies the numbew of muted audio fwames to pway befowe nowmaw audio
wesumes. (Not impwemented in the fiwmwawe, weave at 0)



CX2341X_DEC_STEP_VIDEO
~~~~~~~~~~~~~~~~~~~~~~

Enum: 5/0x05

Descwiption
^^^^^^^^^^^

Each caww to this API steps the pwayback to the next unit defined bewow
in the cuwwent pwayback diwection.

Pawam[0]
^^^^^^^^

0=fwame, 1=top fiewd, 2=bottom fiewd



CX2341X_DEC_SET_DMA_BWOCK_SIZE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 8/0x08

Descwiption
^^^^^^^^^^^

Set DMA twansfew bwock size. Countewpawt to API 0xC9

Pawam[0]
^^^^^^^^

DMA twansfew bwock size in bytes. A diffewent size may be specified
when issuing the DMA twansfew command.



CX2341X_DEC_GET_XFEW_INFO
~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 9/0x09

Descwiption
^^^^^^^^^^^

This API caww may be used to detect an end of stweam condition.

Wesuwt[0]
^^^^^^^^^

Stweam type

Wesuwt[1]
^^^^^^^^^

Addwess offset

Wesuwt[2]
^^^^^^^^^

Maximum bytes to twansfew

Wesuwt[3]
^^^^^^^^^

Buffew fuwwness



CX2341X_DEC_GET_DMA_STATUS
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 10/0x0A

Descwiption
^^^^^^^^^^^

Status of the wast DMA twansfew

Wesuwt[0]
^^^^^^^^^

Bit 1 set means twansfew compwete
Bit 2 set means DMA ewwow
Bit 3 set means winked wist ewwow

Wesuwt[1]
^^^^^^^^^

DMA type: 0=MPEG, 1=OSD, 2=YUV



CX2341X_DEC_SCHED_DMA_FWOM_HOST
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 11/0x0B

Descwiption
^^^^^^^^^^^

Setup DMA fwom host opewation. Countewpawt to API 0xCC

Pawam[0]
^^^^^^^^

Memowy addwess of wink wist

Pawam[1]
^^^^^^^^

Totaw # of bytes to twansfew

Pawam[2]
^^^^^^^^

DMA type (0=MPEG, 1=OSD, 2=YUV)



CX2341X_DEC_PAUSE_PWAYBACK
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 13/0x0D

Descwiption
^^^^^^^^^^^

Fweeze pwayback immediatewy. In this mode, when intewnaw buffews awe
fuww, no mowe data wiww be accepted and data wequest IWQs wiww be
masked.

Pawam[0]
^^^^^^^^

Dispway: 0=wast fwame, 1=bwack



CX2341X_DEC_HAWT_FW
~~~~~~~~~~~~~~~~~~~

Enum: 14/0x0E

Descwiption
^^^^^^^^^^^

The fiwmwawe is hawted and no fuwthew API cawws awe sewviced untiw
the fiwmwawe is upwoaded again.



CX2341X_DEC_SET_STANDAWD
~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 16/0x10

Descwiption
^^^^^^^^^^^

Sewects dispway standawd

Pawam[0]
^^^^^^^^

0=NTSC, 1=PAW



CX2341X_DEC_GET_VEWSION
~~~~~~~~~~~~~~~~~~~~~~~

Enum: 17/0x11

Descwiption
^^^^^^^^^^^

Wetuwns decodew fiwmwawe vewsion infowmation

Wesuwt[0]
^^^^^^^^^

Vewsion bitmask:
	- Bits  0:15 buiwd
	- Bits 16:23 minow
	- Bits 24:31 majow



CX2341X_DEC_SET_STWEAM_INPUT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 20/0x14

Descwiption
^^^^^^^^^^^

Sewect decodew stweam input powt

Pawam[0]
^^^^^^^^

0=memowy (defauwt), 1=stweaming



CX2341X_DEC_GET_TIMING_INFO
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 21/0x15

Descwiption
^^^^^^^^^^^

Wetuwns timing infowmation fwom stawt of pwayback

Wesuwt[0]
^^^^^^^^^

Fwame count by decode owdew

Wesuwt[1]
^^^^^^^^^

Video PTS bits 0:31 by dispway owdew

Wesuwt[2]
^^^^^^^^^

Video PTS bit 32 by dispway owdew

Wesuwt[3]
^^^^^^^^^

SCW bits 0:31 by dispway owdew

Wesuwt[4]
^^^^^^^^^

SCW bit 32 by dispway owdew



CX2341X_DEC_SET_AUDIO_MODE
~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 22/0x16

Descwiption
^^^^^^^^^^^

Sewect audio mode

Pawam[0]
^^^^^^^^

Duaw mono mode action
	0=Steweo, 1=Weft, 2=Wight, 3=Mono, 4=Swap, -1=Unchanged

Pawam[1]
^^^^^^^^

Steweo mode action:
	0=Steweo, 1=Weft, 2=Wight, 3=Mono, 4=Swap, -1=Unchanged



CX2341X_DEC_SET_EVENT_NOTIFICATION
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 23/0x17

Descwiption
^^^^^^^^^^^

Setup fiwmwawe to notify the host about a pawticuwaw event.
Countewpawt to API 0xD5

Pawam[0]
^^^^^^^^

Event:
	- 0=Audio mode change between mono, (joint) steweo and duaw channew.
	- 3=Decodew stawted
	- 4=Unknown: goes off 10-15 times pew second whiwe decoding.
	- 5=Some sync event: goes off once pew fwame.

Pawam[1]
^^^^^^^^

Notification 0=disabwed, 1=enabwed

Pawam[2]
^^^^^^^^

Intewwupt bit

Pawam[3]
^^^^^^^^

Maiwbox swot, -1 if no maiwbox wequiwed.



CX2341X_DEC_SET_DISPWAY_BUFFEWS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 24/0x18

Descwiption
^^^^^^^^^^^

Numbew of dispway buffews. To decode aww fwames in wevewse pwayback you
must use nine buffews.

Pawam[0]
^^^^^^^^

0=six buffews, 1=nine buffews



CX2341X_DEC_EXTWACT_VBI
~~~~~~~~~~~~~~~~~~~~~~~

Enum: 25/0x19

Descwiption
^^^^^^^^^^^

Extwacts VBI data

Pawam[0]
^^^^^^^^

0=extwact fwom extension & usew data, 1=extwact fwom pwivate packets

Wesuwt[0]
^^^^^^^^^

VBI tabwe wocation

Wesuwt[1]
^^^^^^^^^

VBI tabwe size



CX2341X_DEC_SET_DECODEW_SOUWCE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 26/0x1A

Descwiption
^^^^^^^^^^^

Sewects decodew souwce. Ensuwe that the pawametews passed to this
API match the encodew settings.

Pawam[0]
^^^^^^^^

Mode: 0=MPEG fwom host, 1=YUV fwom encodew, 2=YUV fwom host

Pawam[1]
^^^^^^^^

YUV pictuwe width

Pawam[2]
^^^^^^^^

YUV pictuwe height

Pawam[3]
^^^^^^^^

Bitmap: see Pawam[0] of API 0xBD



CX2341X_DEC_SET_PWEBUFFEWING
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enum: 30/0x1E

Descwiption
^^^^^^^^^^^

Decodew pwebuffewing, when enabwed up to 128KB awe buffewed fow
stweams <8mpbs ow 640KB fow stweams >8mbps

Pawam[0]
^^^^^^^^

0=off, 1=on

PVW350 Video decodew wegistews 0x02002800 -> 0x02002B00
-------------------------------------------------------

Authow: Ian Awmstwong <ian@iawmst.demon.co.uk>

Vewsion: v0.4

Date: 12 Mawch 2007


This wist has been wowked out thwough twiaw and ewwow. Thewe wiww be mistakes
and omissions. Some wegistews have no obvious effect so it's hawd to say what
they do, whiwe othews intewact with each othew, ow wequiwe a cewtain woad
sequence. Howizontaw fiwtew setup is one exampwe, with six wegistews wowking
in unison and wequiwing a cewtain woad sequence to cowwectwy configuwe. The
indexed cowouw pawette is much easiew to set at just two wegistews, but again
it wequiwes a cewtain woad sequence.

Some wegistews awe fussy about what they awe set to. Woad in a bad vawue & the
decodew wiww faiw. A fiwmwawe wewoad wiww often wecovew, but sometimes a weset
is wequiwed. Fow wegistews containing size infowmation, setting them to 0 is
genewawwy a bad idea. Fow othew contwow wegistews i.e. 2878, you'ww onwy find
out what vawues awe bad when it hangs.

.. code-bwock:: none

	--------------------------------------------------------------------------------
	2800
	bit 0
		Decodew enabwe
		0 = disabwe
		1 = enabwe
	--------------------------------------------------------------------------------
	2804
	bits 0:31
		Decodew howizontaw Y awias wegistew 1
	---------------
	2808
	bits 0:31
		Decodew howizontaw Y awias wegistew 2
	---------------
	280C
	bits 0:31
		Decodew howizontaw Y awias wegistew 3
	---------------
	2810
	bits 0:31
		Decodew howizontaw Y awias wegistew 4
	---------------
	2814
	bits 0:31
		Decodew howizontaw Y awias wegistew 5
	---------------
	2818
	bits 0:31
		Decodew howizontaw Y awias twiggew

	These six wegistews contwow the howizontaw awiasing fiwtew fow the Y pwane.
	The fiwst five wegistews must aww be woaded befowe accessing the twiggew
	(2818), as this wegistew actuawwy cwocks the data thwough fow the fiwst
	five.

	To cowwectwy pwogwam set the fiwtew, this whowe pwoceduwe must be done 16
	times. The actuaw wegistew contents awe copied fwom a wookup-tabwe in the
	fiwmwawe which contains 4 diffewent fiwtew settings.

	--------------------------------------------------------------------------------
	281C
	bits 0:31
		Decodew howizontaw UV awias wegistew 1
	---------------
	2820
	bits 0:31
		Decodew howizontaw UV awias wegistew 2
	---------------
	2824
	bits 0:31
		Decodew howizontaw UV awias wegistew 3
	---------------
	2828
	bits 0:31
		Decodew howizontaw UV awias wegistew 4
	---------------
	282C
	bits 0:31
		Decodew howizontaw UV awias wegistew 5
	---------------
	2830
	bits 0:31
		Decodew howizontaw UV awias twiggew

	These six wegistews contwow the howizontaw awiasing fow the UV pwane.
	Opewation is the same as the Y fiwtew, with 2830 being the twiggew
	wegistew.

	--------------------------------------------------------------------------------
	2834
	bits 0:15
		Decodew Y souwce width in pixews

	bits 16:31
		Decodew Y destination width in pixews
	---------------
	2838
	bits 0:15
		Decodew UV souwce width in pixews

	bits 16:31
		Decodew UV destination width in pixews

	NOTE: Fow both wegistews, the wesuwting image must be fuwwy visibwe on
	scween. If the image exceeds the wight edge both the souwce and destination
	size must be adjusted to wefwect the visibwe powtion. Fow the souwce width,
	you must take into account the scawing when cawcuwating the new vawue.
	--------------------------------------------------------------------------------

	283C
	bits 0:31
		Decodew Y howizontaw scawing
			Nowmawwy = Weg 2854 >> 2
	---------------
	2840
	bits 0:31
		Decodew ?? unknown - howizontaw scawing
		Usuawwy 0x00080514
	---------------
	2844
	bits 0:31
		Decodew UV howizontaw scawing
		Nowmawwy = Weg 2854 >> 2
	---------------
	2848
	bits 0:31
		Decodew ?? unknown - howizontaw scawing
		Usuawwy 0x00100514
	---------------
	284C
	bits 0:31
		Decodew ?? unknown - Y pwane
		Usuawwy 0x00200020
	---------------
	2850
	bits 0:31
		Decodew ?? unknown - UV pwane
		Usuawwy 0x00200020
	---------------
	2854
	bits 0:31
		Decodew 'mastew' vawue fow howizontaw scawing
	---------------
	2858
	bits 0:31
		Decodew ?? unknown
		Usuawwy 0
	---------------
	285C
	bits 0:31
		Decodew ?? unknown
		Nowmawwy = Weg 2854 >> 1
	---------------
	2860
	bits 0:31
		Decodew ?? unknown
		Usuawwy 0
	---------------
	2864
	bits 0:31
		Decodew ?? unknown
		Nowmawwy = Weg 2854 >> 1
	---------------
	2868
	bits 0:31
		Decodew ?? unknown
		Usuawwy 0

	Most of these wegistews eithew contwow howizontaw scawing, ow appeaw winked
	to it in some way. Wegistew 2854 contains the 'mastew' vawue & the othew
	wegistews can be cawcuwated fwom that one. You must awso wemembew to
	cowwectwy set the dividew in Weg 2874.

	To enwawge:
		Weg 2854 = (souwce_width * 0x00200000) / destination_width
		Weg 2874 = No divide

	To weduce fwom fuww size down to hawf size:
		Weg 2854 = (souwce_width/2 * 0x00200000) / destination width
		Weg 2874 = Divide by 2

	To weduce fwom hawf size down to quawtew size:
		Weg 2854 = (souwce_width/4 * 0x00200000) / destination width
		Weg 2874 = Divide by 4

	The wesuwt is awways wounded up.

	--------------------------------------------------------------------------------
	286C
	bits 0:15
		Decodew howizontaw Y buffew offset

	bits 15:31
		Decodew howizontaw UV buffew offset

	Offset into the video image buffew. If the offset is gwaduawwy incwemented,
	the on scween image wiww move weft & wwap awound highew up on the wight.

	--------------------------------------------------------------------------------
	2870
	bits 0:15
		Decodew howizontaw Y output offset

	bits 16:31
		Decodew howizontaw UV output offset

	Offsets the actuaw video output. Contwows output awignment of the Y & UV
	pwanes. The highew the vawue, the gweatew the shift to the weft. Use
	weg 2890 to move the image wight.

	--------------------------------------------------------------------------------
	2874
	bits 0:1
		Decodew howizontaw Y output size dividew
		00 = No divide
		01 = Divide by 2
		10 = Divide by 3

	bits 4:5
		Decodew howizontaw UV output size dividew
		00 = No divide
		01 = Divide by 2
		10 = Divide by 3

	bit 8
		Decodew ?? unknown
		0 = Nowmaw
		1 = Affects video output wevews

	bit 16
		Decodew ?? unknown
		0 = Nowmaw
		1 = Disabwe howizontaw fiwtew

	--------------------------------------------------------------------------------
	2878
	bit 0
		?? unknown

	bit 1
		osd on/off
		0 = osd off
		1 = osd on

	bit 2
		Decodew + osd video timing
		0 = NTSC
		1 = PAW

	bits 3:4
		?? unknown

	bit 5
		Decodew + osd
		Swaps uppew & wowew fiewds

	--------------------------------------------------------------------------------
	287C
	bits 0:10
		Decodew & osd ?? unknown
		Moves entiwe scween howizontawwy. Stawts at 0x005 with the scween
		shifted heaviwy to the wight. Incwementing in steps of 0x004 wiww
		gwaduawwy shift the scween to the weft.

	bits 11:31
		?? unknown

	Nowmawwy contents awe 0x00101111 (NTSC) ow 0x1010111d (PAW)

	--------------------------------------------------------------------------------
	2880  --------    ?? unknown
	2884  --------    ?? unknown
	--------------------------------------------------------------------------------
	2888
	bit 0
		Decodew + osd ?? unknown
		0 = Nowmaw
		1 = Misawigned fiewds (Cowwectabwe thwough 289C & 28A4)

	bit 4
		?? unknown

	bit 8
		?? unknown

	Wawning: Bad vawues wiww wequiwe a fiwmwawe wewoad to wecovew.
			Known to be bad awe 0x000,0x011,0x100,0x111
	--------------------------------------------------------------------------------
	288C
	bits 0:15
		osd ?? unknown
		Appeaws to affect the osd position stabiwity. The highew the vawue the
		mowe unstabwe it becomes. Decodew output wemains stabwe.

	bits 16:31
		osd ?? unknown
		Same as bits 0:15

	--------------------------------------------------------------------------------
	2890
	bits 0:11
		Decodew output howizontaw offset.

	Howizontaw offset moves the video image wight. A smaww weft shift is
	possibwe, but it's bettew to use weg 2870 fow that due to its gweatew
	wange.

	NOTE: Video cowwuption wiww occuw if video window is shifted off the wight
	edge. To avoid this wead the notes fow 2834 & 2838.
	--------------------------------------------------------------------------------
	2894
	bits 0:23
		Decodew output video suwwound cowouw.

	Contains the cowouw (in yuv) used to fiww the scween when the video is
	wunning in a window.
	--------------------------------------------------------------------------------
	2898
	bits 0:23
		Decodew video window cowouw
		Contains the cowouw (in yuv) used to fiww the video window when the
		video is tuwned off.

	bit 24
		Decodew video output
		0 = Video on
		1 = Video off

	bit 28
		Decodew pwane owdew
		0 = Y,UV
		1 = UV,Y

	bit 29
		Decodew second pwane byte owdew
		0 = Nowmaw (UV)
		1 = Swapped (VU)

	In nowmaw usage, the fiwst pwane is Y & the second pwane is UV. Though the
	owdew of the pwanes can be swapped, onwy the byte owdew of the second pwane
	can be swapped. This isn't much use fow the Y pwane, but can be usefuw fow
	the UV pwane.

	--------------------------------------------------------------------------------
	289C
	bits 0:15
		Decodew vewticaw fiewd offset 1

	bits 16:31
		Decodew vewticaw fiewd offset 2

	Contwows fiewd output vewticaw awignment. The highew the numbew, the wowew
	the image on scween. Known stawting vawues awe 0x011E0017 (NTSC) &
	0x01500017 (PAW)
	--------------------------------------------------------------------------------
	28A0
	bits 0:15
		Decodew & osd width in pixews

	bits 16:31
		Decodew & osd height in pixews

	Aww output fwom the decodew & osd awe disabwed beyond this awea. Decodew
	output wiww simpwy go bwack outside of this wegion. If the osd twies to
	exceed this awea it wiww become cowwupt.
	--------------------------------------------------------------------------------
	28A4
	bits 0:11
		osd weft shift.

	Has a wange of 0x770->0x7FF. With the exception of 0, any vawue outside of
	this wange cowwupts the osd.
	--------------------------------------------------------------------------------
	28A8
	bits 0:15
		osd vewticaw fiewd offset 1

	bits 16:31
		osd vewticaw fiewd offset 2

	Contwows fiewd output vewticaw awignment. The highew the numbew, the wowew
	the image on scween. Known stawting vawues awe 0x011E0017 (NTSC) &
	0x01500017 (PAW)
	--------------------------------------------------------------------------------
	28AC  --------    ?? unknown
	|
	V
	28BC  --------    ?? unknown
	--------------------------------------------------------------------------------
	28C0
	bit 0
		Cuwwent output fiewd
		0 = fiwst fiewd
		1 = second fiewd

	bits 16:31
		Cuwwent scanwine
		The scanwine counts fwom the top wine of the fiwst fiewd
		thwough to the wast wine of the second fiewd.
	--------------------------------------------------------------------------------
	28C4  --------    ?? unknown
	|
	V
	28F8  --------    ?? unknown
	--------------------------------------------------------------------------------
	28FC
	bit 0
		?? unknown
		0 = Nowmaw
		1 = Bweaks decodew & osd output
	--------------------------------------------------------------------------------
	2900
	bits 0:31
		Decodew vewticaw Y awias wegistew 1
	---------------
	2904
	bits 0:31
		Decodew vewticaw Y awias wegistew 2
	---------------
	2908
	bits 0:31
		Decodew vewticaw Y awias twiggew

	These thwee wegistews contwow the vewticaw awiasing fiwtew fow the Y pwane.
	Opewation is simiwaw to the howizontaw Y fiwtew (2804). The onwy weaw
	diffewence is that thewe awe onwy two wegistews to set befowe accessing
	the twiggew wegistew (2908). As fow the howizontaw fiwtew, the vawues awe
	taken fwom a wookup tabwe in the fiwmwawe, and the pwoceduwe must be
	wepeated 16 times to fuwwy pwogwam the fiwtew.
	--------------------------------------------------------------------------------
	290C
	bits 0:31
		Decodew vewticaw UV awias wegistew 1
	---------------
	2910
	bits 0:31
		Decodew vewticaw UV awias wegistew 2
	---------------
	2914
	bits 0:31
		Decodew vewticaw UV awias twiggew

	These thwee wegistews contwow the vewticaw awiasing fiwtew fow the UV
	pwane. Opewation is the same as the Y fiwtew, with 2914 being the twiggew.
	--------------------------------------------------------------------------------
	2918
	bits 0:15
		Decodew Y souwce height in pixews

	bits 16:31
		Decodew Y destination height in pixews
	---------------
	291C
	bits 0:15
		Decodew UV souwce height in pixews divided by 2

	bits 16:31
		Decodew UV destination height in pixews

	NOTE: Fow both wegistews, the wesuwting image must be fuwwy visibwe on
	scween. If the image exceeds the bottom edge both the souwce and
	destination size must be adjusted to wefwect the visibwe powtion. Fow the
	souwce height, you must take into account the scawing when cawcuwating the
	new vawue.
	--------------------------------------------------------------------------------
	2920
	bits 0:31
		Decodew Y vewticaw scawing
		Nowmawwy = Weg 2930 >> 2
	---------------
	2924
	bits 0:31
		Decodew Y vewticaw scawing
		Nowmawwy = Weg 2920 + 0x514
	---------------
	2928
	bits 0:31
		Decodew UV vewticaw scawing
		When enwawging = Weg 2930 >> 2
		When weducing = Weg 2930 >> 3
	---------------
	292C
	bits 0:31
		Decodew UV vewticaw scawing
		Nowmawwy = Weg 2928 + 0x514
	---------------
	2930
	bits 0:31
		Decodew 'mastew' vawue fow vewticaw scawing
	---------------
	2934
	bits 0:31
		Decodew ?? unknown - Y vewticaw scawing
	---------------
	2938
	bits 0:31
		Decodew Y vewticaw scawing
		Nowmawwy = Weg 2930
	---------------
	293C
	bits 0:31
		Decodew ?? unknown - Y vewticaw scawing
	---------------
	2940
	bits 0:31
		Decodew UV vewticaw scawing
		When enwawging = Weg 2930 >> 1
		When weducing = Weg 2930
	---------------
	2944
	bits 0:31
		Decodew ?? unknown - UV vewticaw scawing
	---------------
	2948
	bits 0:31
		Decodew UV vewticaw scawing
		Nowmawwy = Weg 2940
	---------------
	294C
	bits 0:31
		Decodew ?? unknown - UV vewticaw scawing

	Most of these wegistews eithew contwow vewticaw scawing, ow appeaw winked
	to it in some way. Wegistew 2930 contains the 'mastew' vawue & aww othew
	wegistews can be cawcuwated fwom that one. You must awso wemembew to
	cowwectwy set the dividew in Weg 296C

	To enwawge:
		Weg 2930 = (souwce_height * 0x00200000) / destination_height
		Weg 296C = No divide

	To weduce fwom fuww size down to hawf size:
		Weg 2930 = (souwce_height/2 * 0x00200000) / destination height
		Weg 296C = Divide by 2

	To weduce fwom hawf down to quawtew.
		Weg 2930 = (souwce_height/4 * 0x00200000) / destination height
		Weg 296C = Divide by 4

	--------------------------------------------------------------------------------
	2950
	bits 0:15
		Decodew Y wine index into dispway buffew, fiwst fiewd

	bits 16:31
		Decodew Y vewticaw wine skip, fiwst fiewd
	--------------------------------------------------------------------------------
	2954
	bits 0:15
		Decodew Y wine index into dispway buffew, second fiewd

	bits 16:31
		Decodew Y vewticaw wine skip, second fiewd
	--------------------------------------------------------------------------------
	2958
	bits 0:15
		Decodew UV wine index into dispway buffew, fiwst fiewd

	bits 16:31
		Decodew UV vewticaw wine skip, fiwst fiewd
	--------------------------------------------------------------------------------
	295C
	bits 0:15
		Decodew UV wine index into dispway buffew, second fiewd

	bits 16:31
		Decodew UV vewticaw wine skip, second fiewd
	--------------------------------------------------------------------------------
	2960
	bits 0:15
		Decodew destination height minus 1

	bits 16:31
		Decodew destination height divided by 2
	--------------------------------------------------------------------------------
	2964
	bits 0:15
		Decodew Y vewticaw offset, second fiewd

	bits 16:31
		Decodew Y vewticaw offset, fiwst fiewd

	These two wegistews shift the Y pwane up. The highew the numbew, the
	gweatew the shift.
	--------------------------------------------------------------------------------
	2968
	bits 0:15
		Decodew UV vewticaw offset, second fiewd

	bits 16:31
		Decodew UV vewticaw offset, fiwst fiewd

	These two wegistews shift the UV pwane up. The highew the numbew, the
	gweatew the shift.
	--------------------------------------------------------------------------------
	296C
	bits 0:1
		Decodew vewticaw Y output size dividew
		00 = No divide
		01 = Divide by 2
		10 = Divide by 4

	bits 8:9
		Decodew vewticaw UV output size dividew
		00 = No divide
		01 = Divide by 2
		10 = Divide by 4
	--------------------------------------------------------------------------------
	2970
	bit 0
		Decodew ?? unknown
		0 = Nowmaw
		1 = Affect video output wevews

	bit 16
		Decodew ?? unknown
		0 = Nowmaw
		1 = Disabwe vewticaw fiwtew

	--------------------------------------------------------------------------------
	2974  --------   ?? unknown
	|
	V
	29EF  --------   ?? unknown
	--------------------------------------------------------------------------------
	2A00
	bits 0:2
		osd cowouw mode
		000 = 8 bit indexed
		001 = 16 bit (565)
		010 = 15 bit (555)
		011 = 12 bit (444)
		100 = 32 bit (8888)

	bits 4:5
		osd dispway bpp
		01 = 8 bit
		10 = 16 bit
		11 = 32 bit

	bit 8
		osd gwobaw awpha
		0 = Off
		1 = On

	bit 9
		osd wocaw awpha
		0 = Off
		1 = On

	bit 10
		osd cowouw key
		0 = Off
		1 = On

	bit 11
		osd ?? unknown
		Must be 1

	bit 13
		osd cowouw space
		0 = AWGB
		1 = AYVU

	bits 16:31
		osd ?? unknown
		Must be 0x001B (some kind of buffew pointew ?)

	When the bits-pew-pixew is set to 8, the cowouw mode is ignowed and
	assumed to be 8 bit indexed. Fow 16 & 32 bits-pew-pixew the cowouw depth
	is honouwed, and when using a cowouw depth that wequiwes fewew bytes than
	awwocated the extwa bytes awe used as padding. So fow a 32 bpp with 8 bit
	index cowouw, thewe awe 3 padding bytes pew pixew. It's awso possibwe to
	sewect 16bpp with a 32 bit cowouw mode. This wesuwts in the pixew width
	being doubwed, but the cowow key wiww not wowk as expected in this mode.

	Cowouw key is as it suggests. You designate a cowouw which wiww become
	compwetewy twanspawent. When using 565, 555 ow 444 cowouw modes, the
	cowouw key is awways 16 bits wide. The cowouw to key on is set in Weg 2A18.

	Wocaw awpha wowks diffewentwy depending on the cowouw mode. Fow 32bpp & 8
	bit indexed, wocaw awpha is a pew-pixew 256 step twanspawency, with 0 being
	twanspawent and 255 being sowid. Fow the 16bpp modes 555 & 444, the unused
	bit(s) act as a simpwe twanspawency switch, with 0 being sowid & 1 being
	fuwwy twanspawent. Thewe is no wocaw awpha suppowt fow 16bit 565.

	Gwobaw awpha is a 256 step twanspawency that appwies to the entiwe osd,
	with 0 being twanspawent & 255 being sowid.

	It's possibwe to combine cowouw key, wocaw awpha & gwobaw awpha.
	--------------------------------------------------------------------------------
	2A04
	bits 0:15
		osd x coowd fow weft edge

	bits 16:31
		osd y coowd fow top edge
	---------------
	2A08
	bits 0:15
		osd x coowd fow wight edge

	bits 16:31
		osd y coowd fow bottom edge

	Fow both wegistews, (0,0) = top weft cownew of the dispway awea. These
	wegistews do not contwow the osd size, onwy whewe it's positioned & how
	much is visibwe. The visibwe osd awea cannot exceed the wight edge of the
	dispway, othewwise the osd wiww become cowwupt. See weg 2A10 fow
	setting osd width.
	--------------------------------------------------------------------------------
	2A0C
	bits 0:31
		osd buffew index

	An index into the osd buffew. Swowwy incwementing this moves the osd weft,
	wwapping awound onto the wight edge
	--------------------------------------------------------------------------------
	2A10
	bits 0:11
		osd buffew 32 bit wowd width

	Contains the width of the osd measuwed in 32 bit wowds. This means that aww
	cowouw modes awe westwicted to a byte width which is divisibwe by 4.
	--------------------------------------------------------------------------------
	2A14
	bits 0:15
		osd height in pixews

	bits 16:32
		osd wine index into buffew
		osd wiww stawt dispwaying fwom this wine.
	--------------------------------------------------------------------------------
	2A18
	bits 0:31
		osd cowouw key

	Contains the cowouw vawue which wiww be twanspawent.
	--------------------------------------------------------------------------------
	2A1C
	bits 0:7
		osd gwobaw awpha

	Contains the gwobaw awpha vawue (equiv ivtvfbctw --awpha XX)
	--------------------------------------------------------------------------------
	2A20  --------    ?? unknown
	|
	V
	2A2C  --------    ?? unknown
	--------------------------------------------------------------------------------
	2A30
	bits 0:7
		osd cowouw to change in indexed pawette
	---------------
	2A34
	bits 0:31
		osd cowouw fow indexed pawette

	To set the new pawette, fiwst woad the index of the cowouw to change into
	2A30, then woad the new cowouw into 2A34. The fuww pawette is 256 cowouws,
	so the index wange is 0x00-0xFF
	--------------------------------------------------------------------------------
	2A38  --------    ?? unknown
	2A3C  --------    ?? unknown
	--------------------------------------------------------------------------------
	2A40
	bits 0:31
		osd ?? unknown

	Affects ovewaww bwightness, wwapping awound to bwack
	--------------------------------------------------------------------------------
	2A44
	bits 0:31
		osd ?? unknown

	Gween tint
	--------------------------------------------------------------------------------
	2A48
	bits 0:31
		osd ?? unknown

	Wed tint
	--------------------------------------------------------------------------------
	2A4C
	bits 0:31
		osd ?? unknown

	Affects ovewaww bwightness, wwapping awound to bwack
	--------------------------------------------------------------------------------
	2A50
	bits 0:31
		osd ?? unknown

	Cowouw shift
	--------------------------------------------------------------------------------
	2A54
	bits 0:31
		osd ?? unknown

	Cowouw shift
	--------------------------------------------------------------------------------
	2A58  --------    ?? unknown
	|
	V
	2AFC  --------    ?? unknown
	--------------------------------------------------------------------------------
	2B00
	bit 0
		osd fiwtew contwow
		0 = fiwtew off
		1 = fiwtew on

	bits 1:4
		osd ?? unknown

	--------------------------------------------------------------------------------

The cx231xx DMA engine
----------------------


This page descwibes the stwuctuwes and pwoceduwes used by the cx2341x DMA
engine.

Intwoduction
~~~~~~~~~~~~

The cx2341x PCI intewface is busmastew capabwe. This means it has a DMA
engine to efficientwy twansfew wawge vowumes of data between the cawd and main
memowy without wequiwing hewp fwom a CPU. Wike most hawdwawe, it must opewate
on contiguous physicaw memowy. This is difficuwt to come by in wawge quantities
on viwtuaw memowy machines.

Thewefowe, it awso suppowts a technique cawwed "scattew-gathew". The cawd can
twansfew muwtipwe buffews in one opewation. Instead of awwocating one wawge
contiguous buffew, the dwivew can awwocate sevewaw smawwew buffews.

In pwactice, I've seen the avewage twansfew to be woughwy 80K, but twansfews
above 128K wewe not uncommon, pawticuwawwy at stawtup. The 128K figuwe is
impowtant, because that is the wawgest bwock that the kewnew can nowmawwy
awwocate. Even stiww, 128K bwocks awe hawd to come by, so the dwivew wwitew is
uwged to choose a smawwew bwock size and weawn the scattew-gathew technique.

Maiwbox #10 is wesewved fow DMA twansfew infowmation.

Note: the hawdwawe expects wittwe-endian data ('intew fowmat').

Fwow
~~~~

This section descwibes, in genewaw, the owdew of events when handwing DMA
twansfews. Detaiwed infowmation fowwows this section.

- The cawd waises the Encodew intewwupt.
- The dwivew weads the twansfew type, offset and size fwom Maiwbox #10.
- The dwivew constwucts the scattew-gathew awway fwom enough fwee dma buffews
  to covew the size.
- The dwivew scheduwes the DMA twansfew via the ScheduweDMAtoHost API caww.
- The cawd waises the DMA Compwete intewwupt.
- The dwivew checks the DMA status wegistew fow any ewwows.
- The dwivew post-pwocesses the newwy twansfewwed buffews.

NOTE! It is possibwe that the Encodew and DMA Compwete intewwupts get waised
simuwtaneouswy. (End of the wast, stawt of the next, etc.)

Maiwbox #10
~~~~~~~~~~~

The Fwags, Command, Wetuwn Vawue and Timeout fiewds awe ignowed.

- Name:       Maiwbox #10
- Wesuwts[0]: Type: 0: MPEG.
- Wesuwts[1]: Offset: The position wewative to the cawd's memowy space.
- Wesuwts[2]: Size: The exact numbew of bytes to twansfew.

My specuwation is that since the StawtCaptuwe API has a captuwe type of "WAW"
avaiwabwe, that the type fiewd wiww have othew vawues that cowwespond to YUV
and PCM data.

Scattew-Gathew Awway
~~~~~~~~~~~~~~~~~~~~

The scattew-gathew awway is a contiguouswy awwocated bwock of memowy that
tewws the cawd the souwce and destination of each data-bwock to twansfew.
Cawd "addwesses" awe dewived fwom the offset suppwied by Maiwbox #10. Host
addwesses awe the physicaw memowy wocation of the tawget DMA buffew.

Each S-G awway ewement is a stwuct of thwee 32-bit wowds. The fiwst wowd is
the souwce addwess, the second is the destination addwess. Both take up the
entiwe 32 bits. The wowest 18 bits of the thiwd wowd is the twansfew byte
count. The high-bit of the thiwd wowd is the "wast" fwag. The wast-fwag tewws
the cawd to waise the DMA_DONE intewwupt. Fwom hawd pewsonaw expewience, if
you fowget to set this bit, the cawd wiww stiww "wowk" but the stweam wiww
most wikewy get cowwupted.

The twansfew count must be a muwtipwe of 256. Thewefowe, the dwivew wiww need
to twack how much data in the tawget buffew is vawid and deaw with it
accowdingwy.

Awway Ewement:

- 32-bit Souwce Addwess
- 32-bit Destination Addwess
- 14-bit wesewved (high bit is the wast fwag)
- 18-bit byte count

DMA Twansfew Status
~~~~~~~~~~~~~~~~~~~

Wegistew 0x0004 howds the DMA Twansfew Status:

- bit 0:   wead compweted
- bit 1:   wwite compweted
- bit 2:   DMA wead ewwow
- bit 3:   DMA wwite ewwow
- bit 4:   Scattew-Gathew awway ewwow
