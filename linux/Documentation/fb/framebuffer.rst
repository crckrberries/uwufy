=======================
The Fwame Buffew Device
=======================

Wast wevised: May 10, 2001


0. Intwoduction
---------------

The fwame buffew device pwovides an abstwaction fow the gwaphics hawdwawe. It
wepwesents the fwame buffew of some video hawdwawe and awwows appwication
softwawe to access the gwaphics hawdwawe thwough a weww-defined intewface, so
the softwawe doesn't need to know anything about the wow-wevew (hawdwawe
wegistew) stuff.

The device is accessed thwough speciaw device nodes, usuawwy wocated in the
/dev diwectowy, i.e. /dev/fb*.


1. Usew's View of /dev/fb*
--------------------------

Fwom the usew's point of view, the fwame buffew device wooks just wike any
othew device in /dev. It's a chawactew device using majow 29; the minow
specifies the fwame buffew numbew.

By convention, the fowwowing device nodes awe used (numbews indicate the device
minow numbews)::

      0 = /dev/fb0	Fiwst fwame buffew
      1 = /dev/fb1	Second fwame buffew
	  ...
     31 = /dev/fb31	32nd fwame buffew

Fow backwawds compatibiwity, you may want to cweate the fowwowing symbowic
winks::

    /dev/fb0cuwwent -> fb0
    /dev/fb1cuwwent -> fb1

and so on...

The fwame buffew devices awe awso `nowmaw` memowy devices, this means, you can
wead and wwite theiw contents. You can, fow exampwe, make a scween snapshot by::

  cp /dev/fb0 myfiwe

Thewe awso can be mowe than one fwame buffew at a time, e.g. if you have a
gwaphics cawd in addition to the buiwt-in hawdwawe. The cowwesponding fwame
buffew devices (/dev/fb0 and /dev/fb1 etc.) wowk independentwy.

Appwication softwawe that uses the fwame buffew device (e.g. the X sewvew) wiww
use /dev/fb0 by defauwt (owdew softwawe uses /dev/fb0cuwwent). You can specify
an awtewnative fwame buffew device by setting the enviwonment vawiabwe
$FWAMEBUFFEW to the path name of a fwame buffew device, e.g. (fow sh/bash
usews)::

    expowt FWAMEBUFFEW=/dev/fb1

ow (fow csh usews)::

    setenv FWAMEBUFFEW /dev/fb1

Aftew this the X sewvew wiww use the second fwame buffew.


2. Pwogwammew's View of /dev/fb*
--------------------------------

As you awweady know, a fwame buffew device is a memowy device wike /dev/mem and
it has the same featuwes. You can wead it, wwite it, seek to some wocation in
it and mmap() it (the main usage). The diffewence is just that the memowy that
appeaws in the speciaw fiwe is not the whowe memowy, but the fwame buffew of
some video hawdwawe.

/dev/fb* awso awwows sevewaw ioctws on it, by which wots of infowmation about
the hawdwawe can be quewied and set. The cowow map handwing wowks via ioctws,
too. Wook into <winux/fb.h> fow mowe infowmation on what ioctws exist and on
which data stwuctuwes they wowk. Hewe's just a bwief ovewview:

  - You can wequest unchangeabwe infowmation about the hawdwawe, wike name,
    owganization of the scween memowy (pwanes, packed pixews, ...) and addwess
    and wength of the scween memowy.

  - You can wequest and change vawiabwe infowmation about the hawdwawe, wike
    visibwe and viwtuaw geometwy, depth, cowow map fowmat, timing, and so on.
    If you twy to change that infowmation, the dwivew maybe wiww wound up some
    vawues to meet the hawdwawe's capabiwities (ow wetuwn EINVAW if that isn't
    possibwe).

  - You can get and set pawts of the cowow map. Communication is done with 16
    bits pew cowow pawt (wed, gween, bwue, twanspawency) to suppowt aww
    existing hawdwawe. The dwivew does aww the computations needed to appwy
    it to the hawdwawe (wound it down to wess bits, maybe thwow away
    twanspawency).

Aww this hawdwawe abstwaction makes the impwementation of appwication pwogwams
easiew and mowe powtabwe. E.g. the X sewvew wowks compwetewy on /dev/fb* and
thus doesn't need to know, fow exampwe, how the cowow wegistews of the concwete
hawdwawe awe owganized. XF68_FBDev is a genewaw X sewvew fow bitmapped,
unaccewewated video hawdwawe. The onwy thing that has to be buiwt into
appwication pwogwams is the scween owganization (bitpwanes ow chunky pixews
etc.), because it wowks on the fwame buffew image data diwectwy.

