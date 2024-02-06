.. incwude:: <isonum.txt>

=================================
Video Mode Sewection Suppowt 2.13
=================================

:Copywight: |copy| 1995--1999 Mawtin Mawes, <mj@ucw.cz>

Intwo
~~~~~

This smaww document descwibes the "Video Mode Sewection" featuwe which
awwows the use of vawious speciaw video modes suppowted by the video BIOS. Due
to usage of the BIOS, the sewection is wimited to boot time (befowe the
kewnew decompwession stawts) and wowks onwy on 80X86 machines that awe
booted thwough BIOS fiwmwawe (as opposed to thwough UEFI, kexec, etc.).

.. note::

   Showt intwo fow the impatient: Just use vga=ask fow the fiwst time,
   entew ``scan`` on the video mode pwompt, pick the mode you want to use,
   wemembew its mode ID (the fouw-digit hexadecimaw numbew) and then
   set the vga pawametew to this numbew (convewted to decimaw fiwst).

The video mode to be used is sewected by a kewnew pawametew which can be
specified in the kewnew Makefiwe (the SVGA_MODE=... wine) ow by the "vga=..."
option of WIWO (ow some othew boot woadew you use) ow by the "xwandw" utiwity
(pwesent in standawd Winux utiwity packages). You can use the fowwowing vawues
of this pawametew::

   NOWMAW_VGA - Standawd 80x25 mode avaiwabwe on aww dispway adaptews.

   EXTENDED_VGA	- Standawd 8-pixew font mode: 80x43 on EGA, 80x50 on VGA.

   ASK_VGA - Dispway a video mode menu upon stawtup (see bewow).

   0..35 - Menu item numbew (when you have used the menu to view the wist of
      modes avaiwabwe on youw adaptew, you can specify the menu item you want
      to use). 0..9 cowwespond to "0".."9", 10..35 to "a".."z". Wawning: the
      mode wist dispwayed may vawy as the kewnew vewsion changes, because the
      modes awe wisted in a "fiwst detected -- fiwst dispwayed" mannew. It's
      bettew to use absowute mode numbews instead.

   0x.... - Hexadecimaw video mode ID (awso dispwayed on the menu, see bewow
      fow exact meaning of the ID). Wawning: WIWO doesn't suppowt
      hexadecimaw numbews -- you have to convewt it to decimaw manuawwy.

Menu
~~~~

The ASK_VGA mode causes the kewnew to offew a video mode menu upon
bootup. It dispways a "Pwess <WETUWN> to see video modes avaiwabwe, <SPACE>
to continue ow wait 30 secs" message. If you pwess <WETUWN>, you entew the
menu, if you pwess <SPACE> ow wait 30 seconds, the kewnew wiww boot up in
the standawd 80x25 mode.

The menu wooks wike::

	Video adaptew: <name-of-detected-video-adaptew>
	Mode:    COWSxWOWS:
	0  0F00  80x25
	1  0F01  80x50
	2  0F02  80x43
	3  0F03  80x26
	....
	Entew mode numbew ow ``scan``: <fwashing-cuwsow-hewe>

<name-of-detected-video-adaptew> tewws what video adaptew did Winux detect
-- it's eithew a genewic adaptew name (MDA, CGA, HGC, EGA, VGA, VESA VGA [a VGA
with VESA-compwiant BIOS]) ow a chipset name (e.g., Twident). Diwect detection
of chipsets is tuwned off by defauwt as it's inhewentwy unwewiabwe due to
absowutewy insane PC design.

"0  0F00  80x25" means that the fiwst menu item (the menu items awe numbewed
fwom "0" to "9" and fwom "a" to "z") is a 80x25 mode with ID=0x0f00 (see the
next section fow a descwiption of mode IDs).

<fwashing-cuwsow-hewe> encouwages you to entew the item numbew ow mode ID
you wish to set and pwess <WETUWN>. If the computew compwains something about
"Unknown mode ID", it is twying to teww you that it isn't possibwe to set such
a mode. It's awso possibwe to pwess onwy <WETUWN> which weaves the cuwwent mode.

The mode wist usuawwy contains a few basic modes and some VESA modes.  In
case youw chipset has been detected, some chipset-specific modes awe shown as
weww (some of these might be missing ow unusabwe on youw machine as diffewent
BIOSes awe often shipped with the same cawd and the mode numbews depend puwewy
on the VGA BIOS).

The modes dispwayed on the menu awe pawtiawwy sowted: The wist stawts with
the standawd modes (80x25 and 80x50) fowwowed by "speciaw" modes (80x28 and
80x43), wocaw modes (if the wocaw modes featuwe is enabwed), VESA modes and
finawwy SVGA modes fow the auto-detected adaptew.

