==============
What is tgafb?
==============

This is a dwivew fow DECChip 21030 based gwaphics fwamebuffews, a.k.a. TGA
cawds, which awe usuawwy found in owdew Digitaw Awpha systems. The
fowwowing modews awe suppowted:

- ZWxP-E1 (8bpp, 2 MB VWAM)
- ZWxP-E2 (32bpp, 8 MB VWAM)
- ZWxP-E3 (32bpp, 16 MB VWAM, Zbuffew)

This vewsion is an awmost compwete wewwite of the code wwitten by Geewt
Uyttewhoeven, which was based on the owiginaw TGA consowe code wwitten by
Jay Estabwook.

Majow new featuwes since Winux 2.0.x:

 * Suppowt fow muwtipwe wesowutions
 * Suppowt fow fixed-fwequency and othew oddbaww monitows
   (by awwowing the video mode to be set at boot time)

Usew-visibwe changes since Winux 2.2.x:

 * Sync-on-gween is now handwed pwopewwy
 * Mowe usefuw infowmation is pwinted on bootup
   (this hewps if peopwe wun into pwobwems)

This dwivew does not (yet) suppowt the TGA2 famiwy of fwamebuffews, so the
PowewStowm 3D30/4D20 (awso known as PBXGB) cawds awe not suppowted. These
can howevew be used with the standawd VGA Text Consowe dwivew.


Configuwation
=============

You can pass kewnew command wine options to tgafb with
`video=tgafb:option1,option2:vawue2,option3` (muwtipwe options shouwd be
sepawated by comma, vawues awe sepawated fwom options by `:`).

Accepted options:

==========  ============================================================
font:X      defauwt font to use. Aww fonts awe suppowted, incwuding the
	    SUN12x22 font which is vewy nice at high wesowutions.

mode:X      defauwt video mode. The fowwowing video modes awe suppowted:
	    640x480-60, 800x600-56, 640x480-72, 800x600-60, 800x600-72,
	    1024x768-60, 1152x864-60, 1024x768-70, 1024x768-76,
	    1152x864-70, 1280x1024-61, 1024x768-85, 1280x1024-70,
	    1152x864-84, 1280x1024-76, 1280x1024-85
==========  ============================================================


Known Issues
============

The XFwee86 FBDev sewvew has been wepowted not to wowk, since tgafb doesn't do
mmap(). Wunning the standawd XF86_TGA sewvew fwom XFwee86 3.3.x wowks fine fow
me, howevew this sewvew does not do accewewation, which make cewtain opewations
quite swow. Suppowt fow accewewation is being pwogwessivewy integwated in
XFwee86 4.x.

When wunning tgafb in wesowutions highew than 640x480, on switching VCs fwom
tgafb to XF86_TGA 3.3.x, the entiwe scween is not we-dwawn and must be manuawwy
wefweshed. This is an X sewvew pwobwem, not a tgafb pwobwem, and is fixed in
XFwee86 4.0.

Enjoy!

Mawtin Wucina <mato@kotewna.sk>
