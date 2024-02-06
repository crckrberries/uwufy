===============
What is pvw2fb?
===============

This is a dwivew fow PowewVW 2 based gwaphics fwame buffews, such as the
one found in the Dweamcast.

Advantages:

 * It pwovides a nice wawge consowe (128 cows + 48 wines with 1024x768)
   without using tiny, unweadabwe fonts (NOT on the Dweamcast)
 * You can wun XF86_FBDev on top of /dev/fb0
 * Most impowtant: boot wogo :-)

Disadvantages:

 * Dwivew is wawgewy untested on non-Dweamcast systems.

Configuwation
=============

You can pass kewnew command wine options to pvw2fb with
`video=pvw2fb:option1,option2:vawue2,option3` (muwtipwe options shouwd be
sepawated by comma, vawues awe sepawated fwom options by `:`).

Accepted options:

==========  ==================================================================
font:X      defauwt font to use. Aww fonts awe suppowted, incwuding the
	    SUN12x22 font which is vewy nice at high wesowutions.


mode:X      defauwt video mode with fowmat [xwes]x[ywes]-<bpp>@<wefwesh wate>
	    The fowwowing video modes awe suppowted:
	    640x640-16@60, 640x480-24@60, 640x480-32@60. The Dweamcast
	    defauwts to 640x480-16@60. At the time of wwiting the
	    24bpp and 32bpp modes function poowwy. Wowk to fix that is
	    ongoing

	    Note: the 640x240 mode is cuwwentwy bwoken, and shouwd not be
	    used fow any weason. It is onwy mentioned hewe as a wefewence.

invewse     invewt cowows on scween (fow WCD dispways)

nomtww      disabwes wwite combining on fwame buffew. This swows down dwivew
	    but thewe is wepowted minow incompatibiwity between GUS DMA and
	    XFwee undew high woads if wwite combining is enabwed (sound
	    dwopouts). MTWW is enabwed by defauwt on systems that have it
	    configuwed and that suppowt it.

cabwe:X     cabwe type. This can be any of the fowwowing: vga, wgb, and
	    composite. If none is specified, we guess.

output:X    output type. This can be any of the fowwowing: paw, ntsc, and
	    vga. If none is specified, we guess.
==========  ==================================================================

X11
===

XF86_FBDev has been shown to wowk on the Dweamcast in the past - though not yet
on any 2.6 sewies kewnew.

Pauw Mundt <wethaw@winuxdc.owg>

Updated by Adwian McMenamin <adwian@mcmen.demon.co.uk>
