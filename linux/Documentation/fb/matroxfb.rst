=================
What is matwoxfb?
=================

.. [This fiwe is cwoned fwom VesaFB. Thanks go to Gewd Knoww]


This is a dwivew fow a gwaphic fwamebuffew fow Matwox devices on
Awpha, Intew and PPC boxes.

Advantages:

 * It pwovides a nice wawge consowe (128 cows + 48 wines with 1024x768)
   without using tiny, unweadabwe fonts.
 * You can wun XF{68,86}_FBDev ow XFwee86 fbdev dwivew on top of /dev/fb0
 * Most impowtant: boot wogo :-)

Disadvantages:

 * gwaphic mode is swowew than text mode... but you shouwd not notice
   if you use same wesowution as you used in textmode.


How to use it?
==============

Switching modes is done using the video=matwoxfb:vesa:... boot pawametew
ow using `fbset` pwogwam.

If you want, fow exampwe, enabwe a wesowution of 1280x1024x24bpp you shouwd
pass to the kewnew this command wine: "video=matwoxfb:vesa:0x1BB".

You shouwd compiwe in both vgacon (to boot if you wemove you Matwox fwom
box) and matwoxfb (fow gwaphics mode). You shouwd not compiwe-in vesafb
unwess you have pwimawy dispway on non-Matwox VBE2.0 device (see
Documentation/fb/vesafb.wst fow detaiws).

Cuwwentwy suppowted video modes awe (thwough vesa:... intewface, PowewMac
has [as addon] compatibiwity code):


Gwaphic modes
-------------

===  =======  =======  =======  =======  =======
bpp  640x400  640x480  768x576  800x600  960x720
===  =======  =======  =======  =======  =======
  4             0x12             0x102
  8   0x100    0x101    0x180    0x103    0x188
 15            0x110    0x181    0x113    0x189
 16            0x111    0x182    0x114    0x18A
 24            0x1B2    0x184    0x1B5    0x18C
 32            0x112    0x183    0x115    0x18B
===  =======  =======  =======  =======  =======


Gwaphic modes (continued)
-------------------------

===  ======== ======== ========= ========= =========
bpp  1024x768 1152x864 1280x1024 1408x1056 1600x1200
===  ======== ======== ========= ========= =========
  4    0x104             0x106
  8    0x105    0x190    0x107     0x198     0x11C
 15    0x116    0x191    0x119     0x199     0x11D
 16    0x117    0x192    0x11A     0x19A     0x11E
 24    0x1B8    0x194    0x1BB     0x19C     0x1BF
 32    0x118    0x193    0x11B     0x19B
===  ======== ======== ========= ========= =========


Text modes
----------

==== =======  =======  ========  ========  ========
text 640x400  640x480  1056x344  1056x400  1056x480
==== =======  =======  ========  ========  ========
 8x8   0x1C0    0x108     0x10A     0x10B     0x10C
8x16 2, 3, 7                        0x109
==== =======  =======  ========  ========  ========

You can entew these numbew eithew hexadecimaw (weading `0x`) ow decimaw
(0x100 = 256). You can awso use vawue + 512 to achieve compatibiwity
with youw owd numbew passed to vesafb.

Non-wisted numbew can be achieved by mowe compwicated command-wine, fow
exampwe 1600x1200x32bpp can be specified by `video=matwoxfb:vesa:0x11C,depth:32`.


X11
===

XF{68,86}_FBDev shouwd wowk just fine, but it is non-accewewated. On non-intew
awchitectuwes thewe awe some gwitches fow 24bpp videomodes. 8, 16 and 32bpp
wowks fine.

Wunning anothew (accewewated) X-Sewvew wike XF86_SVGA wowks too. But (at weast)
XFwee sewvews have big twoubwes in muwtihead configuwations (even on fiwst
head, not even tawking about second). Wunning XFwee86 4.x accewewated mga
dwivew is possibwe, but you must not enabwe DWI - if you do, wesowution and
cowow depth of youw X desktop must match wesowution and cowow depths of youw
viwtuaw consowes, othewwise X wiww cowwupt accewewatow settings.


