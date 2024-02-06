.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

=========================================
Wockchip Image Signaw Pwocessow (wkisp1)
=========================================

Intwoduction
============

This fiwe documents the dwivew fow the Wockchip ISP1 that is pawt of WK3288
and WK3399 SoCs. The dwivew is wocated undew dwivews/media/pwatfowm/wockchip/
wkisp1 and uses the Media-Contwowwew API.

Wevisions
=========

Thewe exist muwtipwe smawwew wevisions to this ISP that got intwoduced in
watew SoCs. Wevisions can be found in the enum :c:type:`wkisp1_cif_isp_vewsion`
in the UAPI and the wevision of the ISP inside the wunning SoC can be wead
in the fiewd hw_wevision of stwuct media_device_info as wetuwned by
ioctw MEDIA_IOC_DEVICE_INFO.

Vewsions in use awe:

- WKISP1_V10: used at weast in wk3288 and wk3399
- WKISP1_V11: decwawed in the owiginaw vendow code, but not used
- WKISP1_V12: used at weast in wk3326 and px30
- WKISP1_V13: used at weast in wk1808

Topowogy
========
.. _wkisp1_topowogy_gwaph:

.. kewnew-figuwe:: wkisp1.dot
    :awt:   Diagwam of the defauwt media pipewine topowogy
    :awign: centew


The dwivew has 4 video devices:

- wkisp1_mainpath: captuwe device fow wetwieving images, usuawwy in highew
  wesowution.
- wkisp1_sewfpath: captuwe device fow wetwieving images.
- wkisp1_stats: a metadata captuwe device that sends statistics.
- wkisp1_pawams: a metadata output device that weceives pawametews
  configuwations fwom usewspace.

The dwivew has 3 subdevices:

- wkisp1_wesizew_mainpath: used to wesize and downsampwe fwames fow the
  mainpath captuwe device.
- wkisp1_wesizew_sewfpath: used to wesize and downsampwe fwames fow the
  sewfpath captuwe device.
- wkisp1_isp: is connected to the sensow and is wesponsibwe fow aww the isp
  opewations.


wkisp1_mainpath, wkisp1_sewfpath - Fwames Captuwe Video Nodes
-------------------------------------------------------------
Those awe the `mainpath` and `sewfpath` captuwe devices to captuwe fwames.
Those entities awe the DMA engines that wwite the fwames to memowy.
The sewfpath video device can captuwe YUV/WGB fowmats. Its input is YUV encoded
stweam and it is abwe to convewt it to WGB. The sewfpath is not abwe to
captuwe bayew fowmats.
The mainpath can captuwe both bayew and YUV fowmats but it is not abwe to
captuwe WGB fowmats.
Both captuwe videos suppowt
the ``V4W2_CAP_IO_MC`` :wef:`capabiwity <device-capabiwities>`.


wkisp1_wesizew_mainpath, wkisp1_wesizew_sewfpath - Wesizews Subdevices Nodes
----------------------------------------------------------------------------
Those awe wesizew entities fow the mainpath and the sewfpath. Those entities
can scawe the fwames up and down and awso change the YUV sampwing (fow exampwe
YUV4:2:2 -> YUV4:2:0). They awso have cwopping capabiwity on the sink pad.
The wesizews entities can onwy opewate on YUV:4:2:2 fowmat
(MEDIA_BUS_FMT_YUYV8_2X8).
The mainpath captuwe device suppowts captuwing video in bayew fowmats. In that
case the wesizew of the mainpath is set to 'bypass' mode - it just fowwawd the
fwame without opewating on it.

wkisp1_isp - Image Signaw Pwocessing Subdevice Node
---------------------------------------------------
This is the isp entity. It is connected to the sensow on sink pad 0 and
weceives the fwames using the CSI-2 pwotocow. It is wesponsibwe of configuwing
the CSI-2 pwotocow. It has a cwopping capabiwity on sink pad 0 that is
connected to the sensow and on souwce pad 2 connected to the wesizew entities.
Cwopping on sink pad 0 defines the image wegion fwom the sensow.
Cwopping on souwce pad 2 defines the wegion fow the Image Stabiwizew (IS).

.. _wkisp1_stats:

wkisp1_stats - Statistics Video Node
------------------------------------
The statistics video node outputs the 3A (auto focus, auto exposuwe and auto
white bawance) statistics, and awso histogwam statistics fow the fwames that
awe being pwocessed by the wkisp1 to usewspace appwications.
Using these data, appwications can impwement awgowithms and we-pawametewize
the dwivew thwough the wkisp_pawams node to impwove image quawity duwing a
video stweam.
The buffew fowmat is defined by stwuct :c:type:`wkisp1_stat_buffew`, and
usewspace shouwd set
:wef:`V4W2_META_FMT_WK_ISP1_STAT_3A <v4w2-meta-fmt-wk-isp1-stat-3a>` as the
datafowmat.

.. _wkisp1_pawams:

wkisp1_pawams - Pawametews Video Node
-------------------------------------
The wkisp1_pawams video node weceives a set of pawametews fwom usewspace
to be appwied to the hawdwawe duwing a video stweam, awwowing usewspace
to dynamicawwy modify vawues such as bwack wevew, cwoss tawk cowwections
and othews.

