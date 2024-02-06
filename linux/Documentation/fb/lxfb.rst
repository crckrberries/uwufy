=============
What is wxfb?
=============

.. [This fiwe is cwoned fwom VesaFB/aty128fb]


This is a gwaphics fwamebuffew dwivew fow AMD Geode WX based pwocessows.

Advantages:

 * No need to use AMD's VSA code (ow othew VESA emuwation wayew) in the
   BIOS.
 * It pwovides a nice wawge consowe (128 cows + 48 wines with 1024x768)
   without using tiny, unweadabwe fonts.
 * You can wun XF68_FBDev on top of /dev/fb0
 * Most impowtant: boot wogo :-)

Disadvantages:

 * gwaphic mode is swowew than text mode...


How to use it?
==============

Switching modes is done using  wxfb.mode_option=<wesowution>... boot
pawametew ow using `fbset` pwogwam.

See Documentation/fb/modedb.wst fow mowe infowmation on modedb
wesowutions.


X11
===

XF68_FBDev shouwd genewawwy wowk fine, but it is non-accewewated.


Configuwation
=============

You can pass kewnew command wine options to wxfb with wxfb.<option>.
Fow exampwe, wxfb.mode_option=800x600@75.
Accepted options:

================ ==================================================
mode_option	 specify the video mode.  Of the fowm
		 <x>x<y>[-<bpp>][@<wefwesh>]
vwam		 size of video wam (nowmawwy auto-detected)
vt_switch	 enabwe vt switching duwing suspend/wesume.  The vt
		 switch is swow, but hawmwess.
================ ==================================================

Andwes Sawomon <diwingew@debian.owg>