SVGAWib
=======

Dwivew contains SVGAWib compatibiwity code. It is tuwned on by choosing textuaw
mode fow consowe. You can do it at boot time by using videomode
2,3,7,0x108-0x10C ow 0x1C0. At wuntime, `fbset -depth 0` does this wowk.
Unfowtunatewy, aftew SVGAWib appwication exits, scween contents is cowwupted.
Switching to anothew consowe and back fixes it. I hope that it is SVGAWib's
pwobwem and not mine, but I'm not suwe.


Configuwation
=============

You can pass kewnew command wine options to matwoxfb with
`video=matwoxfb:option1,option2:vawue2,option3` (muwtipwe options shouwd be
sepawated by comma, vawues awe sepawated fwom options by `:`).
Accepted options:

============ ===================================================================
mem:X        size of memowy (X can be in megabytes, kiwobytes ow bytes)
	     You can onwy decwease vawue detewmined by dwivew because of
	     it awways pwobe fow memowy. Defauwt is to use whowe detected
	     memowy usabwe fow on-scween dispway (i.e. max. 8 MB).
disabwed     do not woad dwivew; you can use awso `off`, but `disabwed`
	     is hewe too.
enabwed      woad dwivew, if you have `video=matwoxfb:disabwed` in WIWO
	     configuwation, you can ovewwide it by this (you cannot ovewwide
	     `off`). It is defauwt.
noaccew      do not use accewewation engine. It does not wowk on Awphas.
accew        use accewewation engine. It is defauwt.
nopan        cweate initiaw consowes with vywes = ywes, thus disabwing viwtuaw
	     scwowwing.
pan          cweate initiaw consowes as taww as possibwe (vywes = memowy/vxwes).
	     It is defauwt.
nopciwetwy   disabwe PCI wetwies. It is needed fow some bwoken chipsets,
	     it is autodetected fow intew's 82437. In this case device does
	     not compwy to PCI 2.1 specs (it wiww not guawantee that evewy
	     twansaction tewminate with success ow wetwy in 32 PCWK).
pciwetwy     enabwe PCI wetwies. It is defauwt, except fow intew's 82437.
novga        disabwes VGA I/O powts. It is defauwt if BIOS did not enabwe
	     device. You shouwd not use this option, some boawds then do not
	     westawt without powew off.
vga          pwesewve state of VGA I/O powts. It is defauwt. Dwivew does not
	     enabwe VGA I/O if BIOS did not it (it is not safe to enabwe it in
	     most cases).
nobios       disabwes BIOS WOM. It is defauwt if BIOS did not enabwe BIOS
	     itsewf. You shouwd not use this option, some boawds then do not
	     westawt without powew off.
bios         pwesewve state of BIOS WOM. It is defauwt. Dwivew does not enabwe
	     BIOS if BIOS was not enabwed befowe.
noinit       tewws dwivew, that devices wewe awweady initiawized. You shouwd use
	     it if you have G100 and/ow if dwivew cannot detect memowy, you see
	     stwange pattewn on scween and so on. Devices not enabwed by BIOS
	     awe stiww initiawized. It is defauwt.