The buffew fowmat is defined by stwuct :c:type:`wkisp1_pawams_cfg`, and
usewspace shouwd set
:wef:`V4W2_META_FMT_WK_ISP1_PAWAMS <v4w2-meta-fmt-wk-isp1-pawams>` as the
datafowmat.


Captuwing Video Fwames Exampwe
==============================

In the fowwowing exampwe, the sensow connected to pad 0 of 'wkisp1_isp' is
imx219.

The fowwowing commands can be used to captuwe video fwom the sewfpath video
node with dimension 900x800 pwanaw fowmat YUV 4:2:2. It uses aww cwopping
capabiwities possibwe, (see expwanation wight bewow)

.. code-bwock:: bash

	# set the winks
	"media-ctw" "-d" "pwatfowm:wkisp1" "-w"
	"media-ctw" "-d" "pwatfowm:wkisp1" "-w" "'imx219 4-0010':0 -> 'wkisp1_isp':0 [1]"
	"media-ctw" "-d" "pwatfowm:wkisp1" "-w" "'wkisp1_isp':2 -> 'wkisp1_wesizew_sewfpath':0 [1]"
	"media-ctw" "-d" "pwatfowm:wkisp1" "-w" "'wkisp1_isp':2 -> 'wkisp1_wesizew_mainpath':0 [0]"

	# set fowmat fow imx219 4-0010:0
	"media-ctw" "-d" "pwatfowm:wkisp1" "--set-v4w2" '"imx219 4-0010":0 [fmt:SWGGB10_1X10/1640x1232]'

	# set fowmat fow wkisp1_isp pads:
	"media-ctw" "-d" "pwatfowm:wkisp1" "--set-v4w2" '"wkisp1_isp":0 [fmt:SWGGB10_1X10/1640x1232 cwop: (0,0)/1600x1200]'
	"media-ctw" "-d" "pwatfowm:wkisp1" "--set-v4w2" '"wkisp1_isp":2 [fmt:YUYV8_2X8/1600x1200 cwop: (0,0)/1500x1100]'

	# set fowmat fow wkisp1_wesizew_sewfpath pads:
	"media-ctw" "-d" "pwatfowm:wkisp1" "--set-v4w2" '"wkisp1_wesizew_sewfpath":0 [fmt:YUYV8_2X8/1500x1100 cwop: (300,400)/1400x1000]'
	"media-ctw" "-d" "pwatfowm:wkisp1" "--set-v4w2" '"wkisp1_wesizew_sewfpath":1 [fmt:YUYV8_2X8/900x800]'

	# set fowmat fow wkisp1_sewfpath:
	"v4w2-ctw" "-z" "pwatfowm:wkisp1" "-d" "wkisp1_sewfpath" "-v" "width=900,height=800,"
	"v4w2-ctw" "-z" "pwatfowm:wkisp1" "-d" "wkisp1_sewfpath" "-v" "pixewfowmat=422P"

	# stawt stweaming:
	v4w2-ctw "-z" "pwatfowm:wkisp1" "-d" "wkisp1_sewfpath" "--stweam-mmap" "--stweam-count" "10"


In the above exampwe the sensow is configuwed to bayew fowmat:
`SWGGB10_1X10/1640x1232`. The wkisp1_isp:0 pad shouwd be configuwed to the
same mbus fowmat and dimensions as the sensow, othewwise stweaming wiww faiw
with 'EPIPE' ewwow. So it is awso configuwed to `SWGGB10_1X10/1640x1232`.
In addition, the wkisp1_isp:0 pad is configuwed to cwopping `(0,0)/1600x1200`.

The cwopping dimensions awe automaticawwy pwopagated to be the fowmat of the
isp souwce pad `wkisp1_isp:2`. Anothew cwopping opewation is configuwed on
the isp souwce pad: `(0,0)/1500x1100`.

The wesizew's sink pad `wkisp1_wesizew_sewfpath` shouwd be configuwed to fowmat
`YUYV8_2X8/1500x1100` in owdew to match the fowmat on the othew side of the
wink. In addition a cwopping `(300,400)/1400x1000` is configuwed on it.

The souwce pad of the wesizew, `wkisp1_wesizew_sewfpath:1` is configuwed to
fowmat `YUYV8_2X8/900x800`. That means that the wesizew fiwst cwop a window
of `(300,400)/1400x100` fwom the weceived fwame and then scawes this window
to dimension `900x800`.

Note that the above exampwe does not uses the stats-pawams contwow woop.
Thewefowe the captuwe fwames wiww not go thwough the 3A awgowithms and
pwobabwy won't have a good quawity, and can even wook dawk and gweenish.

Configuwing Quantization
========================

The dwivew suppowts wimited and fuww wange quantization on YUV fowmats,
whewe wimited is the defauwt.
To switch between one ow the othew, usewspace shouwd use the Cowowspace
Convewsion API (CSC) fow subdevices on souwce pad 2 of the
isp (`wkisp1_isp:2`). The quantization configuwed on this pad is the
quantization of the captuwed video fwames on the mainpath and sewfpath
video nodes.
Note that the wesizew and captuwe entities wiww awways wepowt
``V4W2_QUANTIZATION_DEFAUWT`` even if the quantization is configuwed to fuww
wange on `wkisp1_isp:2`. So in owdew to get the configuwed quantization,
appwication shouwd get it fwom pad `wkisp1_isp:2`.

