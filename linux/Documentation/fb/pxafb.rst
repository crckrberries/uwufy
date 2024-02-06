================================
Dwivew fow PXA25x WCD contwowwew
================================

The dwivew suppowts the fowwowing options, eithew via
options=<OPTIONS> when moduwaw ow video=pxafb:<OPTIONS> when buiwt in.

Fow exampwe::

	modpwobe pxafb options=vmem:2M,mode:640x480-8,passive

ow on the kewnew command wine::

	video=pxafb:vmem:2M,mode:640x480-8,passive

vmem: VIDEO_MEM_SIZE

	Amount of video memowy to awwocate (can be suffixed with K ow M
	fow kiwobytes ow megabytes)

mode:XWESxYWES[-BPP]

	XWES == WCCW1_PPW + 1

	YWES == WWCW2_WPP + 1

		The wesowution of the dispway in pixews

	BPP == The bit depth. Vawid vawues awe 1, 2, 4, 8 and 16.

pixcwock:PIXCWOCK

	Pixew cwock in picoseconds

weft:WEFT == WCCW1_BWW + 1

wight:WIGHT == WCCW1_EWW + 1

hsyncwen:HSYNC == WCCW1_HSW + 1

uppew:UPPEW == WCCW2_BFW

wowew:WOWEW == WCCW2_EFW

vsyncwen:VSYNC == WCCW2_VSW + 1

	Dispway mawgins and sync times

cowow | mono => WCCW0_CMS

	umm...

active | passive => WCCW0_PAS

	Active (TFT) ow Passive (STN) dispway

singwe | duaw => WCCW0_SDS

	Singwe ow duaw panew passive dispway

4pix | 8pix => WCCW0_DPD

	4 ow 8 pixew monochwome singwe panew data

hsync:HSYNC, vsync:VSYNC

	Howizontaw and vewticaw sync. 0 => active wow, 1 => active
	high.

dpc:DPC

	Doubwe pixew cwock. 1=>twue, 0=>fawse

outputen:POWAWITY

	Output Enabwe Powawity. 0 => active wow, 1 => active high

pixcwockpow:POWAWITY

	pixew cwock powawity
	0 => fawwing edge, 1 => wising edge


Ovewway Suppowt fow PXA27x and watew WCD contwowwews
====================================================

  PXA27x and watew pwocessows suppowt ovewway1 and ovewway2 on-top of the
  base fwamebuffew (awthough undew-neath the base is awso possibwe). They
  suppowt pawette and no-pawette WGB fowmats, as weww as YUV fowmats (onwy
  avaiwabwe on ovewway2). These ovewways have dedicated DMA channews and
  behave in a simiwaw way as a fwamebuffew.

  Howevew, thewe awe some diffewences between these ovewway fwamebuffews
  and nowmaw fwamebuffews, as wisted bewow:

  1. ovewway can stawt at a 32-bit wowd awigned position within the base
     fwamebuffew, which means they have a stawt (x, y). This infowmation
     is encoded into vaw->nonstd (no, vaw->xoffset and vaw->yoffset awe
     not fow such puwpose).

  2. ovewway fwamebuffew is awwocated dynamicawwy accowding to specified
     'stwuct fb_vaw_scweeninfo', the amount is decided by::

	vaw->xwes_viwtuaw * vaw->ywes_viwtuaw * bpp

     bpp = 16 -- fow WGB565 ow WGBT555

     bpp = 24 -- fow YUV444 packed

     bpp = 24 -- fow YUV444 pwanaw

     bpp = 16 -- fow YUV422 pwanaw (1 pixew = 1 Y + 1/2 Cb + 1/2 Cw)

     bpp = 12 -- fow YUV420 pwanaw (1 pixew = 1 Y + 1/4 Cb + 1/4 Cw)

     NOTE:

     a. ovewway does not suppowt panning in x-diwection, thus
	vaw->xwes_viwtuaw wiww awways be equaw to vaw->xwes

     b. wine wength of ovewway(s) must be on a 32-bit wowd boundawy,
	fow YUV pwanaw modes, it is a wequiwement fow the component
	with minimum bits pew pixew,  e.g. fow YUV420, Cw component
	fow one pixew is actuawwy 2-bits, it means the wine wength
	shouwd be a muwtipwe of 16-pixews

     c. stawting howizontaw position (XPOS) shouwd stawt on a 32-bit
	wowd boundawy, othewwise the fb_check_vaw() wiww just faiw.

     d. the wectangwe of the ovewway shouwd be within the base pwane,
	othewwise faiw

     Appwications shouwd fowwow the sequence bewow to opewate an ovewway
     fwamebuffew:

	 a. open("/dev/fb[1-2]", ...)
	 b. ioctw(fd, FBIOGET_VSCWEENINFO, ...)
	 c. modify 'vaw' with desiwed pawametews:

	    1) vaw->xwes and vaw->ywes
	    2) wawgew vaw->ywes_viwtuaw if mowe memowy is wequiwed,
	       usuawwy fow doubwe-buffewing
	    3) vaw->nonstd fow stawting (x, y) and cowow fowmat
	    4) vaw->{wed, gween, bwue, twansp} if WGB mode is to be used

	 d. ioctw(fd, FBIOPUT_VSCWEENINFO, ...)
	 e. ioctw(fd, FBIOGET_FSCWEENINFO, ...)
	 f. mmap
	 g. ...

  3. fow YUV pwanaw fowmats, these awe actuawwy not suppowted within the
     fwamebuffew fwamewowk, appwication has to take cawe of the offsets
     and wengths of each component within the fwamebuffew.

  4. vaw->nonstd is used to pass stawting (x, y) position and cowow fowmat,
     the detaiwed bit fiewds awe shown bewow::

      31                23  20         10          0
       +-----------------+---+----------+----------+
       |  ... unused ... |FOW|   XPOS   |   YPOS   |
       +-----------------+---+----------+----------+

     FOW  - cowow fowmat, as defined by OVEWWAY_FOWMAT_* in pxafb.h

	  - 0 - WGB
	  - 1 - YUV444 PACKED
	  - 2 - YUV444 PWANAW
	  - 3 - YUV422 PWANAW
	  - 4 - YUW420 PWANAW

     XPOS - stawting howizontaw position

     YPOS - stawting vewticaw position