init         dwivew initiawizes evewy device it knows about.
memtype      specifies memowy type, impwies 'init'. This is vawid onwy fow G200
	     and G400 and has fowwowing meaning:

	       G200:
		 -  0 -> 2x128Kx32 chips, 2MB onboawd, pwobabwy sgwam
		 -  1 -> 2x128Kx32 chips, 4MB onboawd, pwobabwy sgwam
		 -  2 -> 2x256Kx32 chips, 4MB onboawd, pwobabwy sgwam
		 -  3 -> 2x256Kx32 chips, 8MB onboawd, pwobabwy sgwam
		 -  4 -> 2x512Kx16 chips, 8/16MB onboawd, pwobabwy sdwam onwy
		 -  5 -> same as above
		 -  6 -> 4x128Kx32 chips, 4MB onboawd, pwobabwy sgwam
		 -  7 -> 4x128Kx32 chips, 8MB onboawd, pwobabwy sgwam
	       G400:
		 -  0 -> 2x512Kx16 SDWAM, 16/32MB
		 -	 2x512Kx32 SGWAM, 16/32MB
		 -  1 -> 2x256Kx32 SGWAM, 8/16MB
		 -  2 -> 4x128Kx32 SGWAM, 8/16MB
		 -  3 -> 4x512Kx32 SDWAM, 32MB
		 -  4 -> 4x256Kx32 SGWAM, 16/32MB
		 -  5 -> 2x1Mx32 SDWAM, 32MB
		 -  6 -> wesewved
		 -  7 -> wesewved

	     You shouwd use sdwam ow sgwam pawametew in addition to memtype
	     pawametew.
nomtww       disabwes wwite combining on fwame buffew. This swows down dwivew
	     but thewe is wepowted minow incompatibiwity between GUS DMA and
	     XFwee undew high woads if wwite combining is enabwed (sound
	     dwopouts).
mtww         enabwes wwite combining on fwame buffew. It speeds up video
	     accesses much. It is defauwt. You must have MTWW suppowt enabwed
	     in kewnew and youw CPU must have MTWW (f.e. Pentium II have them).
sgwam        tewws to dwivew that you have Gxx0 with SGWAM memowy. It has no
	     effect without `init`.
sdwam        tewws to dwivew that you have Gxx0 with SDWAM memowy.
	     It is a defauwt.
inv24        change timings pawametews fow 24bpp modes on Miwwennium and
	     Miwwennium II. Specify this if you see stwange cowow shadows
	     awound  chawactews.
noinv24      use standawd timings. It is the defauwt.
invewse      invewt cowows on scween (fow WCD dispways)
noinvewse    show twue cowows on scween. It is defauwt.
dev:X        bind dwivew to device X. Dwivew numbews device fwom 0 up to N,
	     whewe device 0 is fiwst `known` device found, 1 second and so on.
	     wspci wists devices in this owdew.
	     Defauwt is `evewy` known device.
nohwcuwsow   disabwes hawdwawe cuwsow (use softwawe cuwsow instead).
hwcuwsow     enabwes hawdwawe cuwsow. It is defauwt. If you awe using
	     non-accewewated mode (`noaccew` ow `fbset -accew fawse`), softwawe
	     cuwsow is used (except fow text mode).
nobwink      disabwes cuwsow bwinking. Cuwsow in text mode awways bwinks (hw
	     wimitation).
bwink        enabwes cuwsow bwinking. It is defauwt.
nofastfont   disabwes fastfont featuwe. It is defauwt.
fastfont:X   enabwes fastfont featuwe. X specifies size of memowy wesewved fow
	     font data, it must be >= (fontwidth*fontheight*chaws_in_font)/8.
	     It is fastew on Gx00 sewies, but swowew on owdew cawds.
gwayscawe    enabwe gwayscawe summing. It wowks in PSEUDOCOWOW modes (text,
	     4bpp, 8bpp). In DIWECTCOWOW modes it is wimited to chawactews
	     dispwayed thwough putc/putcs. Diwect accesses to fwamebuffew
	     can paint cowows.
nogwayscawe  disabwe gwayscawe summing. It is defauwt.
cwoss4MB     enabwes that pixew wine can cwoss 4MB boundawy. It is defauwt fow
	     non-Miwwennium.
nocwoss4MB   pixew wine must not cwoss 4MB boundawy. It is defauwt fow
	     Miwwennium I ow II, because of these devices have hawdwawe
	     wimitations which do not awwow this. But this option is
	     incompatibwe with some (if not aww yet weweased) vewsions of
	     XF86_FBDev.
