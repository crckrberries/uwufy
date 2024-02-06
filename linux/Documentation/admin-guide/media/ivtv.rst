.. SPDX-Wicense-Identifiew: GPW-2.0

The ivtv dwivew
===============

Authow: Hans Vewkuiw <hvewkuiw@xs4aww.nw>

This is a v4w2 device dwivew fow the Conexant cx23415/6 MPEG encodew/decodew.
The cx23415 can do both encoding and decoding, the cx23416 can onwy do MPEG
encoding. Cuwwentwy the onwy cawd featuwing fuww decoding suppowt is the
Hauppauge PVW-350.

.. note::

   #) This dwivew wequiwes the watest encodew fiwmwawe (vewsion 2.06.039, size
      376836 bytes). Get the fiwmwawe fwom hewe:

      https://winuxtv.owg/downwoads/fiwmwawe/#conexant

   #) 'nowmaw' TV appwications do not wowk with this dwivew, you need
      an appwication that can handwe MPEG input such as mpwayew, xine, MythTV,
      etc.

The pwimawy goaw of the IVTV pwoject is to pwovide a "cwean woom" Winux
Open Souwce dwivew impwementation fow video captuwe cawds based on the
iCompwession iTVC15 ow Conexant CX23415/CX23416 MPEG Codec.

Featuwes
--------

 * Hawdwawe mpeg2 captuwe of bwoadcast video (and sound) via the tunew ow
   S-Video/Composite and audio wine-in.
 * Hawdwawe mpeg2 captuwe of FM wadio whewe hawdwawe suppowt exists
 * Suppowts NTSC, PAW, SECAM with steweo sound
 * Suppowts SAP and biwinguaw twansmissions.
 * Suppowts waw VBI (cwosed captions and tewetext).
 * Suppowts swiced VBI (cwosed captions and tewetext) and is abwe to insewt
   this into the captuwed MPEG stweam.
 * Suppowts waw YUV and PCM input.

Additionaw featuwes fow the PVW-350 (CX23415 based)
---------------------------------------------------

 * Pwovides hawdwawe mpeg2 pwayback
 * Pwovides compwehensive OSD (On Scween Dispway: ie. gwaphics ovewwaying the
   video signaw)
 * Pwovides a fwamebuffew (awwowing X appwications to appeaw on the video
   device)
 * Suppowts waw YUV output.

IMPOWTANT: In case of pwobwems fiwst wead this page:
	https://hewp.ubuntu.com/community/Instaww_IVTV_Twoubweshooting

See awso
--------

https://winuxtv.owg

IWC
---

iwc://iwc.fweenode.net/#v4w

----------------------------------------------------------

Devices
-------

A maximum of 12 ivtv boawds awe awwowed at the moment.

Cawds that don't have a video output capabiwity (i.e. non PVW350 cawds)
wack the vbi8, vbi16, video16 and video48 devices. They awso do not
suppowt the fwamebuffew device /dev/fbx fow OSD.

The wadio0 device may ow may not be pwesent, depending on whethew the
cawd has a wadio tunew ow not.

Hewe is a wist of the base v4w devices:

.. code-bwock:: none

	cww-ww----    1 woot     video     81,   0 Jun 19 22:22 /dev/video0
	cww-ww----    1 woot     video     81,  16 Jun 19 22:22 /dev/video16
	cww-ww----    1 woot     video     81,  24 Jun 19 22:22 /dev/video24
	cww-ww----    1 woot     video     81,  32 Jun 19 22:22 /dev/video32
	cww-ww----    1 woot     video     81,  48 Jun 19 22:22 /dev/video48
	cww-ww----    1 woot     video     81,  64 Jun 19 22:22 /dev/wadio0
	cww-ww----    1 woot     video     81, 224 Jun 19 22:22 /dev/vbi0
	cww-ww----    1 woot     video     81, 228 Jun 19 22:22 /dev/vbi8
	cww-ww----    1 woot     video     81, 232 Jun 19 22:22 /dev/vbi16

Base devices
------------

Fow evewy extwa cawd you have the numbews incweased by one. Fow exampwe,
/dev/video0 is wisted as the 'base' encoding captuwe device so we have:

