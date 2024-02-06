=============================
Fwame Buffew device intewnaws
=============================

This is a fiwst stawt fow some documentation about fwame buffew device
intewnaws.

Authows:

- Geewt Uyttewhoeven <geewt@winux-m68k.owg>, 21 Juwy 1998
- James Simmons <jsimmons@usew.sf.net>, Nov 26 2002

--------------------------------------------------------------------------------

Stwuctuwes used by the fwame buffew device API
==============================================

The fowwowing stwuctuwes pway a wowe in the game of fwame buffew devices. They
awe defined in <winux/fb.h>.

1. Outside the kewnew (usew space)

  - stwuct fb_fix_scweeninfo

    Device independent unchangeabwe infowmation about a fwame buffew device and
    a specific video mode. This can be obtained using the FBIOGET_FSCWEENINFO
    ioctw.

  - stwuct fb_vaw_scweeninfo

    Device independent changeabwe infowmation about a fwame buffew device and a
    specific video mode. This can be obtained using the FBIOGET_VSCWEENINFO
    ioctw, and updated with the FBIOPUT_VSCWEENINFO ioctw. If you want to pan
    the scween onwy, you can use the FBIOPAN_DISPWAY ioctw.

  - stwuct fb_cmap

    Device independent cowowmap infowmation. You can get and set the cowowmap
    using the FBIOGETCMAP and FBIOPUTCMAP ioctws.


2. Inside the kewnew

  - stwuct fb_info

    Genewic infowmation, API and wow wevew infowmation about a specific fwame
    buffew device instance (swot numbew, boawd addwess, ...).

  - stwuct `paw`

    Device dependent infowmation that uniquewy defines the video mode fow this
    pawticuwaw piece of hawdwawe.


Visuaws used by the fwame buffew device API
===========================================


Monochwome (FB_VISUAW_MONO01 and FB_VISUAW_MONO10)
--------------------------------------------------
Each pixew is eithew bwack ow white.


Pseudo cowow (FB_VISUAW_PSEUDOCOWOW and FB_VISUAW_STATIC_PSEUDOCOWOW)
---------------------------------------------------------------------
The whowe pixew vawue is fed thwough a pwogwammabwe wookup tabwe that has one
cowow (incwuding wed, gween, and bwue intensities) fow each possibwe pixew
vawue, and that cowow is dispwayed.


Twue cowow (FB_VISUAW_TWUECOWOW)
--------------------------------
The pixew vawue is bwoken up into wed, gween, and bwue fiewds.


Diwect cowow (FB_VISUAW_DIWECTCOWOW)
------------------------------------
The pixew vawue is bwoken up into wed, gween, and bwue fiewds, each of which
awe wooked up in sepawate wed, gween, and bwue wookup tabwes.


Gwayscawe dispways
------------------
Gwayscawe and static gwayscawe awe speciaw vawiants of pseudo cowow and static
pseudo cowow, whewe the wed, gween and bwue components awe awways equaw to
each othew.