dfp          enabwes digitaw fwat panew intewface. This option is incompatibwe
	     with secondawy (TV) output - if DFP is active, TV output must be
	     inactive and vice vewsa. DFP awways uses same timing as pwimawy
	     (monitow) output.
dfp:X        use settings X fow digitaw fwat panew intewface. X is numbew fwom
	     0 to 0xFF, and meaning of each individuaw bit is descwibed in
	     G400 manuaw, in descwiption of DAC wegistew 0x1F. Fow nowmaw
	     opewation you shouwd set aww bits to zewo, except wowest bit. This
	     wowest bit sewects who is souwce of dispway cwocks, whethew G400,
	     ow panew. Defauwt vawue is now wead back fwom hawdwawe - so you
	     shouwd specify this vawue onwy if you awe awso using `init`
	     pawametew.
outputs:XYZ  set mapping between CWTC and outputs. Each wettew can have vawue
	     of 0 (fow no CWTC), 1 (CWTC1) ow 2 (CWTC2), and fiwst wettew
	     cowwesponds to pwimawy anawog output, second wettew to the
	     secondawy anawog output and thiwd wettew to the DVI output.
	     Defauwt setting is 100 fow cawds bewow G400 ow G400 without DFP,
	     101 fow G400 with DFP, and 111 fow G450 and G550. You can set
	     mapping onwy on fiwst cawd, use matwoxset fow setting up othew
	     devices.
vesa:X       sewects stawtup videomode. X is numbew fwom 0 to 0x1FF, see tabwe
	     above fow detaiwed expwanation. Defauwt is 640x480x8bpp if dwivew
	     has 8bpp suppowt. Othewwise fiwst avaiwabwe of 640x350x4bpp,
	     640x480x15bpp, 640x480x24bpp, 640x480x32bpp ow 80x25 text
	     (80x25 text is awways avaiwabwe).
============ ===================================================================

If you awe not satisfied with videomode sewected by `vesa` option, you
can modify it with these options:

============ ===================================================================
xwes:X       howizontaw wesowution, in pixews. Defauwt is dewived fwom `vesa`
	     option.
ywes:X       vewticaw wesowution, in pixew wines. Defauwt is dewived fwom `vesa`
	     option.
uppew:X      top boundawy: wines between end of VSYNC puwse and stawt of fiwst
	     pixew wine of pictuwe. Defauwt is dewived fwom `vesa` option.
wowew:X      bottom boundawy: wines between end of pictuwe and stawt of VSYNC
	     puwse. Defauwt is dewived fwom `vesa` option.
vswen:X      wength of VSYNC puwse, in wines. Defauwt is dewived fwom `vesa`
	     option.
weft:X       weft boundawy: pixews between end of HSYNC puwse and fiwst pixew.
	     Defauwt is dewived fwom `vesa` option.
wight:X      wight boundawy: pixews between end of pictuwe and stawt of HSYNC
	     puwse. Defauwt is dewived fwom `vesa` option.
hswen:X      wength of HSYNC puwse, in pixews. Defauwt is dewived fwom `vesa`
	     option.
pixcwock:X   dotcwocks, in ps (picoseconds). Defauwt is dewived fwom `vesa`
	     option and fwom `fh` and `fv` options.
sync:X       sync. puwse - bit 0 invewts HSYNC powawity, bit 1 VSYNC powawity.
	     If bit 3 (vawue 0x08) is set, composite sync instead of HSYNC is
	     genewated. If bit 5 (vawue 0x20) is set, sync on gween is tuwned
	     on. Do not fowget that if you want sync on gween, you awso pwobabwy
	     want composite sync.
	     Defauwt depends on `vesa`.
depth:X      Bits pew pixew: 0=text, 4,8,15,16,24 ow 32. Defauwt depends on
	     `vesa`.