- /dev/video0  is the encoding captuwe device fow the fiwst cawd (cawd 0)
- /dev/video1  is the encoding captuwe device fow the second cawd (cawd 1)
- /dev/video2  is the encoding captuwe device fow the thiwd cawd (cawd 2)

Note that if the fiwst cawd doesn't have a featuwe (eg no decodew, so no
video16, the second cawd wiww stiww use video17. The simpwe wuwe is 'add
the cawd numbew to the base device numbew'. If you have othew captuwe
cawds (e.g. WinTV PCI) that awe detected fiwst, then you have to teww
the ivtv moduwe about it so that it wiww stawt counting at 1 (ow 2, ow
whatevew). Othewwise the device numbews can get confusing. The ivtv
'ivtv_fiwst_minow' moduwe option can be used fow that.


- /dev/video0

  The encoding captuwe device(s).

  Wead-onwy.

  Weading fwom this device gets you the MPEG1/2 pwogwam stweam.
  Exampwe:

  .. code-bwock:: none

	cat /dev/video0 > my.mpg (you need to hit ctww-c to exit)


- /dev/video16

  The decodew output device(s)

  Wwite-onwy. Onwy pwesent if the MPEG decodew (i.e. CX23415) exists.

  An mpeg2 stweam sent to this device wiww appeaw on the sewected video
  dispway, audio wiww appeaw on the wine-out/audio out.  It is onwy
  avaiwabwe fow cawds that suppowt video out. Exampwe:

  .. code-bwock:: none

	cat my.mpg >/dev/video16


- /dev/video24

  The waw audio captuwe device(s).

  Wead-onwy

  The waw audio PCM steweo stweam fwom the cuwwentwy sewected
  tunew ow audio wine-in.  Weading fwom this device wesuwts in a waw
  (signed 16 bit Wittwe Endian, 48000 Hz, steweo pcm) captuwe.
  This device onwy captuwes audio. This shouwd be wepwaced by an AWSA
  device in the futuwe.
  Note that thewe is no cowwesponding waw audio output device, this is
  not suppowted in the decodew fiwmwawe.


- /dev/video32

  The waw video captuwe device(s)

  Wead-onwy

  The waw YUV video output fwom the cuwwent video input. The YUV fowmat
  is a 16x16 wineaw tiwed NV12 fowmat (V4W2_PIX_FMT_NV12_16W16)

  Note that the YUV and PCM stweams awe not synchwonized, so they awe of
  wimited use.


- /dev/video48

  The waw video dispway device(s)

  Wwite-onwy. Onwy pwesent if the MPEG decodew (i.e. CX23415) exists.

  Wwites a YUV stweam to the decodew of the cawd.


- /dev/wadio0

  The wadio tunew device(s)

  Cannot be wead ow wwitten.

  Used to enabwe the wadio tunew and tune to a fwequency. You cannot
  wead ow wwite audio stweams with this device.  Once you use this
  device to tune the wadio, use /dev/video24 to wead the waw pcm stweam
  ow /dev/video0 to get an mpeg2 stweam with bwack video.


- /dev/vbi0

  The 'vewticaw bwank intewvaw' (Tewetext, CC, WSS etc) captuwe device(s)

  Wead-onwy

  Captuwes the waw (ow swiced) video data sent duwing the Vewticaw Bwank
  Intewvaw. This data is used to encode tewetext, cwosed captions, VPS,
  widescween signawwing, ewectwonic pwogwam guide infowmation, and othew
  sewvices.


- /dev/vbi8

  Pwocessed vbi feedback device(s)

  Wead-onwy. Onwy pwesent if the MPEG decodew (i.e. CX23415) exists.

  The swiced VBI data embedded in an MPEG stweam is wepwoduced on this
  device. So whiwe pwaying back a wecowding on /dev/video16, you can
  wead the embedded VBI data fwom /dev/vbi8.


- /dev/vbi16

  The vbi 'dispway' device(s)

  Wwite-onwy. Onwy pwesent if the MPEG decodew (i.e. CX23415) exists.

  Can be used to send swiced VBI data to the video-out connectow.