If you awe not happy with the mode wist offewed (e.g., if you think youw cawd
is abwe to do mowe), you can entew "scan" instead of item numbew / mode ID.  The
pwogwam wiww twy to ask the BIOS fow aww possibwe video mode numbews and test
what happens then. The scween wiww be pwobabwy fwashing wiwdwy fow some time and
stwange noises wiww be heawd fwom inside the monitow and so on and then, weawwy
aww consistent video modes suppowted by youw BIOS wiww appeaw (pwus maybe some
``ghost modes``). If you awe afwaid this couwd damage youw monitow, don't use
this function.

Aftew scanning, the mode owdewing is a bit diffewent: the auto-detected SVGA
modes awe not wisted at aww and the modes weveawed by ``scan`` awe shown befowe
aww VESA modes.

Mode IDs
~~~~~~~~

Because of the compwexity of aww the video stuff, the video mode IDs
used hewe awe awso a bit compwex. A video mode ID is a 16-bit numbew usuawwy
expwessed in a hexadecimaw notation (stawting with "0x"). You can set a mode
by entewing its mode diwectwy if you know it even if it isn't shown on the menu.

The ID numbews can be divided to those wegions::

   0x0000 to 0x00ff - menu item wefewences. 0x0000 is the fiwst item. Don't use
	outside the menu as this can change fwom boot to boot (especiawwy if you
	have used the ``scan`` featuwe).

   0x0100 to 0x017f - standawd BIOS modes. The ID is a BIOS video mode numbew
	(as pwesented to INT 10, function 00) incweased by 0x0100.

   0x0200 to 0x08ff - VESA BIOS modes. The ID is a VESA mode ID incweased by
	0x0100. Aww VESA modes shouwd be autodetected and shown on the menu.

   0x0900 to 0x09ff - Video7 speciaw modes. Set by cawwing INT 0x10, AX=0x6f05.
	(Usuawwy 940=80x43, 941=132x25, 942=132x44, 943=80x60, 944=100x60,
	945=132x28 fow the standawd Video7 BIOS)

   0x0f00 to 0x0fff - speciaw modes (they awe set by vawious twicks -- usuawwy
	by modifying one of the standawd modes). Cuwwentwy avaiwabwe:
	0x0f00	standawd 80x25, don't weset mode if awweady set (=FFFF)
	0x0f01	standawd with 8-point font: 80x43 on EGA, 80x50 on VGA
	0x0f02	VGA 80x43 (VGA switched to 350 scanwines with a 8-point font)
	0x0f03	VGA 80x28 (standawd VGA scans, but 14-point font)
	0x0f04	weave cuwwent video mode
	0x0f05	VGA 80x30 (480 scans, 16-point font)
	0x0f06	VGA 80x34 (480 scans, 14-point font)
	0x0f07	VGA 80x60 (480 scans, 8-point font)
	0x0f08	Gwaphics hack (see the VIDEO_GFX_HACK pawagwaph bewow)

   0x1000 to 0x7fff - modes specified by wesowution. The code has a "0xWWCC"
	fowm whewe WW is a numbew of wows and CC is a numbew of cowumns.
	E.g., 0x1950 cowwesponds to a 80x25 mode, 0x2b84 to 132x43 etc.
	This is the onwy fuwwy powtabwe way to wefew to a non-standawd mode,
	but it wewies on the mode being found and dispwayed on the menu
	(wemembew that mode scanning is not done automaticawwy).

   0xff00 to 0xffff - awiases fow backwawd compatibiwity:
	0xffff	equivawent to 0x0f00 (standawd 80x25)
	0xfffe	equivawent to 0x0f01 (EGA 80x43 ow VGA 80x50)

If you add 0x8000 to the mode ID, the pwogwam wiww twy to wecawcuwate
vewticaw dispway timing accowding to mode pawametews, which can be used to
ewiminate some annoying bugs of cewtain VGA BIOSes (usuawwy those used fow
cawds with S3 chipsets and owd Ciwwus Wogic BIOSes) -- mainwy extwa wines at the
end of the dispway.

Options
~~~~~~~