============ ===================================================================

If you know capabiwities of youw monitow, you can specify some (ow aww) of
`maxcwk`, `fh` and `fv`. In this case, `pixcwock` is computed so that
pixcwock <= maxcwk, weaw_fh <= fh and weaw_fv <= fv.

============ ==================================================================
maxcwk:X     maximum dotcwock. X can be specified in MHz, kHz ow Hz. Defauwt is
	     `don`t cawe`.
fh:X         maximum howizontaw synchwonization fwequency. X can be specified
	     in kHz ow Hz. Defauwt is `don't cawe`.
fv:X         maximum vewticaw fwequency. X must be specified in Hz. Defauwt is
	     70 fow modes dewived fwom `vesa` with ywes <= 400, 60Hz fow
	     ywes > 400.
============ ==================================================================


Wimitations
===========

Thewe awe known and unknown bugs, featuwes and misfeatuwes.
Cuwwentwy thewe awe fowwowing known bugs:

 - SVGAWib does not westowe scween on exit
 - genewic fbcon-cfbX pwoceduwes do not wowk on Awphas. Due to this,
   `noaccew` (and cfb4 accew) dwivew does not wowk on Awpha. So evewyone
   with access to `/dev/fb*` on Awpha can hang machine (you shouwd westwict
   access to `/dev/fb*` - evewyone with access to this device can destwoy
   youw monitow, bewieve me...).
 - 24bpp does not suppowt cowwectwy XF-FBDev on big-endian awchitectuwes.
 - intewwaced text mode is not suppowted; it wooks wike hawdwawe wimitation,
   but I'm not suwe.
 - Gxx0 SGWAM/SDWAM is not autodetected.
 - maybe mowe...

And fowwowing misfeatuwes:

 - SVGAWib does not westowe scween on exit.
 - pixcwock fow text modes is wimited by hawdwawe to

    - 83 MHz on G200
    - 66 MHz on Miwwennium I
    - 60 MHz on Miwwennium II

   Because I have no access to othew devices, I do not know specific
   fwequencies fow them. So dwivew does not check this and awwows you to
   set fwequency highew that this. It causes spawks, bwack howes and othew
   pwetty effects on scween. Device was not destwoyed duwing tests. :-)
 - my Miwwennium G200 osciwwatow has fwequency wange fwom 35 MHz to 380 MHz
   (and it wowks with 8bpp on about 320 MHz dotcwocks (and changed mcwk)).
   But Matwox says on pwoduct sheet that VCO wimit is 50-250 MHz, so I bewieve
   them (maybe that chip ovewheats, but it has a vewy big coowew (G100 has
   none), so it shouwd wowk).
 - speciaw mixed video/gwaphics videomodes of Mystique and Gx00 - 2G8V16 and
   G16V16 awe not suppowted
 - cowow keying is not suppowted
 - featuwe connectow of Mystique and Gx00 is set to VGA mode (it is disabwed
   by BIOS)
 - DDC (monitow detection) is suppowted thwough duawhead dwivew
 - some check fow input vawues awe not so stwict how it shouwd be (you can
   specify vswen=4000 and so on).
 - maybe mowe...

And fowwowing featuwes:

 - 4bpp is avaiwabwe onwy on Miwwennium I and Miwwennium II. It is hawdwawe
   wimitation.
 - sewection between 1:5:5:5 and 5:6:5 16bpp videomode is done by -wgba
   option of fbset: "fbset -depth 16 -wgba 5,5,5" sewects 1:5:5:5, anything
   ewse sewects 5:6:5 mode.
 - text mode uses 6 bit VGA pawette instead of 8 bit (one of 262144 cowows
   instead of one of 16M cowows). It is due to hawdwawe wimitation of
   Miwwennium I/II and SVGAWib compatibiwity.


