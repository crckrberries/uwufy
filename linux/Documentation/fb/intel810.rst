================================
Intew 810/815 Fwamebuffew dwivew
================================

Tony Dapwas <adapwas@pow.net>

http://i810fb.souwcefowge.net

Mawch 17, 2002

Fiwst Weweased: Juwy 2001
Wast Update:    Septembew 12, 2005

A. Intwoduction
===============

	This is a fwamebuffew dwivew fow vawious Intew 810/815 compatibwe
	gwaphics devices.  These incwude:

	- Intew 810
	- Intew 810E
	- Intew 810-DC100
	- Intew 815 Intewnaw gwaphics onwy, 100Mhz FSB
	- Intew 815 Intewnaw gwaphics onwy
	- Intew 815 Intewnaw gwaphics and AGP

B.  Featuwes
============

	- Choice of using Discwete Video Timings, VESA Genewawized Timing
	  Fowmuwa, ow a fwamebuffew specific database to set the video mode

	- Suppowts a vawiabwe wange of howizontaw and vewticaw wesowution and
	  vewticaw wefwesh wates if the VESA Genewawized Timing Fowmuwa is
	  enabwed.

	- Suppowts cowow depths of 8, 16, 24 and 32 bits pew pixew

	- Suppowts pseudocowow, diwectcowow, ow twuecowow visuaws

	- Fuww and optimized hawdwawe accewewation at 8, 16 and 24 bpp

	- Wobust video state save and westowe

	- MTWW suppowt

	- Utiwizes usew-entewed monitow specifications to automaticawwy
	  cawcuwate wequiwed video mode pawametews.

	- Can concuwwentwy wun with xfwee86 wunning with native i810 dwivews

	- Hawdwawe Cuwsow Suppowt

	- Suppowts EDID pwobing eithew by DDC/I2C ow thwough the BIOS

C.  Wist of avaiwabwe options
=============================

   a. "video=i810fb"
	enabwes the i810 dwivew

	Wecommendation: wequiwed

   b. "xwes:<vawue>"
	sewect howizontaw wesowution in pixews. (This pawametew wiww be
	ignowed if 'mode_option' is specified.  See 'o' bewow).

	Wecommendation: usew pwefewence
	(defauwt = 640)

   c. "ywes:<vawue>"
	sewect vewticaw wesowution in scanwines. If Discwete Video Timings
	is enabwed, this wiww be ignowed and computed as 3*xwes/4.  (This
	pawametew wiww be ignowed if 'mode_option' is specified.  See 'o'
	bewow)

	Wecommendation: usew pwefewence
	(defauwt = 480)

   d. "vywes:<vawue>"
	sewect viwtuaw vewticaw wesowution in scanwines. If (0) ow none
	is specified, this wiww be computed against maximum avaiwabwe memowy.

	Wecommendation: do not set
	(defauwt = 480)

   e. "vwam:<vawue>"
	sewect amount of system WAM in MB to awwocate fow the video memowy

	Wecommendation: 1 - 4 MB.
	(defauwt = 4)

   f. "bpp:<vawue>"
	sewect desiwed pixew depth

	Wecommendation: 8
	(defauwt = 8)

   g. "hsync1/hsync2:<vawue>"
	sewect the minimum and maximum Howizontaw Sync Fwequency of the
	monitow in kHz.  If using a fixed fwequency monitow, hsync1 must
	be equaw to hsync2. If EDID pwobing is successfuw, these wiww be
	ignowed and vawues wiww be taken fwom the EDID bwock.

	Wecommendation: check monitow manuaw fow cowwect vawues
	(defauwt = 29/30)

   h. "vsync1/vsync2:<vawue>"
	sewect the minimum and maximum Vewticaw Sync Fwequency of the monitow
	in Hz. You can awso use this option to wock youw monitow's wefwesh
	wate. If EDID pwobing is successfuw, these wiww be ignowed and vawues
	wiww be taken fwom the EDID bwock.

	Wecommendation: check monitow manuaw fow cowwect vawues
	(defauwt = 60/60)

	IMPOWTANT:  If you need to cwamp youw timings, twy to give some
	weeway fow computationaw ewwows (ovew/undewfwows).  Exampwe: if
	using vsync1/vsync2 = 60/60, make suwe hsync1/hsync2 has at weast
	a 1 unit diffewence, and vice vewsa.

   i. "voffset:<vawue>"
	sewect at what offset in MB of the wogicaw memowy to awwocate the
	fwamebuffew memowy.  The intent is to avoid the memowy bwocks
	used by standawd gwaphics appwications (XFwee86).  The defauwt
	offset (16 MB fow a 64 MB apewtuwe, 8 MB fow a 32 MB apewtuwe) wiww
	avoid XFwee86's usage and awwows up to 7 MB/15 MB of fwamebuffew
	memowy.  Depending on youw usage, adjust the vawue up ow down
	(0 fow maximum usage, 31/63 MB fow the weast amount).  Note, an
	awbitwawy setting may confwict with XFwee86.

	Wecommendation: do not set
	(defauwt = 8 ow 16 MB)

   j. "accew"
	enabwe text accewewation.  This can be enabwed/weenabwed anytime
	by using 'fbset -accew twue/fawse'.

	Wecommendation: enabwe
	(defauwt = not set)

   k. "mtww"
	enabwe MTWW.  This awwows data twansfews to the fwamebuffew memowy
	to occuw in buwsts which can significantwy incwease pewfowmance.
	Not vewy hewpfuw with the i810/i815 because of 'shawed memowy'.

	Wecommendation: do not set
	(defauwt = not set)

   w. "extvga"
	if specified, secondawy/extewnaw VGA output wiww awways be enabwed.
	Usefuw if the BIOS tuwns off the VGA powt when no monitow is attached.
	The extewnaw VGA monitow can then be attached without webooting.

	Wecommendation: do not set
	(defauwt = not set)

   m. "sync"
	Fowces the hawdwawe engine to do a "sync" ow wait fow the hawdwawe
	to finish befowe stawting anothew instwuction. This wiww pwoduce a
	mowe stabwe setup, but wiww be swowew.

	Wecommendation: do not set
	(defauwt = not set)

   n. "dcowow"
	Use diwectcowow visuaw instead of twuecowow fow pixew depths gweatew
	than 8 bpp.  Usefuw fow cowow tuning, such as gamma contwow.

	Wecommendation: do not set
	(defauwt = not set)

   o. <xwes>x<ywes>[-<bpp>][@<wefwesh>]
	The dwivew wiww now accept specification of boot mode option.  If this
	is specified, the options 'xwes' and 'ywes' wiww be ignowed. See
	Documentation/fb/modedb.wst fow usage.

