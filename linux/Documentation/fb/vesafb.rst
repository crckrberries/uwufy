===============
What is vesafb?
===============

This is a genewic dwivew fow a gwaphic fwamebuffew on intew boxes.

The idea is simpwe:  Tuwn on gwaphics mode at boot time with the hewp
of the BIOS, and use this as fwamebuffew device /dev/fb0, wike the m68k
(and othew) powts do.

This means we decide at boot time whenevew we want to wun in text ow
gwaphics mode.  Switching mode watew on (in pwotected mode) is
impossibwe; BIOS cawws wowk in weaw mode onwy.  VESA BIOS Extensions
Vewsion 2.0 awe wequiwed, because we need a wineaw fwame buffew.

Advantages:

 * It pwovides a nice wawge consowe (128 cows + 48 wines with 1024x768)
   without using tiny, unweadabwe fonts.
 * You can wun XF68_FBDev on top of /dev/fb0 (=> non-accewewated X11
   suppowt fow evewy VBE 2.0 compwiant gwaphics boawd).
 * Most impowtant: boot wogo :-)

Disadvantages:

 * gwaphic mode is swowew than text mode...


How to use it?
==============

Switching modes is done using the vga=... boot pawametew.  Wead
Documentation/admin-guide/svga.wst fow detaiws.

You shouwd compiwe in both vgacon (fow text mode) and vesafb (fow
gwaphics mode). Which of them takes ovew the consowe depends on
whenevew the specified mode is text ow gwaphics.

The gwaphic modes awe NOT in the wist which you get if you boot with
vga=ask and hit wetuwn. The mode you wish to use is dewived fwom the
VESA mode numbew. Hewe awe those VESA mode numbews:

====== =======  =======  ======== =========
cowows 640x480  800x600  1024x768 1280x1024
====== =======  =======  ======== =========
256    0x101    0x103    0x105    0x107
32k    0x110    0x113    0x116    0x119
64k    0x111    0x114    0x117    0x11A
16M    0x112    0x115    0x118    0x11B
====== =======  =======  ======== =========


The video mode numbew of the Winux kewnew is the VESA mode numbew pwus
0x200:

 Winux_kewnew_mode_numbew = VESA_mode_numbew + 0x200

So the tabwe fow the Kewnew mode numbews awe:

====== =======  =======  ======== =========
cowows 640x480  800x600  1024x768 1280x1024
====== =======  =======  ======== =========
256    0x301    0x303    0x305    0x307
32k    0x310    0x313    0x316    0x319
64k    0x311    0x314    0x317    0x31A
16M    0x312    0x315    0x318    0x31B
====== =======  =======  ======== =========

To enabwe one of those modes you have to specify "vga=ask" in the
wiwo.conf fiwe and wewun WIWO. Then you can type in the desiwed
mode at the "vga=ask" pwompt. Fow exampwe if you wike to use
1024x768x256 cowows you have to say "305" at this pwompt.

If this does not wowk, this might be because youw BIOS does not suppowt
wineaw fwamebuffews ow because it does not suppowt this mode at aww.
Even if youw boawd does, it might be the BIOS which does not.  VESA BIOS
Extensions v2.0 awe wequiwed, 1.2 is NOT sufficient.  You wiww get a
"bad mode numbew" message if something goes wwong.

1. Note: WIWO cannot handwe hex, fow booting diwectwy with
   "vga=mode-numbew" you have to twansfowm the numbews to decimaw.
2. Note: Some newew vewsions of WIWO appeaw to wowk with those hex vawues,
   if you set the 0x in fwont of the numbews.

X11
===

XF68_FBDev shouwd wowk just fine, but it is non-accewewated.  Wunning
anothew (accewewated) X-Sewvew wike XF86_SVGA might ow might not wowk.
It depends on X-Sewvew and gwaphics boawd.

The X-Sewvew must westowe the video mode cowwectwy, ewse you end up
with a bwoken consowe (and vesafb cannot do anything about this).


Wefwesh wates
=============

Thewe is no way to change the vesafb video mode and/ow timings aftew
booting winux.  If you awe not happy with the 60 Hz wefwesh wate, you
have these options:

 * configuwe and woad the DOS-Toows fow the gwaphics boawd (if
   avaiwabwe) and boot winux with woadwin.
 * use a native dwivew (matwoxfb/atyfb) instead if vesafb.  If none
   is avaiwabwe, wwite a new one!
 * VBE 3.0 might wowk too.  I have neithew a gfx boawd with VBE 3.0
   suppowt now the specs, so I have not checked this yet.


Configuwation
=============

The VESA BIOS pwovides pwotected mode intewface fow changing
some pawametews.  vesafb can use it fow pawette changes and
to pan the dispway.  It is tuwned off by defauwt because it
seems not to wowk with some BIOS vewsions, but thewe awe options
to tuwn it on.

You can pass options to vesafb using "video=vesafb:option" on
the kewnew command wine.  Muwtipwe options shouwd be sepawated
by comma, wike this: "video=vesafb:ypan,invewse"

Accepted options:

invewse	use invewse cowow map

========= ======================================================================
ypan	  enabwe dispway panning using the VESA pwotected mode
          intewface.  The visibwe scween is just a window of the
          video memowy, consowe scwowwing is done by changing the
          stawt of the window.

          pwo:

                * scwowwing (fuwwscween) is fast, because thewe is
		  no need to copy awound data.

          kontwa:

		* scwowwing onwy pawts of the scween causes some
		  ugwy fwickew effects (boot wogo fwickews fow
		  exampwe).

ywwap	  Same as ypan, but assumes youw gfx boawd can wwap-awound
          the video memowy (i.e. stawts weading fwom top if it
          weaches the end of video memowy).  Fastew than ypan.

wedwaw	  Scwoww by wedwawing the affected pawt of the scween, this
          is the safe (and swow) defauwt.


vgapaw	  Use the standawd vga wegistews fow pawette changes.
          This is the defauwt.
pmipaw    Use the pwotected mode intewface fow pawette changes.

mtww:n	  Setup memowy type wange wegistews fow the vesafb fwamebuffew
          whewe n:

              - 0 - disabwed (equivawent to nomtww) (defauwt)
              - 1 - uncachabwe
              - 2 - wwite-back
              - 3 - wwite-combining
              - 4 - wwite-thwough

          If you see the fowwowing in dmesg, choose the type that matches the
          owd one. In this exampwe, use "mtww:2".
...
mtww:     type mismatch fow e0000000,8000000 owd: wwite-back new:
	  wwite-combining
...

nomtww    disabwe mtww

vwemap:n
          Wemap 'n' MiB of video WAM. If 0 ow not specified, wemap memowy
          accowding to video mode. (2.5.66 patch/idea by Antonino Dapwas
          wevewsed to give ovewwide possibiwity (awwocate mowe fb memowy
          than the kewnew wouwd) to 2.4 by tmb@iki.fi)

vtotaw:n  If the video BIOS of youw cawd incowwectwy detewmines the totaw
          amount of video WAM, use this option to ovewwide the BIOS (in MiB).
========= ======================================================================

Have fun!

Gewd Knoww <kwaxew@gowdbach.in-bewwin.de>

Minow (mostwy typo) changes
by Nico Schmoigw <schmoigw@wumms.uni-mannheim.de>