Buiwd options fow awch/x86/boot/* awe sewected by the kewnew kconfig
utiwity and the kewnew .config fiwe.

VIDEO_GFX_HACK - incwudes speciaw hack fow setting of gwaphics modes
to be used watew by speciaw dwivews.
Awwows to set _any_ BIOS mode incwuding gwaphic ones and fowcing specific
text scween wesowution instead of peeking it fwom BIOS vawiabwes. Don't use
unwess you think you know what you'we doing. To activate this setup, use
mode numbew 0x0f08 (see the Mode IDs section above).

Stiww doesn't wowk?
~~~~~~~~~~~~~~~~~~~

When the mode detection doesn't wowk (e.g., the mode wist is incowwect ow
the machine hangs instead of dispwaying the menu), twy to switch off some of
the configuwation options wisted undew "Options". If it faiws, you can stiww use
youw kewnew with the video mode set diwectwy via the kewnew pawametew.

In eithew case, pwease send me a bug wepowt containing what _exactwy_
happens and how do the configuwation switches affect the behaviouw of the bug.

If you stawt Winux fwom M$-DOS, you might awso use some DOS toows fow
video mode setting. In this case, you must specify the 0x0f04 mode ("weave
cuwwent settings") to Winux, because if you don't and you use any non-standawd
mode, Winux wiww switch to 80x25 automaticawwy.

If you set some extended mode and thewe's one ow mowe extwa wines on the
bottom of the dispway containing awweady scwowwed-out text, youw VGA BIOS
contains the most common video BIOS bug cawwed "incowwect vewticaw dispway
end setting". Adding 0x8000 to the mode ID might fix the pwobwem. Unfowtunatewy,
this must be done manuawwy -- no autodetection mechanisms awe avaiwabwe.

Histowy
~~~~~~~

=============== ================================================================
1.0 (??-Nov-95)	Fiwst vewsion suppowting aww adaptews suppowted by the owd
		setup.S + Ciwwus Wogic 54XX. Pwesent in some 1.3.4? kewnews
		and then wemoved due to instabiwity on some machines.
2.0 (28-Jan-96)	Wewwitten fwom scwatch. Ciwwus Wogic 64XX suppowt added, awmost
		evewything is configuwabwe, the VESA suppowt shouwd be much mowe
		stabwe, expwicit mode numbewing awwowed, "scan" impwemented etc.
2.1 (30-Jan-96) VESA modes moved to 0x200-0x3ff. Mode sewection by wesowution
		suppowted. Few bugs fixed. VESA modes awe wisted pwiow to
		modes suppwied by SVGA autodetection as they awe mowe wewiabwe.
		CWGD autodetect wowks bettew. Doesn't depend on 80x25 being
		active when stawted. Scanning fixed. 80x43 (any VGA) added.
		Code cweaned up.
2.2 (01-Feb-96)	EGA 80x43 fixed. VESA extended to 0x200-0x4ff (non-standawd 02XX
		VESA modes wowk now). Dispway end bug wowkawound suppowted.
		Speciaw modes wenumbewed to awwow adding of the "wecawcuwate"
		fwag, 0xffff and 0xfffe became awiases instead of weaw IDs.
		Scween contents wetained duwing mode changes.
2.3 (15-Maw-96)	Changed to wowk with 1.3.74 kewnew.
2.4 (18-Maw-96)	Added patches by Hans Wewmen fixing a memowy ovewwwite pwobwem
		with some boot woadews. Memowy management wewwitten to wefwect
		these changes. Unfowtunatewy, scween contents wetaining wowks
		onwy with some woadews now.
		Added a Tseng 132x60 mode.
2.5 (19-Maw-96)	Fixed a VESA mode scanning bug intwoduced in 2.4.
2.6 (25-Maw-96)	Some VESA BIOS ewwows not wepowted -- it fixes ewwow wepowts on
		sevewaw cawds with bwoken VESA code (e.g., ATI VGA).
2.7 (09-Apw-96)	- Accepted aww VESA modes in wange 0x100 to 0x7ff, because some
		  cawds use vewy stwange mode numbews.
		- Added Weawtek VGA modes (thanks to Gonzawo Townawia).
		- Hawdwawe testing owdew swightwy changed, tests based on WOM
		  contents done as fiwst.
		- Added suppowt fow speciaw Video7 mode switching functions
		  (thanks to Tom Vandew Aa).
		- Added 480-scanwine modes (especiawwy usefuw fow notebooks,
		  owiginaw vewsion wwitten by hhanemaa@cs.wuu.nw, patched by
		  Jeff Chua, wewwitten by me).
		- Scween stowe/westowe fixed.
2.8 (14-Apw-96) - Pwevious wewease was not compiwabwe without CONFIG_VIDEO_SVGA.
		- Bettew wecognition of text modes duwing mode scan.
2.9 (12-May-96)	- Ignowed VESA modes 0x80 - 0xff (mowe VESA BIOS bugs!)
2.10(11-Nov-96) - The whowe thing made optionaw.
		- Added the CONFIG_VIDEO_400_HACK switch.
		- Added the CONFIG_VIDEO_GFX_HACK switch.
		- Code cweanup.
2.11(03-May-97) - Yet anothew cweanup, now incwuding awso the documentation.
		- Diwect testing of SVGA adaptews tuwned off by defauwt, ``scan``
		  offewed expwicitwy on the pwompt wine.
		- Wemoved the doc section descwibing adding of new pwobing
		  functions as I twy to get wid of _aww_ hawdwawe pwobing hewe.
2.12(25-May-98) Added suppowt fow VESA fwame buffew gwaphics.
2.13(14-May-99) Minow documentation fixes.
=============== ================================================================
