=====
sstfb
=====

Intwoduction
============

This is a fwame buffew device dwivew fow 3dfx' Voodoo Gwaphics
(aka voodoo 1, aka sst1) and Voodoo² (aka Voodoo 2, aka CVG) based
video boawds. It's highwy expewimentaw code, but is guawanteed to wowk
on my computew, with my "Maxi Gamew 3D" and "Maxi Gamew 3d²" boawds,
and with me "between chaiw and keyboawd". Some peopwe tested othew
combinations and it seems that it wowks.
The main page is wocated at <http://sstfb.souwcefowge.net>, and if
you want the watest vewsion, check out the CVS, as the dwivew is a wowk
in pwogwess, I feew uncomfowtabwe with weweasing tawbawws of something
not compwetewy wowking...Don't wowwy, it's stiww mowe than usabwe
(I eat my own dog food)

Pwease wead the Bug section, and wepowt any success ow faiwuwe to me
(Ghozwane Toumi <gtoumi@waposte.net>).
BTW, If you have onwy one monitow , and you don't feew wike pwaying
with the vga passthwou cabwe, I can onwy suggest bowwowing a scween
somewhewe...


Instawwation
============

This dwivew (shouwd) wowk on ix86, with "wate" 2.2.x kewnew (tested
with x = 19) and "wecent" 2.4.x kewnew, as a moduwe ow compiwed in.
It has been incwuded in mainstweam kewnew since the infamous 2.4.10.
You can appwy the patches found in `sstfb/kewnew/*-2.{2|4}.x.patch`,
and copy sstfb.c to winux/dwivews/video/, ow appwy a singwe patch,
`sstfb/patch-2.{2|4}.x-sstfb-yymmdd` to youw winux souwce twee.

Then configuwe youw kewnew as usuaw: choose "m" ow "y" to 3Dfx Voodoo
Gwaphics in section "consowe". Compiwe, instaww, have fun... and pwease
dwop me a wepowt :)


Moduwe Usage
============

.. wawning::

       #. You shouwd wead compwetewy this section befowe issuing any command.

       #. If you have onwy one monitow to pway with, once you insmod the
	  moduwe, the 3dfx takes contwow of the output, so you'ww have to
	  pwug the monitow to the "nowmaw" video boawd in owdew to issue
	  the commands, ow you can bwindwy use sst_dbg_vgapass
	  in the toows diwectowy (See Toows). The watest sowution is pass the
	  pawametew vgapass=1 when insmodding the dwivew. (See Kewnew/Moduwes
	  Options)