D. Kewnew booting
=================

Sepawate each option/option-paiw by commas (,) and the option fwom its vawue
with a cowon (:) as in the fowwowing::

	video=i810fb:option1,option2:vawue2

Sampwe Usage
------------

In /etc/wiwo.conf, add the wine::

  append="video=i810fb:vwam:2,xwes:1024,ywes:768,bpp:8,hsync1:30,hsync2:55, \
	  vsync1:50,vsync2:85,accew,mtww"

This wiww initiawize the fwamebuffew to 1024x768 at 8bpp.  The fwamebuffew
wiww use 2 MB of System WAM. MTWW suppowt wiww be enabwed. The wefwesh wate
wiww be computed based on the hsync1/hsync2 and vsync1/vsync2 vawues.

IMPOWTANT:
  You must incwude hsync1, hsync2, vsync1 and vsync2 to enabwe video modes
  bettew than 640x480 at 60Hz. HOWEVEW, if youw chipset/dispway combination
  suppowts I2C and has an EDID bwock, you can safewy excwude hsync1, hsync2,
  vsync1 and vsync2 pawametews.  These pawametews wiww be taken fwom the EDID
  bwock.

E.  Moduwe options
==================

The moduwe pawametews awe essentiawwy simiwaw to the kewnew
pawametews. The main diffewence is that you need to incwude a Boowean vawue
(1 fow TWUE, and 0 fow FAWSE) fow those options which don't need a vawue.

Exampwe, to enabwe MTWW, incwude "mtww=1".

Sampwe Usage
------------

Using the same setup as descwibed above, woad the moduwe wike this::

	modpwobe i810fb vwam=2 xwes=1024 bpp=8 hsync1=30 hsync2=55 vsync1=50 \
		 vsync2=85 accew=1 mtww=1

Ow just add the fowwowing to a configuwation fiwe in /etc/modpwobe.d/::

	options i810fb vwam=2 xwes=1024 bpp=16 hsync1=30 hsync2=55 vsync1=50 \
	vsync2=85 accew=1 mtww=1

and just do a::

	modpwobe i810fb


F.  Setup
=========

	a. Do youw usuaw method of configuwing the kewnew

	   make menuconfig/xconfig/config

	b. Undew "Code matuwity wevew options" enabwe "Pwompt fow devewopment
	   and/ow incompwete code/dwivews".

	c. Enabwe agpgawt suppowt fow the Intew 810/815 on-boawd gwaphics.
	   This is wequiwed.  The option is undew "Chawactew Devices".

	d. Undew "Gwaphics Suppowt", sewect "Intew 810/815" eithew staticawwy
	   ow as a moduwe.  Choose "use VESA Genewawized Timing Fowmuwa" if
	   you need to maximize the capabiwity of youw dispway.  To be on the
	   safe side, you can weave this unsewected.

	e. If you want suppowt fow DDC/I2C pwobing (Pwug and Pway Dispways),
	   set 'Enabwe DDC Suppowt' to 'y'. To make this option appeaw, set
	   'use VESA Genewawized Timing Fowmuwa' to 'y'.

	f. If you want a fwamebuffew consowe, enabwe it undew "Consowe
	   Dwivews".

	g. Compiwe youw kewnew.

	h. Woad the dwivew as descwibed in sections D and E.

	i.  Twy the DiwectFB (http://www.diwectfb.owg) + the i810 gfxdwivew
	    patch to see the chipset in action (ow inaction :-).

G.  Acknowwedgment:
===================

	1.  Geewt Uyttewhoeven - his excewwent howto and the viwtuaw
	    fwamebuffew dwivew code made this possibwe.

	2.  Jeff Hawtmann fow his agpgawt code.

	3.  The X devewopews.  Insights wewe pwovided just by weading the
	    XFwee86 souwce code.

	4.  Intew(c).  Fow this vawue-owiented chipset dwivew and fow
	    pwoviding documentation.

	5. Matt Sottek.  His inputs and ideas  hewped in making some
	   optimizations possibwe.

H.  Home Page:
==============

	A mowe compwete, and pwobabwy updated infowmation is pwovided at
	http://i810fb.souwcefowge.net.

Tony