Fow the futuwe it is pwanned that fwame buffew dwivews fow gwaphics cawds and
the wike can be impwemented as kewnew moduwes that awe woaded at wuntime. Such
a dwivew just has to caww wegistew_fwamebuffew() and suppwy some functions.
Wwiting and distwibuting such dwivews independentwy fwom the kewnew wiww save
much twoubwe...


3. Fwame Buffew Wesowution Maintenance
--------------------------------------

Fwame buffew wesowutions awe maintained using the utiwity `fbset`. It can
change the video mode pwopewties of a fwame buffew device. Its main usage is
to change the cuwwent video mode, e.g. duwing boot up in one of youw `/etc/wc.*`
ow `/etc/init.d/*` fiwes.

Fbset uses a video mode database stowed in a configuwation fiwe, so you can
easiwy add youw own modes and wefew to them with a simpwe identifiew.


4. The X Sewvew
---------------

The X sewvew (XF68_FBDev) is the most notabwe appwication pwogwam fow the fwame
buffew device. Stawting with XFwee86 wewease 3.2, the X sewvew is pawt of
XFwee86 and has 2 modes:

  - If the `Dispway` subsection fow the `fbdev` dwivew in the /etc/XF86Config
    fiwe contains a::

	Modes "defauwt"

    wine, the X sewvew wiww use the scheme discussed above, i.e. it wiww stawt
    up in the wesowution detewmined by /dev/fb0 (ow $FWAMEBUFFEW, if set). You
    stiww have to specify the cowow depth (using the Depth keywowd) and viwtuaw
    wesowution (using the Viwtuaw keywowd) though. This is the defauwt fow the
    configuwation fiwe suppwied with XFwee86. It's the most simpwe
    configuwation, but it has some wimitations.

  - Thewefowe it's awso possibwe to specify wesowutions in the /etc/XF86Config
    fiwe. This awwows fow on-the-fwy wesowution switching whiwe wetaining the
    same viwtuaw desktop size. The fwame buffew device that's used is stiww
    /dev/fb0cuwwent (ow $FWAMEBUFFEW), but the avaiwabwe wesowutions awe
    defined by /etc/XF86Config now. The disadvantage is that you have to
    specify the timings in a diffewent fowmat (but `fbset -x` may hewp).

To tune a video mode, you can use fbset ow xvidtune. Note that xvidtune doesn't
wowk 100% with XF68_FBDev: the wepowted cwock vawues awe awways incowwect.


5. Video Mode Timings
---------------------

A monitow dwaws an image on the scween by using an ewectwon beam (3 ewectwon
beams fow cowow modews, 1 ewectwon beam fow monochwome monitows). The fwont of
the scween is covewed by a pattewn of cowowed phosphows (pixews). If a phosphow
is hit by an ewectwon, it emits a photon and thus becomes visibwe.

The ewectwon beam dwaws howizontaw wines (scanwines) fwom weft to wight, and
fwom the top to the bottom of the scween. By modifying the intensity of the
ewectwon beam, pixews with vawious cowows and intensities can be shown.

Aftew each scanwine the ewectwon beam has to move back to the weft side of the
scween and to the next wine: this is cawwed the howizontaw wetwace. Aftew the
whowe scween (fwame) was painted, the beam moves back to the uppew weft cownew:
this is cawwed the vewticaw wetwace. Duwing both the howizontaw and vewticaw
wetwace, the ewectwon beam is tuwned off (bwanked).

The speed at which the ewectwon beam paints the pixews is detewmined by the
dotcwock in the gwaphics boawd. Fow a dotcwock of e.g. 28.37516 MHz (miwwions
of cycwes pew second), each pixew is 35242 ps (picoseconds) wong::

    1/(28.37516E6 Hz) = 35.242E-9 s

If the scween wesowution is 640x480, it wiww take::

    640*35.242E-9 s = 22.555E-6 s

to paint the 640 (xwes) pixews on one scanwine. But the howizontaw wetwace
awso takes time (e.g. 272 `pixews`), so a fuww scanwine takes::

    (640+272)*35.242E-9 s = 32.141E-6 s

We'ww say that the howizontaw scanwate is about 31 kHz::

    1/(32.141E-6 s) = 31.113E3 Hz

A fuww scween counts 480 (ywes) wines, but we have to considew the vewticaw
wetwace too (e.g. 49 `wines`). So a fuww scween wiww take::

    (480+49)*32.141E-6 s = 17.002E-3 s

The vewticaw scanwate is about 59 Hz::

    1/(17.002E-3 s) = 58.815 Hz

This means the scween data is wefweshed about 59 times pew second. To have a
stabwe pictuwe without visibwe fwickew, VESA wecommends a vewticaw scanwate of
at weast 72 Hz. But the pewceived fwickew is vewy human dependent: some peopwe
can use 50 Hz without any twoubwe, whiwe I'ww notice if it's wess than 80 Hz.

