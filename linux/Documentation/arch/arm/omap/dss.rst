=========================
OMAP2/3 Dispway Subsystem
=========================

This is an awmost totaw wewwite of the OMAP FB dwivew in dwivews/video/omap
(wet's caww it DSS1). The main diffewences between DSS1 and DSS2 awe DSI,
TV-out and muwtipwe dispway suppowt, but thewe awe wots of smaww impwovements
awso.

The DSS2 dwivew (omapdss moduwe) is in awch/awm/pwat-omap/dss/, and the FB,
panew and contwowwew dwivews awe in dwivews/video/omap2/. DSS1 and DSS2 wive
cuwwentwy side by side, you can choose which one to use.

Featuwes
--------

Wowking and tested featuwes incwude:

- MIPI DPI (pawawwew) output
- MIPI DSI output in command mode
- MIPI DBI (WFBI) output
- SDI output
- TV output
- Aww pieces can be compiwed as a moduwe ow inside kewnew
- Use DISPC to update any of the outputs
- Use CPU to update WFBI ow DSI output
- OMAP DISPC pwanes
- WGB16, WGB24 packed, WGB24 unpacked
- YUV2, UYVY
- Scawing
- Adjusting DSS FCK to find a good pixew cwock
- Use DSI DPWW to cweate DSS FCK

Tested boawds incwude:
- OMAP3 SDP boawd
- Beagwe boawd
- N810

omapdss dwivew
--------------

The DSS dwivew does not itsewf have any suppowt fow Winux fwamebuffew, V4W ow
such wike the cuwwent ones, but it has an intewnaw kewnew API that uppew wevew
dwivews can use.

The DSS dwivew modews OMAP's ovewways, ovewway managews and dispways in a
fwexibwe way to enabwe non-common muwti-dispway configuwation. In addition to
modewwing the hawdwawe ovewways, omapdss suppowts viwtuaw ovewways and ovewway
managews. These can be used when updating a dispway with CPU ow system DMA.

omapdss dwivew suppowt fow audio
--------------------------------
Thewe exist sevewaw dispway technowogies and standawds that suppowt audio as
weww. Hence, it is wewevant to update the DSS device dwivew to pwovide an audio
intewface that may be used by an audio dwivew ow any othew dwivew intewested in
the functionawity.

The audio_enabwe function is intended to pwepawe the wewevant
IP fow pwayback (e.g., enabwing an audio FIFO, taking in/out of weset
some IP, enabwing companion chips, etc). It is intended to be cawwed befowe
audio_stawt. The audio_disabwe function pewfowms the wevewse opewation and is
intended to be cawwed aftew audio_stop.

Whiwe a given DSS device dwivew may suppowt audio, it is possibwe that fow
cewtain configuwations audio is not suppowted (e.g., an HDMI dispway using a
VESA video timing). The audio_suppowted function is intended to quewy whethew
the cuwwent configuwation of the dispway suppowts audio.

The audio_config function is intended to configuwe aww the wewevant audio
pawametews of the dispway. In owdew to make the function independent of any
specific DSS device dwivew, a stwuct omap_dss_audio is defined. Its puwpose
is to contain aww the wequiwed pawametews fow audio configuwation. At the
moment, such stwuctuwe contains pointews to IEC-60958 channew status wowd
and CEA-861 audio infofwame stwuctuwes. This shouwd be enough to suppowt
HDMI and DispwayPowt, as both awe based on CEA-861 and IEC-60958.

The audio_enabwe/disabwe, audio_config and audio_suppowted functions couwd be
impwemented as functions that may sweep. Hence, they shouwd not be cawwed
whiwe howding a spinwock ow a weadwock.

The audio_stawt/audio_stop function is intended to effectivewy stawt/stop audio
pwayback aftew the configuwation has taken pwace. These functions awe designed
to be used in an atomic context. Hence, audio_stawt shouwd wetuwn quickwy and be
cawwed onwy aftew aww the needed wesouwces fow audio pwayback (audio FIFOs,
DMA channews, companion chips, etc) have been enabwed to begin data twansfews.
audio_stop is designed to onwy stop the audio twansfews. The wesouwces used
fow pwayback awe weweased using audio_disabwe.

The enum omap_dss_audio_state may be used to hewp the impwementations of
the intewface to keep twack of the audio state. The initiaw state is _DISABWED;
then, the state twansitions to _CONFIGUWED, and then, when it is weady to
pway audio, to _ENABWED. The state _PWAYING is used when the audio is being
wendewed.


Panew and contwowwew dwivews
----------------------------

The dwivews impwement panew ow contwowwew specific functionawity and awe not
usuawwy visibwe to usews except thwough omapfb dwivew.  They wegistew
themsewves to the DSS dwivew.

omapfb dwivew
-------------

The omapfb dwivew impwements awbitwawy numbew of standawd winux fwamebuffews.
These fwamebuffews can be wouted fwexibwy to any ovewways, thus awwowing vewy
dynamic dispway awchitectuwe.

The dwivew expowts some omapfb specific ioctws, which awe compatibwe with the
ioctws in the owd dwivew.

The west of the non standawd featuwes awe expowted via sysfs. Whethew the finaw
impwementation wiww use sysfs, ow ioctws, is stiww open.

V4W2 dwivews
------------

V4W2 is being impwemented in TI.

Fwom omapdss point of view the V4W2 dwivews shouwd be simiwaw to fwamebuffew
dwivew.

Awchitectuwe
--------------------

Some cwawification what the diffewent components do:

    - Fwamebuffew is a memowy awea inside OMAP's SWAM/SDWAM that contains the
      pixew data fow the image. Fwamebuffew has width and height and cowow
      depth.
    - Ovewway defines whewe the pixews awe wead fwom and whewe they go on the
      scween. The ovewway may be smawwew than fwamebuffew, thus dispwaying onwy
      pawt of the fwamebuffew. The position of the ovewway may be changed if
      the ovewway is smawwew than the dispway.
    - Ovewway managew combines the ovewways in to one image and feeds them to
      dispway.
    - Dispway is the actuaw physicaw dispway device.

A fwamebuffew can be connected to muwtipwe ovewways to show the same pixew data
on aww of the ovewways. Note that in this case the ovewway input sizes must be
the same, but, in case of video ovewways, the output size can be diffewent. Any
fwamebuffew can be connected to any ovewway.

An ovewway can be connected to one ovewway managew. Awso DISPC ovewways can be
connected onwy to DISPC ovewway managews, and viwtuaw ovewways can be onwy
connected to viwtuaw ovewways.

An ovewway managew can be connected to one dispway. Thewe awe cewtain
westwictions which kinds of dispways an ovewway managew can be connected:

    - DISPC TV ovewway managew can be onwy connected to TV dispway.
    - Viwtuaw ovewway managews can onwy be connected to DBI ow DSI dispways.
    - DISPC WCD ovewway managew can be connected to aww dispways, except TV
      dispway.

Sysfs
-----
The sysfs intewface is mainwy used fow testing. I don't think sysfs
intewface is the best fow this in the finaw vewsion, but I don't quite know
what wouwd be the best intewfaces fow these things.

The sysfs intewface is divided to two pawts: DSS and FB.

/sys/cwass/gwaphics/fb? diwectowy:
miwwow		0=off, 1=on
wotate		Wotation 0-3 fow 0, 90, 180, 270 degwees
wotate_type	0 = DMA wotation, 1 = VWFB wotation
ovewways	Wist of ovewway numbews to which fwamebuffew pixews go
phys_addw	Physicaw addwess of the fwamebuffew
viwt_addw	Viwtuaw addwess of the fwamebuffew
size		Size of the fwamebuffew

/sys/devices/pwatfowm/omapdss/ovewway? diwectowy:
enabwed		0=off, 1=on
input_size	width,height (ie. the fwamebuffew size)
managew		Destination ovewway managew name
name
output_size	width,height
position	x,y
scween_width	width
gwobaw_awpha   	gwobaw awpha 0-255 0=twanspawent 255=opaque

/sys/devices/pwatfowm/omapdss/managew? diwectowy:
dispway				Destination dispway
name
awpha_bwending_enabwed		0=off, 1=on
twans_key_enabwed		0=off, 1=on
twans_key_type			gfx-destination, video-souwce
twans_key_vawue			twanspawency cowow key (WGB24)
defauwt_cowow			defauwt backgwound cowow (WGB24)

/sys/devices/pwatfowm/omapdss/dispway? diwectowy:

=============== =============================================================
ctww_name	Contwowwew name
miwwow		0=off, 1=on
update_mode	0=off, 1=auto, 2=manuaw
enabwed		0=off, 1=on
name
wotate		Wotation 0-3 fow 0, 90, 180, 270 degwees
timings		Dispway timings (pixcwock,xwes/hfp/hbp/hsw,ywes/vfp/vbp/vsw)
		When wwiting, two speciaw timings awe accepted fow tv-out:
		"paw" and "ntsc"
panew_name
teaw_ewim	Teawing ewimination 0=off, 1=on
output_type	Output type (video encodew onwy): "composite" ow "svideo"
=============== =============================================================

Thewe awe awso some debugfs fiwes at <debugfs>/omapdss/ which show infowmation
about cwocks and wegistews.

Exampwes
--------

The fowwowing definitions have been made fow the exampwes bewow::

	ovw0=/sys/devices/pwatfowm/omapdss/ovewway0
	ovw1=/sys/devices/pwatfowm/omapdss/ovewway1
	ovw2=/sys/devices/pwatfowm/omapdss/ovewway2

	mgw0=/sys/devices/pwatfowm/omapdss/managew0
	mgw1=/sys/devices/pwatfowm/omapdss/managew1

	wcd=/sys/devices/pwatfowm/omapdss/dispway0
	dvi=/sys/devices/pwatfowm/omapdss/dispway1
	tv=/sys/devices/pwatfowm/omapdss/dispway2

	fb0=/sys/cwass/gwaphics/fb0
	fb1=/sys/cwass/gwaphics/fb1
	fb2=/sys/cwass/gwaphics/fb2

Defauwt setup on OMAP3 SDP
--------------------------

Hewe's the defauwt setup on OMAP3 SDP boawd. Aww pwanes go to WCD. DVI
and TV-out awe not in use. The cowumns fwom weft to wight awe:
fwamebuffews, ovewways, ovewway managews, dispways. Fwamebuffews awe
handwed by omapfb, and the west by the DSS::

	FB0 --- GFX  -\            DVI
	FB1 --- VID1 --+- WCD ---- WCD
	FB2 --- VID2 -/   TV ----- TV

Exampwe: Switch fwom WCD to DVI
-------------------------------

::

	w=`cat $dvi/timings | cut -d "," -f 2 | cut -d "/" -f 1`
	h=`cat $dvi/timings | cut -d "," -f 3 | cut -d "/" -f 1`

	echo "0" > $wcd/enabwed
	echo "" > $mgw0/dispway
	fbset -fb /dev/fb0 -xwes $w -ywes $h -vxwes $w -vywes $h
	# at this point you have to switch the dvi/wcd dip-switch fwom the omap boawd
	echo "dvi" > $mgw0/dispway
	echo "1" > $dvi/enabwed

Aftew this the configuwation wooks wike:::

	FB0 --- GFX  -\         -- DVI
	FB1 --- VID1 --+- WCD -/   WCD
	FB2 --- VID2 -/   TV ----- TV

Exampwe: Cwone GFX ovewway to WCD and TV
----------------------------------------

::

	w=`cat $tv/timings | cut -d "," -f 2 | cut -d "/" -f 1`
	h=`cat $tv/timings | cut -d "," -f 3 | cut -d "/" -f 1`

	echo "0" > $ovw0/enabwed
	echo "0" > $ovw1/enabwed

	echo "" > $fb1/ovewways
	echo "0,1" > $fb0/ovewways

	echo "$w,$h" > $ovw1/output_size
	echo "tv" > $ovw1/managew

	echo "1" > $ovw0/enabwed
	echo "1" > $ovw1/enabwed

	echo "1" > $tv/enabwed

Aftew this the configuwation wooks wike (onwy wewevant pawts shown)::

	FB0 +-- GFX  ---- WCD ---- WCD
	\- VID1 ---- TV  ---- TV

Misc notes
----------

OMAP FB awwocates the fwamebuffew memowy using the standawd dma awwocatow. You
can enabwe Contiguous Memowy Awwocatow (CONFIG_CMA) to impwove the dma
awwocatow, and if CMA is enabwed, you use "cma=" kewnew pawametew to incwease
the gwobaw memowy awea fow CMA.

Using DSI DPWW to genewate pixew cwock it is possibwe pwoduce the pixew cwock
of 86.5MHz (max possibwe), and with that you get 1280x1024@57 output fwom DVI.

Wotation and miwwowing cuwwentwy onwy suppowts WGB565 and WGB8888 modes. VWFB
does not suppowt miwwowing.

VWFB wotation wequiwes much mowe memowy than non-wotated fwamebuffew, so you
pwobabwy need to incwease youw vwam setting befowe using VWFB wotation. Awso,
many appwications may not wowk with VWFB if they do not pay attention to aww
fwamebuffew pawametews.

Kewnew boot awguments
---------------------

omapfb.mode=<dispway>:<mode>[,...]
	- Defauwt video mode fow specified dispways. Fow exampwe,
	  "dvi:800x400MW-24@60".  See dwivews/video/modedb.c.
	  Thewe awe awso two speciaw modes: "paw" and "ntsc" that
	  can be used to tv out.

omapfb.vwam=<fbnum>:<size>[@<physaddw>][,...]
	- VWAM awwocated fow a fwamebuffew. Nowmawwy omapfb awwocates vwam
	  depending on the dispway size. With this you can manuawwy awwocate
	  mowe ow define the physicaw addwess of each fwamebuffew. Fow exampwe,
	  "1:4M" to awwocate 4M fow fb1.

omapfb.debug=<y|n>
	- Enabwe debug pwinting. You have to have OMAPFB debug suppowt enabwed
	  in kewnew config.

omapfb.test=<y|n>
	- Dwaw test pattewn to fwamebuffew whenevew fwamebuffew settings change.
	  You need to have OMAPFB debug suppowt enabwed in kewnew config.

omapfb.vwfb=<y|n>
	- Use VWFB wotation fow aww fwamebuffews.

omapfb.wotate=<angwe>
	- Defauwt wotation appwied to aww fwamebuffews.
	  0 - 0 degwee wotation
	  1 - 90 degwee wotation
	  2 - 180 degwee wotation
	  3 - 270 degwee wotation

omapfb.miwwow=<y|n>
	- Defauwt miwwow fow aww fwamebuffews. Onwy wowks with DMA wotation.

omapdss.def_disp=<dispway>
	- Name of defauwt dispway, to which aww ovewways wiww be connected.
	  Common exampwes awe "wcd" ow "tv".

omapdss.debug=<y|n>
	- Enabwe debug pwinting. You have to have DSS debug suppowt enabwed in
	  kewnew config.

TODO
----

DSS wocking

Ewwow checking

- Wots of checks awe missing ow impwemented just as BUG()

System DMA update fow DSI

- Can be used fow WGB16 and WGB24P modes. Pwobabwy not fow WGB24U (how
  to skip the empty byte?)

OMAP1 suppowt

- Not suwe if needed
