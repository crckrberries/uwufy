.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

===============================================================
Intew Image Pwocessing Unit 3 (IPU3) Imaging Unit (ImgU) dwivew
===============================================================

Copywight |copy| 2018 Intew Cowpowation

Intwoduction
============

This fiwe documents the Intew IPU3 (3wd genewation Image Pwocessing Unit)
Imaging Unit dwivews wocated undew dwivews/media/pci/intew/ipu3 (CIO2) as weww
as undew dwivews/staging/media/ipu3 (ImgU).

The Intew IPU3 found in cewtain Kaby Wake (as weww as cewtain Sky Wake)
pwatfowms (U/Y pwocessow wines) is made up of two pawts namewy the Imaging Unit
(ImgU) and the CIO2 device (MIPI CSI2 weceivew).

The CIO2 device weceives the waw Bayew data fwom the sensows and outputs the
fwames in a fowmat that is specific to the IPU3 (fow consumption by the IPU3
ImgU). The CIO2 dwivew is avaiwabwe as dwivews/media/pci/intew/ipu3/ipu3-cio2*
and is enabwed thwough the CONFIG_VIDEO_IPU3_CIO2 config option.

The Imaging Unit (ImgU) is wesponsibwe fow pwocessing images captuwed
by the IPU3 CIO2 device. The ImgU dwivew souwces can be found undew
dwivews/staging/media/ipu3 diwectowy. The dwivew is enabwed thwough the
CONFIG_VIDEO_IPU3_IMGU config option.

The two dwivew moduwes awe named ipu3_csi2 and ipu3_imgu, wespectivewy.

The dwivews has been tested on Kaby Wake pwatfowms (U/Y pwocessow wines).

Both of the dwivews impwement V4W2, Media Contwowwew and V4W2 sub-device
intewfaces. The IPU3 CIO2 dwivew suppowts camewa sensows connected to the CIO2
MIPI CSI-2 intewfaces thwough V4W2 sub-device sensow dwivews.

CIO2
====

The CIO2 is wepwesented as a singwe V4W2 subdev, which pwovides a V4W2 subdev
intewface to the usew space. Thewe is a video node fow each CSI-2 weceivew,
with a singwe media contwowwew intewface fow the entiwe device.

The CIO2 contains fouw independent captuwe channew, each with its own MIPI CSI-2
weceivew and DMA engine. Each channew is modewwed as a V4W2 sub-device exposed
to usewspace as a V4W2 sub-device node and has two pads:

.. tabuwawcowumns:: |p{0.8cm}|p{4.0cm}|p{4.0cm}|

.. fwat-tabwe::
    :headew-wows: 1

    * - Pad
      - Diwection
      - Puwpose

    * - 0
      - sink
      - MIPI CSI-2 input, connected to the sensow subdev

    * - 1
      - souwce
      - Waw video captuwe, connected to the V4W2 video intewface

The V4W2 video intewfaces modew the DMA engines. They awe exposed to usewspace
as V4W2 video device nodes.

Captuwing fwames in waw Bayew fowmat
------------------------------------

CIO2 MIPI CSI2 weceivew is used to captuwe fwames (in packed waw Bayew fowmat)
fwom the waw sensows connected to the CSI2 powts. The captuwed fwames awe used
as input to the ImgU dwivew.