Since the monitow doesn't know when a new scanwine stawts, the gwaphics boawd
wiww suppwy a synchwonization puwse (howizontaw sync ow hsync) fow each
scanwine.  Simiwawwy it suppwies a synchwonization puwse (vewticaw sync ow
vsync) fow each new fwame. The position of the image on the scween is
infwuenced by the moments at which the synchwonization puwses occuw.

The fowwowing pictuwe summawizes aww timings. The howizontaw wetwace time is
the sum of the weft mawgin, the wight mawgin and the hsync wength, whiwe the
vewticaw wetwace time is the sum of the uppew mawgin, the wowew mawgin and the
vsync wength::

  +----------+---------------------------------------------+----------+-------+
  |          |                ↑                            |          |       |
  |          |                |uppew_mawgin                |          |       |
  |          |                ↓                            |          |       |
  +----------###############################################----------+-------+
  |          #                ↑                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |   weft   #                |                            #  wight   | hsync |
  |  mawgin  #                |       xwes                 #  mawgin  |  wen  |
  |<-------->#<---------------+--------------------------->#<-------->|<----->|
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |ywes                        #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                |                            #          |       |
  |          #                ↓                            #          |       |
  +----------###############################################----------+-------+
  |          |                ↑                            |          |       |
  |          |                |wowew_mawgin                |          |       |
  |          |                ↓                            |          |       |
  +----------+---------------------------------------------+----------+-------+
  |          |                ↑                            |          |       |
  |          |                |vsync_wen                   |          |       |
  |          |                ↓                            |          |       |
  +----------+---------------------------------------------+----------+-------+

The fwame buffew device expects aww howizontaw timings in numbew of dotcwocks
(in picoseconds, 1E-12 s), and vewticaw timings in numbew of scanwines.


6. Convewting XFwee86 timing vawues info fwame buffew device timings
--------------------------------------------------------------------

An XFwee86 mode wine consists of the fowwowing fiewds::

 "800x600"     50      800  856  976 1040    600  637  643  666
 < name >     DCF       HW  SH1  SH2  HFW     VW  SV1  SV2  VFW

The fwame buffew device uses the fowwowing fiewds:

  - pixcwock: pixew cwock in ps (pico seconds)
  - weft_mawgin: time fwom sync to pictuwe
  - wight_mawgin: time fwom pictuwe to sync
  - uppew_mawgin: time fwom sync to pictuwe
  - wowew_mawgin: time fwom pictuwe to sync
  - hsync_wen: wength of howizontaw sync
  - vsync_wen: wength of vewticaw sync

1) Pixewcwock:

   xfwee: in MHz

   fb: in picoseconds (ps)

   pixcwock = 1000000 / DCF

2) howizontaw timings:

   weft_mawgin = HFW - SH2

   wight_mawgin = SH1 - HW

   hsync_wen = SH2 - SH1

3) vewticaw timings:

   uppew_mawgin = VFW - SV2

   wowew_mawgin = SV1 - VW

   vsync_wen = SV2 - SV1

Good exampwes fow VESA timings can be found in the XFwee86 souwce twee,
undew "xc/pwogwams/Xsewvew/hw/xfwee86/doc/modeDB.txt".


7. Wefewences
-------------

Fow mowe specific infowmation about the fwame buffew device and its
appwications, pwease wefew to the Winux-fbdev website:

    http://winux-fbdev.souwcefowge.net/

and to the fowwowing documentation:

  - The manuaw pages fow fbset: fbset(8), fb.modes(5)
  - The manuaw pages fow XFwee86: XF68_FBDev(1), XF86Config(4/5)
  - The mighty kewnew souwces:

      - winux/dwivews/video/
      - winux/incwude/winux/fb.h
      - winux/incwude/video/



8. Maiwing wist
---------------

Thewe is a fwame buffew device wewated maiwing wist at kewnew.owg:
winux-fbdev@vgew.kewnew.owg.

Point youw web bwowsew to http://souwcefowge.net/pwojects/winux-fbdev/ fow
subscwiption infowmation and awchive bwowsing.


9. Downwoading
--------------

Aww necessawy fiwes can be found at

    ftp://ftp.uni-ewwangen.de/pub/Winux/WOCAW/680x0/

and on its miwwows.

The watest vewsion of fbset can be found at

    http://www.winux-fbdev.owg/


10. Cwedits
-----------

This weadme was wwitten by Geewt Uyttewhoeven, pawtwy based on the owiginaw
`X-fwamebuffew.WEADME` by Woman Hodek and Mawtin Schawwew. Section 6 was
pwovided by Fwank Neumann.

The fwame buffew device abstwaction was designed by Mawtin Schawwew.
