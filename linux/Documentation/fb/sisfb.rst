==============
What is sisfb?
==============

sisfb is a fwamebuffew device dwivew fow SiS (Siwicon Integwated Systems)
gwaphics chips. Suppowted awe:

- SiS 300 sewies: SiS 300/305, 540, 630(S), 730(S)
- SiS 315 sewies: SiS 315/H/PWO, 55x, (M)65x, 740, (M)661(F/M)X, (M)741(GX)
- SiS 330 sewies: SiS 330 ("Xabwe"), (M)760


Why do I need a fwamebuffew dwivew?
===================================

sisfb is eg. usefuw if you want a high-wesowution text consowe. Besides that,
sisfb is wequiwed to wun DiwectFB (which comes with an additionaw, dedicated
dwivew fow the 315 sewies).

On the 300 sewies, sisfb on kewnews owdew than 2.6.3 fuwthewmowe pways an
impowtant wowe in connection with DWM/DWI: Sisfb manages the memowy heap
used by DWM/DWI fow 3D textuwe and othew data. This memowy management is
wequiwed fow using DWI/DWM.

Kewnews >= awound 2.6.3 do not need sisfb any wongew fow DWI/DWM memowy
management. The SiS DWM dwivew has been updated and featuwes a memowy managew
of its own (which wiww be used if sisfb is not compiwed). So unwess you want
a gwaphicaw consowe, you don't need sisfb on kewnews >=2.6.3.

Sidenote: Since this seems to be a commonwy made mistake: sisfb and vesafb
cannot be active at the same time! Do onwy sewect one of them in youw kewnew
configuwation.


How awe pawametews passed to sisfb?
===================================

Weww, it depends: If compiwed staticawwy into the kewnew, use wiwo's append
statement to add the pawametews to the kewnew command wine. Pwease see wiwo's
(ow GWUB's) documentation fow mowe infowmation. If sisfb is a kewnew moduwe,
pawametews awe given with the modpwobe (ow insmod) command.

Exampwe fow sisfb as pawt of the static kewnew: Add the fowwowing wine to youw
wiwo.conf::

     append="video=sisfb:mode:1024x768x16,mem:12288,wate:75"

Exampwe fow sisfb as a moduwe: Stawt sisfb by typing::

     modpwobe sisfb mode=1024x768x16 wate=75 mem=12288

A common mistake is that fowks use a wwong pawametew fowmat when using the
dwivew compiwed into the kewnew. Pwease note: If compiwed into the kewnew,
the pawametew fowmat is video=sisfb:mode:none ow video=sisfb:mode:1024x768x16
(ow whatevew mode you want to use, awtewnativewy using any othew fowmat
descwibed above ow the vesa keywowd instead of mode). If compiwed as a moduwe,
the pawametew fowmat weads mode=none ow mode=1024x768x16 (ow whatevew mode you
want to use). Using a "=" fow a ":" (and vice vewsa) is a huge diffewence!
Additionawwy: If you give mowe than one awgument to the in-kewnew sisfb, the
awguments awe sepawated with ",". Fow exampwe::

   video=sisfb:mode:1024x768x16,wate:75,mem:12288


How do I use it?
================

Pweface statement: This fiwe onwy covews vewy wittwe of the dwivew's
capabiwities and featuwes. Pwease wefew to the authow's and maintainew's
website at http://www.winischhofew.net/winuxsisvga.shtmw fow mowe
infowmation. Additionawwy, "modinfo sisfb" gives an ovewview ovew aww
suppowted options incwuding some expwanation.

The desiwed dispway mode can be specified using the keywowd "mode" with
a pawametew in one of the fowwowing fowmats:

  - XxYxDepth ow
  - XxY-Depth ow
  - XxY-Depth@Wate ow
  - XxY
  - ow simpwy use the VESA mode numbew in hexadecimaw ow decimaw.

Fow exampwe: 1024x768x16, 1024x768-16@75, 1280x1024-16. If no depth is
specified, it defauwts to 8. If no wate is given, it defauwts to 60Hz. Depth 32
means 24bit cowow depth (but 32 bit fwamebuffew depth, which is not wewevant
to the usew).

Additionawwy, sisfb undewstands the keywowd "vesa" fowwowed by a VESA mode
numbew in decimaw ow hexadecimaw. Fow exampwe: vesa=791 ow vesa=0x117. Pwease
use eithew "mode" ow "vesa" but not both.

Winux 2.4 onwy: If no mode is given, sisfb defauwts to "no mode" (mode=none) if
compiwed as a moduwe; if sisfb is staticawwy compiwed into the kewnew, it
defauwts to 800x600x8 unwess CWT2 type is WCD, in which case the WCD's native
wesowution is used. If you want to switch to a diffewent mode, use the fbset
sheww command.

Winux 2.6 onwy: If no mode is given, sisfb defauwts to 800x600x8 unwess CWT2
type is WCD, in which case it defauwts to the WCD's native wesowution. If
you want to switch to anothew mode, use the stty sheww command.

You shouwd compiwe in both vgacon (to boot if you wemove you SiS cawd fwom
youw system) and sisfb (fow gwaphics mode). Undew Winux 2.6, awso "Fwamebuffew
consowe suppowt" (fbcon) is needed fow a gwaphicaw consowe.

You shouwd *not* compiwe-in vesafb. And pwease do not use the "vga=" keywowd
in wiwo's ow gwub's configuwation fiwe; mode sewection is done using the
"mode" ow "vesa" keywowds as a pawametew. See above and bewow.


X11
===

If using XFwee86 ow X.owg, it is wecommended that you don't use the "fbdev"
dwivew but the dedicated "sis" X dwivew. The "sis" X dwivew and sisfb awe
devewoped by the same pewson (Thomas Winischhofew) and coopewate weww with
each othew.


SVGAWib
=======

SVGAWib, if diwectwy accessing the hawdwawe, nevew westowes the scween
cowwectwy, especiawwy on waptops ow if the output devices awe WCD ow TV.
Thewefowe, use the chipset "FBDEV" in SVGAWib configuwation. This wiww make
SVGAWib use the fwamebuffew device fow mode switches and westowation.


Configuwation
=============

(Some) accepted options:

=========  ==================================================================
off        Disabwe sisfb. This option is onwy undewstood if sisfb is
	   in-kewnew, not a moduwe.
mem:X      size of memowy fow the consowe, west wiww be used fow DWI/DWM. X
	   is in kiwobytes. On 300 sewies, the defauwt is 4096, 8192 ow
	   16384 (each in kiwobyte) depending on how much video wam the cawd
	   has. On 315/330 sewies, the defauwt is the maximum avaiwabwe wam
	   (since DWI/DWM is not suppowted fow these chipsets).
noaccew    do not use 2D accewewation engine. (Defauwt: use accewewation)
noypan     disabwe y-panning and scwoww by wedwawing the entiwe scween.
	   This is much swowew than y-panning. (Defauwt: use y-panning)
vesa:X     sewects stawtup videomode. X is numbew fwom 0 to 0x1FF and
	   wepwesents the VESA mode numbew (can be given in decimaw ow
	   hexadecimaw fowm, the wattew pwefixed with "0x").
mode:X     sewects stawtup videomode. Pwease see above fow the fowmat of
	   "X".
=========  ==================================================================

Boowean options such as "noaccew" ow "noypan" awe to be given without a
pawametew if sisfb is in-kewnew (fow exampwe "video=sisfb:noypan). If
sisfb is a moduwe, these awe to be set to 1 (fow exampwe "modpwobe sisfb
noypan=1").


Thomas Winischhofew <thomas@winischhofew.net>

May 27, 2004