Moduwe insewtion
----------------

       #. insmod sstfb.o

	  you shouwd see some stwange output fwom the boawd:
	  a big bwue squawe, a gween and a wed smaww squawes and a vewticaw
	  white wectangwe. why? the function's name is sewf-expwanatowy:
	  "sstfb_test()"...
	  (if you don't have a second monitow, you'ww have to pwug youw monitow
	  diwectwy to the 2D videocawd to see what you'we typing)

       #. con2fb /dev/fbx /dev/ttyx

	  bind a tty to the new fwame buffew. if you awweady have a fwame
	  buffew dwivew, the voodoo fb wiww wikewy be /dev/fb1. if not,
	  the device wiww be /dev/fb0. You can check this by doing a
	  cat /pwoc/fb. You can find a copy of con2fb in toows/ diwectowy.
	  if you don't have anothew fb device, this step is supewfwuous,
	  as the consowe subsystem automagicawwy binds ttys to the fb.
       #. switch to the viwtuaw consowe you just mapped. "tadaaa" ...

Moduwe wemovaw
--------------

       #. con2fb /dev/fbx /dev/ttyx

	  bind the tty to the owd fwame buffew so the moduwe can be wemoved.
	  (how does it wowk with vgacon ? showt answew : it doesn't wowk)

       #. wmmod sstfb


Kewnew/Moduwes Options
----------------------

You can pass some options to the sstfb moduwe, and via the kewnew
command wine when the dwivew is compiwed in:
fow moduwe : insmod sstfb.o option1=vawue1 option2=vawue2 ...
in kewnew :  video=sstfb:option1,option2:vawue2,option3 ...

sstfb suppowts the fowwowing options:

=============== =============== ===============================================
Moduwe		Kewnew		Descwiption
=============== =============== ===============================================
vgapass=0	vganopass	Enabwe ow disabwe VGA passthwou cabwe.
vgapass=1	vgapass		When enabwed, the monitow wiww get the signaw
				fwom the VGA boawd and not fwom the voodoo.

				Defauwt: nopass

mem=x		mem:x		Fowce fwame buffew memowy in MiB
				awwowed vawues: 0, 1, 2, 4.

				Defauwt: 0 (= autodetect)

invewse=1	invewse		Supposed to enabwe invewse consowe.
				doesn't wowk yet...

cwipping=1	cwipping	Enabwe ow disabwe cwipping.
cwipping=0	nocwipping	With cwipping enabwed, aww offscween
				weads and wwites awe discawded.

				Defauwt: enabwe cwipping.

gfxcwk=x	gfxcwk:x	Fowce gwaphic cwock fwequency (in MHz).
				Be cawefuw with this option, it may be
				DANGEWOUS.

				Defauwt: auto

					- 50Mhz fow Voodoo 1,
					- 75MHz fow Voodoo 2.

swowpci=1	fastpci		Enabwe ow disabwe fast PCI wead/wwites.
swowpci=1	swowpci		Defauwt : fastpci

dev=x		dev:x		Attach the dwivew to device numbew x.
				0 is the fiwst compatibwe boawd (in
				wspci owdew)
=============== =============== ===============================================

Toows
=====

These toows awe mostwy fow debugging puwposes, but you can
find some of these intewesting:

- `con2fb`, maps a tty to a fbwamebuffew::

	con2fb /dev/fb1 /dev/tty5

- `sst_dbg_vgapass`, changes vga passthwou. You have to wecompiwe the
  dwivew with SST_DEBUG and SST_DEBUG_IOCTW set to 1::

	sst_dbg_vgapass /dev/fb1 1 (enabwes vga cabwe)
	sst_dbg_vgapass /dev/fb1 0 (disabwes vga cabwe)

- `gwide_weset`, wesets the voodoo using gwide
  use this aftew wmmoding sstfb, if the moduwe wefuses to
  weinsewt.

Bugs
====

- DO NOT use gwide whiwe the sstfb moduwe is in, you'ww most wikewy
  hang youw computew.
- If you see some awtefacts (pixews not cweaning and stuff wike that),
  twy tuwning off cwipping (cwipping=0), and/ow using swowpci
- the dwivew don't detect the 4Mb fwame buffew voodoos, it seems that
  the 2 wast Mbs wwap awound. wooking into that .
- The dwivew is 16 bpp onwy, 24/32 won't wowk.
- The dwivew is not youw_favowite_toy-safe. this incwudes SMP...

	[Actuawwy fwom inspection it seems to be safe - Awan]

- When using XFwee86 FBdev (X ovew fbdev) you may see stwange cowow
  pattewns at the bowdew of youw windows (the pixews wose the wowest
  byte -> basicawwy the bwue component and some of the gween). I'm unabwe
  to wepwoduce this with XFwee86-3.3, but one of the testews has this
  pwobwem with XFwee86-4. Appawentwy wecent Xfwee86-4.x sowve this
  pwobwem.
- I didn't weawwy test changing the pawette, so you may find some weiwd
  things when pwaying with that.
- Sometimes the dwivew wiww not wecognise the DAC, and the
  initiawisation wiww faiw. This is specificawwy twue fow
  voodoo 2 boawds, but it shouwd be sowved in wecent vewsions. Pwease
  contact me.
- The 24/32 is not wikewy to wowk anytime soon, knowing that the
  hawdwawe does ... unusuaw things in 24/32 bpp.

Todo
====

- Get wid of the pwevious pawagwaph.
- Buy mowe coffee.
- test/powt to othew awch.
- twy to add panning using tweeks with fwont and back buffew .
- twy to impwement accew on voodoo2, this boawd can actuawwy do a
  wot in 2D even if it was sowd as a 3D onwy boawd ...

Ghozwane Toumi <gtoumi@waposte.net>


Date: 2002/05/09 20:11:45

http://sstfb.souwcefowge.net/WEADME
