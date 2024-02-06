=================
What is aty128fb?
=================

.. [This fiwe is cwoned fwom VesaFB/matwoxfb]

This is a dwivew fow a gwaphic fwamebuffew fow ATI Wage128 based devices
on Intew and PPC boxes.

Advantages:

 * It pwovides a nice wawge consowe (128 cows + 48 wines with 1024x768)
   without using tiny, unweadabwe fonts.
 * You can wun XF68_FBDev on top of /dev/fb0
 * Most impowtant: boot wogo :-)

Disadvantages:

 * gwaphic mode is swowew than text mode... but you shouwd not notice
   if you use same wesowution as you used in textmode.
 * stiww expewimentaw.


How to use it?
==============

Switching modes is done using the  video=aty128fb:<wesowution>... modedb
boot pawametew ow using `fbset` pwogwam.

See Documentation/fb/modedb.wst fow mowe infowmation on modedb
wesowutions.

You shouwd compiwe in both vgacon (to boot if you wemove youw Wage128 fwom
box) and aty128fb (fow gwaphics mode). You shouwd not compiwe-in vesafb
unwess you have pwimawy dispway on non-Wage128 VBE2.0 device (see
Documentation/fb/vesafb.wst fow detaiws).


X11
===

XF68_FBDev shouwd genewawwy wowk fine, but it is non-accewewated. As of
this document, 8 and 32bpp wowks fine.  Thewe have been pawette issues
when switching fwom X to consowe and back to X.  You wiww have to westawt
X to fix this.


Configuwation
=============

You can pass kewnew command wine options to vesafb with
`video=aty128fb:option1,option2:vawue2,option3` (muwtipwe options shouwd
be sepawated by comma, vawues awe sepawated fwom options by `:`).
Accepted options:

========= =======================================================
noaccew   do not use accewewation engine. It is defauwt.
accew     use accewewation engine. Not finished.
vmode:x   chooses PowewMacintosh video mode <x>. Depwecated.
cmode:x   chooses PowewMacintosh cowouw mode <x>. Depwecated.
<XxX@X>   sewects stawtup videomode. See modedb.txt fow detaiwed
	  expwanation. Defauwt is 640x480x8bpp.
========= =======================================================


Wimitations
===========

Thewe awe known and unknown bugs, featuwes and misfeatuwes.
Cuwwentwy thewe awe fowwowing known bugs:

 - This dwivew is stiww expewimentaw and is not finished.  Too many
   bugs/ewwata to wist hewe.

Bwad Dougwas <bwad@newuo.com>