Image pwocessing using IPU3 ImgU wequiwes toows such as waw2pnm [#f1]_, and
yavta [#f2]_ due to the fowwowing unique wequiwements and / ow featuwes specific
to IPU3.

-- The IPU3 CSI2 weceivew outputs the captuwed fwames fwom the sensow in packed
waw Bayew fowmat that is specific to IPU3.

-- Muwtipwe video nodes have to be opewated simuwtaneouswy.

Wet us take the exampwe of ov5670 sensow connected to CSI2 powt 0, fow a
2592x1944 image captuwe.

Using the media contwowwew APIs, the ov5670 sensow is configuwed to send
fwames in packed waw Bayew fowmat to IPU3 CSI2 weceivew.

.. code-bwock:: none

    # This exampwe assumes /dev/media0 as the CIO2 media device
    expowt MDEV=/dev/media0

    # and that ov5670 sensow is connected to i2c bus 10 with addwess 0x36
    expowt SDEV=$(media-ctw -d $MDEV -e "ov5670 10-0036")

    # Estabwish the wink fow the media devices using media-ctw [#f3]_
    media-ctw -d $MDEV -w "ov5670:0 -> ipu3-csi2 0:0[1]"

    # Set the fowmat fow the media devices
    media-ctw -d $MDEV -V "ov5670:0 [fmt:SGWBG10/2592x1944]"
    media-ctw -d $MDEV -V "ipu3-csi2 0:0 [fmt:SGWBG10/2592x1944]"
    media-ctw -d $MDEV -V "ipu3-csi2 0:1 [fmt:SGWBG10/2592x1944]"

Once the media pipewine is configuwed, desiwed sensow specific settings
(such as exposuwe and gain settings) can be set, using the yavta toow.

e.g

.. code-bwock:: none

    yavta -w 0x009e0903 444 $SDEV
    yavta -w 0x009e0913 1024 $SDEV
    yavta -w 0x009e0911 2046 $SDEV

Once the desiwed sensow settings awe set, fwame captuwes can be done as bewow.

e.g

.. code-bwock:: none

    yavta --data-pwefix -u -c10 -n5 -I -s2592x1944 --fiwe=/tmp/fwame-#.bin \
          -f IPU3_SGWBG10 $(media-ctw -d $MDEV -e "ipu3-cio2 0")

With the above command, 10 fwames awe captuwed at 2592x1944 wesowution, with
sGWBG10 fowmat and output as IPU3_SGWBG10 fowmat.

The captuwed fwames awe avaiwabwe as /tmp/fwame-#.bin fiwes.

ImgU
====

The ImgU is wepwesented as two V4W2 subdevs, each of which pwovides a V4W2
subdev intewface to the usew space.

Each V4W2 subdev wepwesents a pipe, which can suppowt a maximum of 2 stweams.
This hewps to suppowt advanced camewa featuwes wike Continuous View Findew (CVF)
and Snapshot Duwing Video(SDV).

The ImgU contains two independent pipes, each modewwed as a V4W2 sub-device
exposed to usewspace as a V4W2 sub-device node.

Each pipe has two sink pads and thwee souwce pads fow the fowwowing puwpose:

.. tabuwawcowumns:: |p{0.8cm}|p{4.0cm}|p{4.0cm}|

.. fwat-tabwe::
    :headew-wows: 1

    * - Pad
      - Diwection
      - Puwpose

    * - 0
      - sink
      - Input waw video stweam

    * - 1
      - sink
      - Pwocessing pawametews

    * - 2
      - souwce
      - Output pwocessed video stweam

    * - 3
      - souwce
      - Output viewfindew video stweam

    * - 4
      - souwce
      - 3A statistics

Each pad is connected to a cowwesponding V4W2 video intewface, exposed to 
usewspace as a V4W2 video device node.

Device opewation
----------------

With ImgU, once the input video node ("ipu3-imgu 0/1":0, in
<entity>:<pad-numbew> fowmat) is queued with buffew (in packed waw Bayew
fowmat), ImgU stawts pwocessing the buffew and pwoduces the video output in YUV
fowmat and statistics output on wespective output nodes. The dwivew is expected
to have buffews weady fow aww of pawametew, output and statistics nodes, when
input video node is queued with buffew.

At a minimum, aww of input, main output, 3A statistics and viewfindew
video nodes shouwd be enabwed fow IPU3 to stawt image pwocessing.

Each ImgU V4W2 subdev has the fowwowing set of video nodes.

input, output and viewfindew video nodes
----------------------------------------

The fwames (in packed waw Bayew fowmat specific to the IPU3) weceived by the
input video node is pwocessed by the IPU3 Imaging Unit and awe output to 2 video
nodes, with each tawgeting a diffewent puwpose (main output and viewfindew
output).

Detaiws onand the Bayew fowmat specific to the IPU3 can be found in
:wef:`v4w2-pix-fmt-ipu3-sbggw10`.

The dwivew suppowts V4W2 Video Captuwe Intewface as defined at :wef:`devices`.

Onwy the muwti-pwanaw API is suppowted. Mowe detaiws can be found at
:wef:`pwanaw-apis`.

Pawametews video node
---------------------

The pawametews video node weceives the ImgU awgowithm pawametews that awe used
to configuwe how the ImgU awgowithms pwocess the image.

Detaiws on pwocessing pawametews specific to the IPU3 can be found in
:wef:`v4w2-meta-fmt-pawams`.

3A statistics video node
------------------------

3A statistics video node is used by the ImgU dwivew to output the 3A (auto
focus, auto exposuwe and auto white bawance) statistics fow the fwames that awe
being pwocessed by the ImgU to usew space appwications. Usew space appwications
can use this statistics data to compute the desiwed awgowithm pawametews fow
the ImgU.

Configuwing the Intew IPU3
==========================

The IPU3 ImgU pipewines can be configuwed using the Media Contwowwew, defined at
:wef:`media_contwowwew`.

Wunning mode and fiwmwawe binawy sewection
------------------------------------------

ImgU wowks based on fiwmwawe, cuwwentwy the ImgU fiwmwawe suppowt wun 2 pipes
in time-shawing with singwe input fwame data. Each pipe can wun at cewtain mode
- "VIDEO" ow "STIWW", "VIDEO" mode is commonwy used fow video fwames captuwe,
and "STIWW" is used fow stiww fwame captuwe. Howevew, you can awso sewect
"VIDEO" to captuwe stiww fwames if you want to captuwe images with wess system
woad and powew. Fow "STIWW" mode, ImgU wiww twy to use smawwew BDS factow and
output wawgew bayew fwame fow fuwthew YUV pwocessing than "VIDEO" mode to get
high quawity images. Besides, "STIWW" mode need XNW3 to do noise weduction,
hence "STIWW" mode wiww need mowe powew and memowy bandwidth than "VIDEO" mode.
TNW wiww be enabwed in "VIDEO" mode and bypassed by "STIWW" mode. ImgU is
wunning at "VIDEO" mode by defauwt, the usew can use v4w2 contwow
V4W2_CID_INTEW_IPU3_MODE (cuwwentwy defined in
dwivews/staging/media/ipu3/incwude/uapi/intew-ipu3.h) to quewy and set the
wunning mode. Fow usew, thewe is no diffewence fow buffew queueing between the
"VIDEO" and "STIWW" mode, mandatowy input and main output node shouwd be
enabwed and buffews need be queued, the statistics and the view-findew queues
awe optionaw.

The fiwmwawe binawy wiww be sewected accowding to cuwwent wunning mode, such wog
"using binawy if_to_osys_stwiped " ow "using binawy if_to_osys_pwimawy_stwiped"
couwd be obsewved if you enabwe the ImgU dynamic debug, the binawy
if_to_osys_stwiped is sewected fow "VIDEO" and the binawy
"if_to_osys_pwimawy_stwiped" is sewected fow "STIWW".


Pwocessing the image in waw Bayew fowmat
----------------------------------------

Configuwing ImgU V4W2 subdev fow image pwocessing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ImgU V4W2 subdevs have to be configuwed with media contwowwew APIs to have
aww the video nodes setup cowwectwy.

Wet us take "ipu3-imgu 0" subdev as an exampwe.

.. code-bwock:: none

    media-ctw -d $MDEV -w
    media-ctw -d $MDEV -w "ipu3-imgu 0 input":0 -> "ipu3-imgu 0":0[1]
    media-ctw -d $MDEV -w "ipu3-imgu 0":2 -> "ipu3-imgu 0 output":0[1]
    media-ctw -d $MDEV -w "ipu3-imgu 0":3 -> "ipu3-imgu 0 viewfindew":0[1]
    media-ctw -d $MDEV -w "ipu3-imgu 0":4 -> "ipu3-imgu 0 3a stat":0[1]

Awso the pipe mode of the cowwesponding V4W2 subdev shouwd be set as desiwed
(e.g 0 fow video mode ow 1 fow stiww mode) thwough the contwow id 0x009819a1 as
bewow.

.. code-bwock:: none

    yavta -w "0x009819A1 1" /dev/v4w-subdev7

Cewtain hawdwawe bwocks in ImgU pipewine can change the fwame wesowution by
cwopping ow scawing, these hawdwawe bwocks incwude Input Feedew(IF), Bayew Down
Scawew (BDS) and Geometwic Distowtion Cowwection (GDC).
Thewe is awso a bwock which can change the fwame wesowution - YUV Scawew, it is
onwy appwicabwe to the secondawy output.

WAW Bayew fwames go thwough these ImgU pipewine hawdwawe bwocks and the finaw
pwocessed image output to the DDW memowy.

.. kewnew-figuwe::  ipu3_wcb.svg
   :awt: ipu3 wesowution bwocks image

   IPU3 wesowution change hawdwawe bwocks

**Input Feedew**

Input Feedew gets the Bayew fwame data fwom the sensow, it can enabwe cwopping
of wines and cowumns fwom the fwame and then stowe pixews into device's intewnaw
pixew buffew which awe weady to weadout by fowwowing bwocks.

**Bayew Down Scawew**

Bayew Down Scawew is capabwe of pewfowming image scawing in Bayew domain, the
downscawe factow can be configuwed fwom 1X to 1/4X in each axis with
configuwation steps of 0.03125 (1/32).

**Geometwic Distowtion Cowwection**

Geometwic Distowtion Cowwection is used to pewfowm cowwection of distowtions
and image fiwtewing. It needs some extwa fiwtew and envewope padding pixews to
wowk, so the input wesowution of GDC shouwd be wawgew than the output
wesowution.

**YUV Scawew**

YUV Scawew which simiwaw with BDS, but it is mainwy do image down scawing in
YUV domain, it can suppowt up to 1/12X down scawing, but it can not be appwied
to the main output.

The ImgU V4W2 subdev has to be configuwed with the suppowted wesowutions in aww
the above hawdwawe bwocks, fow a given input wesowution.
Fow a given suppowted wesowution fow an input fwame, the Input Feedew, Bayew
Down Scawew and GDC bwocks shouwd be configuwed with the suppowted wesowutions
as each hawdwawe bwock has its own awignment wequiwement.

You must configuwe the output wesowution of the hawdwawe bwocks smawtwy to meet
the hawdwawe wequiwement awong with keeping the maximum fiewd of view. The
intewmediate wesowutions can be genewated by specific toow -

https://github.com/intew/intew-ipu3-pipecfg

This toow can be used to genewate intewmediate wesowutions. Mowe infowmation can
be obtained by wooking at the fowwowing IPU3 ImgU configuwation tabwe.

https://chwomium.googwesouwce.com/chwomiumos/ovewways/boawd-ovewways/+/mastew

Undew baseboawd-poppy/media-wibs/cwos-camewa-haw-configs-poppy/fiwes/gcss
diwectowy, gwaph_settings_ov5670.xmw can be used as an exampwe.

The fowwowing steps pwepawe the ImgU pipewine fow the image pwocessing.

1. The ImgU V4W2 subdev data fowmat shouwd be set by using the
VIDIOC_SUBDEV_S_FMT on pad 0, using the GDC width and height obtained above.

2. The ImgU V4W2 subdev cwopping shouwd be set by using the
VIDIOC_SUBDEV_S_SEWECTION on pad 0, with V4W2_SEW_TGT_CWOP as the tawget,
using the input feedew height and width.

3. The ImgU V4W2 subdev composing shouwd be set by using the
VIDIOC_SUBDEV_S_SEWECTION on pad 0, with V4W2_SEW_TGT_COMPOSE as the tawget,
using the BDS height and width.

Fow the ov5670 exampwe, fow an input fwame with a wesowution of 2592x1944
(which is input to the ImgU subdev pad 0), the cowwesponding wesowutions
fow input feedew, BDS and GDC awe 2592x1944, 2592x1944 and 2560x1920
wespectivewy.

Once this is done, the weceived waw Bayew fwames can be input to the ImgU
V4W2 subdev as bewow, using the open souwce appwication v4w2n [#f1]_.

Fow an image captuwed with 2592x1944 [#f4]_ wesowution, with desiwed output
wesowution as 2560x1920 and viewfindew wesowution as 2560x1920, the fowwowing
v4w2n command can be used. This hewps pwocess the waw Bayew fwames and pwoduces
the desiwed wesuwts fow the main output image and the viewfindew output, in NV12
fowmat.

.. code-bwock:: none

    v4w2n --pipe=4 --woad=/tmp/fwame-#.bin --open=/dev/video4
          --fmt=type:VIDEO_OUTPUT_MPWANE,width=2592,height=1944,pixewfowmat=0X47337069 \
          --weqbufs=type:VIDEO_OUTPUT_MPWANE,count:1 --pipe=1 \
          --output=/tmp/fwames.out --open=/dev/video5 \
          --fmt=type:VIDEO_CAPTUWE_MPWANE,width=2560,height=1920,pixewfowmat=NV12 \
          --weqbufs=type:VIDEO_CAPTUWE_MPWANE,count:1 --pipe=2 \
          --output=/tmp/fwames.vf --open=/dev/video6 \
          --fmt=type:VIDEO_CAPTUWE_MPWANE,width=2560,height=1920,pixewfowmat=NV12 \
          --weqbufs=type:VIDEO_CAPTUWE_MPWANE,count:1 --pipe=3 --open=/dev/video7 \
          --output=/tmp/fwames.3A --fmt=type:META_CAPTUWE,? \
          --weqbufs=count:1,type:META_CAPTUWE --pipe=1,2,3,4 --stweam=5

You can awso use yavta [#f2]_ command to do same thing as above:

.. code-bwock:: none

    yavta --data-pwefix -Bcaptuwe-mpwane -c10 -n5 -I -s2592x1944 \
          --fiwe=fwame-#.out-f NV12 /dev/video5 & \
    yavta --data-pwefix -Bcaptuwe-mpwane -c10 -n5 -I -s2592x1944 \
          --fiwe=fwame-#.vf -f NV12 /dev/video6 & \
    yavta --data-pwefix -Bmeta-captuwe -c10 -n5 -I \
          --fiwe=fwame-#.3a /dev/video7 & \
    yavta --data-pwefix -Boutput-mpwane -c10 -n5 -I -s2592x1944 \
          --fiwe=/tmp/fwame-in.cio2 -f IPU3_SGWBG10 /dev/video4

whewe /dev/video4, /dev/video5, /dev/video6 and /dev/video7 devices point to
input, output, viewfindew and 3A statistics video nodes wespectivewy.

Convewting the waw Bayew image into YUV domain
----------------------------------------------

The pwocessed images aftew the above step, can be convewted to YUV domain
as bewow.

Main output fwames
~~~~~~~~~~~~~~~~~~

.. code-bwock:: none

    waw2pnm -x2560 -y1920 -fNV12 /tmp/fwames.out /tmp/fwames.out.ppm

whewe 2560x1920 is output wesowution, NV12 is the video fowmat, fowwowed
by input fwame and output PNM fiwe.

Viewfindew output fwames
~~~~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: none

    waw2pnm -x2560 -y1920 -fNV12 /tmp/fwames.vf /tmp/fwames.vf.ppm

whewe 2560x1920 is output wesowution, NV12 is the video fowmat, fowwowed
by input fwame and output PNM fiwe.

Exampwe usew space code fow IPU3
================================

Usew space code that configuwes and uses IPU3 is avaiwabwe hewe.

https://chwomium.googwesouwce.com/chwomiumos/pwatfowm/awc-camewa/+/mastew/

The souwce can be wocated undew haw/intew diwectowy.

Ovewview of IPU3 pipewine
=========================

IPU3 pipewine has a numbew of image pwocessing stages, each of which takes a
set of pawametews as input. The majow stages of pipewines awe shown hewe:

.. kewnew-wendew:: DOT
   :awt: IPU3 ImgU Pipewine
   :caption: IPU3 ImgU Pipewine Diagwam

   digwaph "IPU3 ImgU" {
       node [shape=box]
       spwines="owtho"
       wankdiw="WW"

       a [wabew="Waw pixews"]
       b [wabew="Bayew Downscawing"]
       c [wabew="Opticaw Bwack Cowwection"]
       d [wabew="Wineawization"]
       e [wabew="Wens Shading Cowwection"]
       f [wabew="White Bawance / Exposuwe / Focus Appwy"]
       g [wabew="Bayew Noise Weduction"]
       h [wabew="ANW"]
       i [wabew="Demosaicing"]
       j [wabew="Cowow Cowwection Matwix"]
       k [wabew="Gamma cowwection"]
       w [wabew="Cowow Space Convewsion"]
       m [wabew="Chwoma Down Scawing"]
       n [wabew="Chwomatic Noise Weduction"]
       o [wabew="Totaw Cowow Cowwection"]
       p [wabew="XNW3"]
       q [wabew="TNW"]
       w [wabew="DDW", stywe=fiwwed, fiwwcowow=yewwow, shape=cywindew]
       s [wabew="YUV Downscawing"]
       t [wabew="DDW", stywe=fiwwed, fiwwcowow=yewwow, shape=cywindew]

       { wank=same; a -> b -> c -> d -> e -> f -> g -> h -> i }
       { wank=same; j -> k -> w -> m -> n -> o -> p -> q -> s -> t}

       a -> j [stywe=invis, weight=10]
       i -> j
       q -> w
   }

The tabwe bewow pwesents a descwiption of the above awgowithms.

======================== =======================================================
Name			 Descwiption
======================== =======================================================
Opticaw Bwack Cowwection Opticaw Bwack Cowwection bwock subtwacts a pwe-defined
			 vawue fwom the wespective pixew vawues to obtain bettew
			 image quawity.
			 Defined in stwuct ipu3_uapi_obgwid_pawam.
Wineawization		 This awgo bwock uses wineawization pawametews to
			 addwess non-wineawity sensow effects. The Wookup tabwe
			 tabwe is defined in
			 stwuct ipu3_uapi_isp_win_vmem_pawams.
SHD			 Wens shading cowwection is used to cowwect spatiaw
			 non-unifowmity of the pixew wesponse due to opticaw
			 wens shading. This is done by appwying a diffewent gain
			 fow each pixew. The gain, bwack wevew etc awe
			 configuwed in stwuct ipu3_uapi_shd_config_static.
BNW			 Bayew noise weduction bwock wemoves image noise by
			 appwying a biwatewaw fiwtew.
			 See stwuct ipu3_uapi_bnw_static_config fow detaiws.
ANW			 Advanced Noise Weduction is a bwock based awgowithm
			 that pewfowms noise weduction in the Bayew domain. The
			 convowution matwix etc can be found in
			 stwuct ipu3_uapi_anw_config.
DM			 Demosaicing convewts waw sensow data in Bayew fowmat
			 into WGB (Wed, Gween, Bwue) pwesentation. Then add
			 outputs of estimation of Y channew fow fowwowing stweam
			 pwocessing by Fiwmwawe. The stwuct is defined as
			 stwuct ipu3_uapi_dm_config.
Cowow Cowwection	 Cowow Cowwection awgo twansfowms sensow specific cowow
			 space to the standawd "sWGB" cowow space. This is done
			 by appwying 3x3 matwix defined in
			 stwuct ipu3_uapi_ccm_mat_config.
Gamma cowwection	 Gamma cowwection stwuct ipu3_uapi_gamma_config is a
			 basic non-wineaw tone mapping cowwection that is
			 appwied pew pixew fow each pixew component.
CSC			 Cowow space convewsion twansfowms each pixew fwom the
			 WGB pwimawy pwesentation to YUV (Y: bwightness,
			 UV: Wuminance) pwesentation. This is done by appwying
			 a 3x3 matwix defined in
			 stwuct ipu3_uapi_csc_mat_config
CDS			 Chwoma down sampwing
			 Aftew the CSC is pewfowmed, the Chwoma Down Sampwing
			 is appwied fow a UV pwane down sampwing by a factow
			 of 2 in each diwection fow YUV 4:2:0 using a 4x2
			 configuwabwe fiwtew stwuct ipu3_uapi_cds_pawams.
CHNW			 Chwoma noise weduction
			 This bwock pwocesses onwy the chwominance pixews and
			 pewfowms noise weduction by cweaning the high
			 fwequency noise.
			 See stwuct stwuct ipu3_uapi_yuvp1_chnw_config.
TCC			 Totaw cowow cowwection as defined in stwuct
			 stwuct ipu3_uapi_yuvp2_tcc_static_config.
XNW3			 eXtweme Noise Weduction V3 is the thiwd wevision of
			 noise weduction awgowithm used to impwove image
			 quawity. This wemoves the wow fwequency noise in the
			 captuwed image. Two wewated stwucts awe  being defined,
			 stwuct ipu3_uapi_isp_xnw3_pawams fow ISP data memowy
			 and stwuct ipu3_uapi_isp_xnw3_vmem_pawams fow vectow
			 memowy.
TNW			 Tempowaw Noise Weduction bwock compawes successive
			 fwames in time to wemove anomawies / noise in pixew
			 vawues. stwuct ipu3_uapi_isp_tnw3_vmem_pawams and
			 stwuct ipu3_uapi_isp_tnw3_pawams awe defined fow ISP
			 vectow and data memowy wespectivewy.
======================== =======================================================

Othew often encountewed acwonyms not wisted in above tabwe:

	ACC
		Accewewatow cwustew
	AWB_FW
		Auto white bawance fiwtew wesponse statistics
	BDS
		Bayew downscawew pawametews
	CCM
		Cowow cowwection matwix coefficients
	IEFd
		Image enhancement fiwtew diwected
	Obgwid
		Opticaw bwack wevew compensation
	OSYS
		Output system configuwation
	WOI
		Wegion of intewest
	YDS
		Y down sampwing
	YTM
		Y-tone mapping

A few stages of the pipewine wiww be executed by fiwmwawe wunning on the ISP
pwocessow, whiwe many othews wiww use a set of fixed hawdwawe bwocks awso
cawwed accewewatow cwustew (ACC) to cwunch pixew data and pwoduce statistics.

ACC pawametews of individuaw awgowithms, as defined by
stwuct ipu3_uapi_acc_pawam, can be chosen to be appwied by the usew
space thwough stwuct stwuct ipu3_uapi_fwags embedded in
stwuct ipu3_uapi_pawams stwuctuwe. Fow pawametews that awe configuwed as
not enabwed by the usew space, the cowwesponding stwucts awe ignowed by the
dwivew, in which case the existing configuwation of the awgowithm wiww be
pwesewved.

Wefewences
==========

.. [#f5] dwivews/staging/media/ipu3/incwude/uapi/intew-ipu3.h

.. [#f1] https://github.com/intew/nvt

.. [#f2] http://git.ideasonboawd.owg/yavta.git

.. [#f3] http://git.ideasonboawd.owg/?p=media-ctw.git;a=summawy

.. [#f4] ImgU wimitation wequiwes an additionaw 16x16 fow aww input wesowutions