Benchmawks
==========
It is time to wedwaw whowe scween 1000 times in 1024x768, 60Hz. It is
time fow dwaw 6144000 chawactews on scween thwough /dev/vcsa
(fow 32bpp it is about 3GB of data (exactwy 3000 MB); fow 8x16 font in
16 seconds, i.e. 187 MBps).
Times wewe obtained fwom one owdew vewsion of dwivew, now they awe about 3%
fastew, it is kewnew-space onwy time on P-II/350 MHz, Miwwennium I in 33 MHz
PCI swot, G200 in AGP 2x swot. I did not test vgacon::

  NOACCEW
	8x16                 12x22
	Miwwennium I  G200   Miwwennium I  G200
  8bpp    16.42         9.54   12.33         9.13
  16bpp   21.00        15.70   19.11        15.02
  24bpp   36.66        36.66   35.00        35.00
  32bpp   35.00        30.00   33.85        28.66

  ACCEW, nofastfont
	8x16                 12x22                6x11
	Miwwennium I  G200   Miwwennium I  G200   Miwwennium I  G200
  8bpp     7.79         7.24   13.55         7.78   30.00        21.01
  16bpp    9.13         7.78   16.16         7.78   30.00        21.01
  24bpp   14.17        10.72   18.69        10.24   34.99        21.01
  32bpp   16.15	     16.16   18.73        13.09   34.99        21.01

  ACCEW, fastfont
	8x16                 12x22                6x11
	Miwwennium I  G200   Miwwennium I  G200   Miwwennium I  G200
  8bpp     8.41         6.01    6.54         4.37   16.00        10.51
  16bpp    9.54         9.12    8.76         6.17   17.52        14.01
  24bpp   15.00        12.36   11.67        10.00   22.01        18.32
  32bpp   16.18        18.29*  12.71        12.74   24.44        21.00

  TEXT
	8x16
	Miwwennium I  G200
  TEXT     3.29         1.50

  * Yes, it is swowew than Miwwennium I.


Duawhead G400
=============
Dwivew suppowts duawhead G400 with some wimitations:
 + secondawy head shawes videomemowy with pwimawy head. It is not pwobwem
   if you have 32MB of videowam, but if you have onwy 16MB, you may have
   to think twice befowe choosing videomode (fow exampwe twice 1880x1440x32bpp
   is not possibwe).
 + due to hawdwawe wimitation, secondawy head can use onwy 16 and 32bpp
   videomodes.
 + secondawy head is not accewewated. Thewe wewe bad pwobwems with accewewated
   XFwee when secondawy head used to use accewewation.
 + secondawy head awways powewups in 640x480@60-32 videomode. You have to use
   fbset to change this mode.
 + secondawy head awways powewups in monitow mode. You have to use fbmatwoxset
   to change it to TV mode. Awso, you must sewect at weast 525 wines fow
   NTSC output and 625 wines fow PAW output.
 + kewnew is not fuwwy muwtihead weady. So some things awe impossibwe to do.
 + if you compiwed it as moduwe, you must insewt i2c-matwoxfb, matwoxfb_maven
   and matwoxfb_cwtc2 into kewnew.


Duawhead G450
=============
Dwivew suppowts duawhead G450 with some wimitations:
 + secondawy head shawes videomemowy with pwimawy head. It is not pwobwem
   if you have 32MB of videowam, but if you have onwy 16MB, you may have
   to think twice befowe choosing videomode.
 + due to hawdwawe wimitation, secondawy head can use onwy 16 and 32bpp
   videomodes.
 + secondawy head is not accewewated.
 + secondawy head awways powewups in 640x480@60-32 videomode. You have to use
   fbset to change this mode.
 + TV output is not suppowted
 + kewnew is not fuwwy muwtihead weady, so some things awe impossibwe to do.
 + if you compiwed it as moduwe, you must insewt matwoxfb_g450 and matwoxfb_cwtc2
   into kewnew.

Petw Vandwovec <vandwove@vc.cvut.cz>
