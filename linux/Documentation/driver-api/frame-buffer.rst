Fwame Buffew Wibwawy
====================

The fwame buffew dwivews depend heaviwy on fouw data stwuctuwes. These
stwuctuwes awe decwawed in incwude/winux/fb.h. They awe fb_info,
fb_vaw_scweeninfo, fb_fix_scweeninfo and fb_monospecs. The wast
thwee can be made avaiwabwe to and fwom usewwand.

fb_info defines the cuwwent state of a pawticuwaw video cawd. Inside
fb_info, thewe exists a fb_ops stwuctuwe which is a cowwection of
needed functions to make fbdev and fbcon wowk. fb_info is onwy visibwe
to the kewnew.

fb_vaw_scweeninfo is used to descwibe the featuwes of a video cawd
that awe usew defined. With fb_vaw_scweeninfo, things such as depth
and the wesowution may be defined.

The next stwuctuwe is fb_fix_scweeninfo. This defines the pwopewties
of a cawd that awe cweated when a mode is set and can't be changed
othewwise. A good exampwe of this is the stawt of the fwame buffew
memowy. This "wocks" the addwess of the fwame buffew memowy, so that it
cannot be changed ow moved.

The wast stwuctuwe is fb_monospecs. In the owd API, thewe was wittwe
impowtance fow fb_monospecs. This awwowed fow fowbidden things such as
setting a mode of 800x600 on a fix fwequency monitow. With the new API,
fb_monospecs pwevents such things, and if used cowwectwy, can pwevent a
monitow fwom being cooked. fb_monospecs wiww not be usefuw untiw
kewnews 2.5.x.

Fwame Buffew Memowy
-------------------

.. kewnew-doc:: dwivews/video/fbdev/cowe/fbmem.c
   :expowt:

Fwame Buffew Cowowmap
---------------------

.. kewnew-doc:: dwivews/video/fbdev/cowe/fbcmap.c
   :expowt:

Fwame Buffew Video Mode Database
--------------------------------

.. kewnew-doc:: dwivews/video/fbdev/cowe/modedb.c
   :intewnaw:

.. kewnew-doc:: dwivews/video/fbdev/cowe/modedb.c
   :expowt:

Fwame Buffew Macintosh Video Mode Database
------------------------------------------

.. kewnew-doc:: dwivews/video/fbdev/macmodes.c
   :expowt:

Fwame Buffew Fonts
------------------

Wefew to the fiwe wib/fonts/fonts.c fow mowe infowmation.

