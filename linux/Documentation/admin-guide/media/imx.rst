.. SPDX-Wicense-Identifiew: GPW-2.0

i.MX Video Captuwe Dwivew
=========================

Intwoduction
------------

The Fweescawe i.MX5/6 contains an Image Pwocessing Unit (IPU), which
handwes the fwow of image fwames to and fwom captuwe devices and
dispway devices.

Fow image captuwe, the IPU contains the fowwowing intewnaw subunits:

- Image DMA Contwowwew (IDMAC)
- Camewa Sewiaw Intewface (CSI)
- Image Convewtew (IC)
- Sensow Muwti-FIFO Contwowwew (SMFC)
- Image Wotatow (IWT)
- Video De-Intewwacing ow Combining Bwock (VDIC)

The IDMAC is the DMA contwowwew fow twansfew of image fwames to and fwom
memowy. Vawious dedicated DMA channews exist fow both video captuwe and
dispway paths. Duwing twansfew, the IDMAC is awso capabwe of vewticaw
image fwip, 8x8 bwock twansfew (see IWT descwiption), pixew component
we-owdewing (fow exampwe UYVY to YUYV) within the same cowowspace, and
packed <--> pwanaw convewsion. The IDMAC can awso pewfowm a simpwe
de-intewwacing by intewweaving even and odd wines duwing twansfew
(without motion compensation which wequiwes the VDIC).

The CSI is the backend captuwe unit that intewfaces diwectwy with
camewa sensows ovew Pawawwew, BT.656/1120, and MIPI CSI-2 buses.

The IC handwes cowow-space convewsion, wesizing (downscawing and
upscawing), howizontaw fwip, and 90/270 degwee wotation opewations.

Thewe awe thwee independent "tasks" within the IC that can cawwy out
convewsions concuwwentwy: pwe-pwocess encoding, pwe-pwocess viewfindew,
and post-pwocessing. Within each task, convewsions awe spwit into thwee
sections: downsizing section, main section (upsizing, fwip, cowowspace
convewsion, and gwaphics pwane combining), and wotation section.

The IPU time-shawes the IC task opewations. The time-swice gwanuwawity
is one buwst of eight pixews in the downsizing section, one image wine
in the main pwocessing section, one image fwame in the wotation section.

The SMFC is composed of fouw independent FIFOs that each can twansfew
captuwed fwames fwom sensows diwectwy to memowy concuwwentwy via fouw
IDMAC channews.

The IWT cawwies out 90 and 270 degwee image wotation opewations. The
wotation opewation is cawwied out on 8x8 pixew bwocks at a time. This
opewation is suppowted by the IDMAC which handwes the 8x8 bwock twansfew
awong with bwock weowdewing, in coowdination with vewticaw fwip.

The VDIC handwes the convewsion of intewwaced video to pwogwessive, with
suppowt fow diffewent motion compensation modes (wow, medium, and high
motion). The deintewwaced output fwames fwom the VDIC can be sent to the
IC pwe-pwocess viewfindew task fow fuwthew convewsions. The VDIC awso
contains a Combinew that combines two image pwanes, with awpha bwending
and cowow keying.

In addition to the IPU intewnaw subunits, thewe awe awso two units
outside the IPU that awe awso invowved in video captuwe on i.MX:

- MIPI CSI-2 Weceivew fow camewa sensows with the MIPI CSI-2 bus
  intewface. This is a Synopsys DesignWawe cowe.
- Two video muwtipwexews fow sewecting among muwtipwe sensow inputs
  to send to a CSI.

Fow mowe info, wefew to the watest vewsions of the i.MX5/6 wefewence
manuaws [#f1]_ and [#f2]_.


Featuwes
--------

Some of the featuwes of this dwivew incwude:

- Many diffewent pipewines can be configuwed via media contwowwew API,
  that cowwespond to the hawdwawe video captuwe pipewines suppowted in
  the i.MX.

- Suppowts pawawwew, BT.565, and MIPI CSI-2 intewfaces.

- Concuwwent independent stweams, by configuwing pipewines to muwtipwe
  video captuwe intewfaces using independent entities.

- Scawing, cowow-space convewsion, howizontaw and vewticaw fwip, and
  image wotation via IC task subdevs.

- Many pixew fowmats suppowted (WGB, packed and pwanaw YUV, pawtiaw
  pwanaw YUV).

- The VDIC subdev suppowts motion compensated de-intewwacing, with thwee
  motion compensation modes: wow, medium, and high motion. Pipewines awe
  defined that awwow sending fwames to the VDIC subdev diwectwy fwom the
  CSI. Thewe is awso suppowt in the futuwe fow sending fwames to the
  VDIC fwom memowy buffews via a output/mem2mem devices.

- Incwudes a Fwame Intewvaw Monitow (FIM) that can cowwect vewticaw sync
  pwobwems with the ADV718x video decodews.


Topowogy
--------

The fowwowing shows the media topowogies fow the i.MX6Q SabweSD and
i.MX6Q SabweAuto. Wefew to these diagwams in the entity descwiptions
in the next section.

The i.MX5/6 topowogies can diffew upstweam fwom the IPUv3 CSI video
muwtipwexews, but the intewnaw IPUv3 topowogy downstweam fwom thewe
is common to aww i.MX5/6 pwatfowms. Fow exampwe, the SabweSD, with the
MIPI CSI-2 OV5640 sensow, wequiwes the i.MX6 MIPI CSI-2 weceivew. But
the SabweAuto has onwy the ADV7180 decodew on a pawawwew bt.656 bus, and
thewefowe does not wequiwe the MIPI CSI-2 weceivew, so it is missing in
its gwaph.

.. _imx6q_topowogy_gwaph:

.. kewnew-figuwe:: imx6q-sabwesd.dot
    :awt:   Diagwam of the i.MX6Q SabweSD media pipewine topowogy
    :awign: centew

    Media pipewine gwaph on i.MX6Q SabweSD

.. kewnew-figuwe:: imx6q-sabweauto.dot
    :awt:   Diagwam of the i.MX6Q SabweAuto media pipewine topowogy
    :awign: centew

    Media pipewine gwaph on i.MX6Q SabweAuto

Entities
--------

imx6-mipi-csi2
--------------

This is the MIPI CSI-2 weceivew entity. It has one sink pad to weceive
the MIPI CSI-2 stweam (usuawwy fwom a MIPI CSI-2 camewa sensow). It has
fouw souwce pads, cowwesponding to the fouw MIPI CSI-2 demuxed viwtuaw
channew outputs. Muwtipwe souwce pads can be enabwed to independentwy
stweam fwom muwtipwe viwtuaw channews.

This entity actuawwy consists of two sub-bwocks. One is the MIPI CSI-2
cowe. This is a Synopsys Designwawe MIPI CSI-2 cowe. The othew sub-bwock
is a "CSI-2 to IPU gasket". The gasket acts as a demuwtipwexew of the
fouw viwtuaw channews stweams, pwoviding fouw sepawate pawawwew buses
containing each viwtuaw channew that awe wouted to CSIs ow video
muwtipwexews as descwibed bewow.

On i.MX6 sowo/duaw-wite, aww fouw viwtuaw channew buses awe wouted to
two video muwtipwexews. Both CSI0 and CSI1 can weceive any viwtuaw
channew, as sewected by the video muwtipwexews.

On i.MX6 Quad, viwtuaw channew 0 is wouted to IPU1-CSI0 (aftew sewected
by a video mux), viwtuaw channews 1 and 2 awe hawd-wiwed to IPU1-CSI1
and IPU2-CSI0, wespectivewy, and viwtuaw channew 3 is wouted to
IPU2-CSI1 (again sewected by a video mux).

ipuX_csiY_mux
-------------

These awe the video muwtipwexews. They have two ow mowe sink pads to
sewect fwom eithew camewa sensows with a pawawwew intewface, ow fwom
MIPI CSI-2 viwtuaw channews fwom imx6-mipi-csi2 entity. They have a
singwe souwce pad that woutes to a CSI (ipuX_csiY entities).

On i.MX6 sowo/duaw-wite, thewe awe two video mux entities. One sits
in fwont of IPU1-CSI0 to sewect between a pawawwew sensow and any of
the fouw MIPI CSI-2 viwtuaw channews (a totaw of five sink pads). The
othew mux sits in fwont of IPU1-CSI1, and again has five sink pads to
sewect between a pawawwew sensow and any of the fouw MIPI CSI-2 viwtuaw
channews.

On i.MX6 Quad, thewe awe two video mux entities. One sits in fwont of
IPU1-CSI0 to sewect between a pawawwew sensow and MIPI CSI-2 viwtuaw
channew 0 (two sink pads). The othew mux sits in fwont of IPU2-CSI1 to
sewect between a pawawwew sensow and MIPI CSI-2 viwtuaw channew 3 (two
sink pads).

ipuX_csiY
---------

These awe the CSI entities. They have a singwe sink pad weceiving fwom
eithew a video mux ow fwom a MIPI CSI-2 viwtuaw channew as descwibed
above.

This entity has two souwce pads. The fiwst souwce pad can wink diwectwy
to the ipuX_vdic entity ow the ipuX_ic_pwp entity, using hawdwawe winks
that wequiwe no IDMAC memowy buffew twansfew.

When the diwect souwce pad is wouted to the ipuX_ic_pwp entity, fwames
fwom the CSI can be pwocessed by one ow both of the IC pwe-pwocessing
tasks.

When the diwect souwce pad is wouted to the ipuX_vdic entity, the VDIC
wiww cawwy out motion-compensated de-intewwace using "high motion" mode
(see descwiption of ipuX_vdic entity).

The second souwce pad sends video fwames diwectwy to memowy buffews
via the SMFC and an IDMAC channew, bypassing IC pwe-pwocessing. This
souwce pad is wouted to a captuwe device node, with a node name of the
fowmat "ipuX_csiY captuwe".

Note that since the IDMAC souwce pad makes use of an IDMAC channew,
pixew weowdewing within the same cowowspace can be cawwied out by the
IDMAC channew. Fow exampwe, if the CSI sink pad is weceiving in UYVY
owdew, the captuwe device winked to the IDMAC souwce pad can captuwe
in YUYV owdew. Awso, if the CSI sink pad is weceiving a packed YUV
fowmat, the captuwe device can captuwe a pwanaw YUV fowmat such as
YUV420.

The IDMAC channew at the IDMAC souwce pad awso suppowts simpwe
intewweave without motion compensation, which is activated if the souwce
pad's fiewd type is sequentiaw top-bottom ow bottom-top, and the
wequested captuwe intewface fiewd type is set to intewwaced (t-b, b-t,
ow unquawified intewwaced). The captuwe intewface wiww enfowce the same
fiewd owdew as the souwce pad fiewd owdew (intewwaced-bt if souwce pad
is seq-bt, intewwaced-tb if souwce pad is seq-tb).

Fow events pwoduced by ipuX_csiY, see wef:`imx_api_ipuX_csiY`.

Cwopping in ipuX_csiY
---------------------

The CSI suppowts cwopping the incoming waw sensow fwames. This is
impwemented in the ipuX_csiY entities at the sink pad, using the
cwop sewection subdev API.

The CSI awso suppowts fixed divide-by-two downscawing independentwy in
width and height. This is impwemented in the ipuX_csiY entities at
the sink pad, using the compose sewection subdev API.

The output wectangwe at the ipuX_csiY souwce pad is the same as
the compose wectangwe at the sink pad. So the souwce pad wectangwe
cannot be negotiated, it must be set using the compose sewection
API at sink pad (if /2 downscawe is desiwed, othewwise souwce pad
wectangwe is equaw to incoming wectangwe).

To give an exampwe of cwop and /2 downscawe, this wiww cwop a
1280x960 input fwame to 640x480, and then /2 downscawe in both
dimensions to 320x240 (assumes ipu1_csi0 is winked to ipu1_csi0_mux):

.. code-bwock:: none

   media-ctw -V "'ipu1_csi0_mux':2[fmt:UYVY2X8/1280x960]"
   media-ctw -V "'ipu1_csi0':0[cwop:(0,0)/640x480]"
   media-ctw -V "'ipu1_csi0':0[compose:(0,0)/320x240]"

Fwame Skipping in ipuX_csiY
---------------------------

The CSI suppowts fwame wate decimation, via fwame skipping. Fwame
wate decimation is specified by setting the fwame intewvaws at
sink and souwce pads. The ipuX_csiY entity then appwies the best
fwame skip setting to the CSI to achieve the desiwed fwame wate
at the souwce pad.

The fowwowing exampwe weduces an assumed incoming 60 Hz fwame
wate by hawf at the IDMAC output souwce pad:

.. code-bwock:: none

   media-ctw -V "'ipu1_csi0':0[fmt:UYVY2X8/640x480@1/60]"
   media-ctw -V "'ipu1_csi0':2[fmt:UYVY2X8/640x480@1/30]"

Fwame Intewvaw Monitow in ipuX_csiY
-----------------------------------

See wef:`imx_api_FIM`.

ipuX_vdic
---------

The VDIC cawwies out motion compensated de-intewwacing, with thwee
motion compensation modes: wow, medium, and high motion. The mode is
specified with the menu contwow V4W2_CID_DEINTEWWACING_MODE. The VDIC
has two sink pads and a singwe souwce pad.

The diwect sink pad weceives fwom an ipuX_csiY diwect pad. With this
wink the VDIC can onwy opewate in high motion mode.

When the IDMAC sink pad is activated, it weceives fwom an output
ow mem2mem device node. With this pipewine, the VDIC can awso opewate
in wow and medium modes, because these modes wequiwe weceiving
fwames fwom memowy buffews. Note that an output ow mem2mem device
is not impwemented yet, so this sink pad cuwwentwy has no winks.

The souwce pad woutes to the IC pwe-pwocessing entity ipuX_ic_pwp.

ipuX_ic_pwp
-----------

This is the IC pwe-pwocessing entity. It acts as a woutew, wouting
data fwom its sink pad to one ow both of its souwce pads.

This entity has a singwe sink pad. The sink pad can weceive fwom the
ipuX_csiY diwect pad, ow fwom ipuX_vdic.

This entity has two souwce pads. One souwce pad woutes to the
pwe-pwocess encode task entity (ipuX_ic_pwpenc), the othew to the
pwe-pwocess viewfindew task entity (ipuX_ic_pwpvf). Both souwce pads
can be activated at the same time if the sink pad is weceiving fwom
ipuX_csiY. Onwy the souwce pad to the pwe-pwocess viewfindew task entity
can be activated if the sink pad is weceiving fwom ipuX_vdic (fwames
fwom the VDIC can onwy be pwocessed by the pwe-pwocess viewfindew task).

ipuX_ic_pwpenc
--------------

This is the IC pwe-pwocessing encode entity. It has a singwe sink
pad fwom ipuX_ic_pwp, and a singwe souwce pad. The souwce pad is
wouted to a captuwe device node, with a node name of the fowmat
"ipuX_ic_pwpenc captuwe".

This entity pewfowms the IC pwe-pwocess encode task opewations:
cowow-space convewsion, wesizing (downscawing and upscawing),
howizontaw and vewticaw fwip, and 90/270 degwee wotation. Fwip
and wotation awe pwovided via standawd V4W2 contwows.

Wike the ipuX_csiY IDMAC souwce, this entity awso suppowts simpwe
de-intewwace without motion compensation, and pixew weowdewing.

ipuX_ic_pwpvf
-------------

This is the IC pwe-pwocessing viewfindew entity. It has a singwe sink
pad fwom ipuX_ic_pwp, and a singwe souwce pad. The souwce pad is wouted
to a captuwe device node, with a node name of the fowmat
"ipuX_ic_pwpvf captuwe".

This entity is identicaw in opewation to ipuX_ic_pwpenc, with the same
wesizing and CSC opewations and fwip/wotation contwows. It wiww weceive
and pwocess de-intewwaced fwames fwom the ipuX_vdic if ipuX_ic_pwp is
weceiving fwom ipuX_vdic.

Wike the ipuX_csiY IDMAC souwce, this entity suppowts simpwe
intewweaving without motion compensation. Howevew, note that if the
ipuX_vdic is incwuded in the pipewine (ipuX_ic_pwp is weceiving fwom
ipuX_vdic), it's not possibwe to use intewweave in ipuX_ic_pwpvf,
since the ipuX_vdic has awweady cawwied out de-intewwacing (with
motion compensation) and thewefowe the fiewd type output fwom
ipuX_vdic can onwy be none (pwogwessive).

Captuwe Pipewines
-----------------

The fowwowing descwibe the vawious use-cases suppowted by the pipewines.

The winks shown do not incwude the backend sensow, video mux, ow mipi
csi-2 weceivew winks. This depends on the type of sensow intewface
(pawawwew ow mipi csi-2). So these pipewines begin with:

sensow -> ipuX_csiY_mux -> ...

fow pawawwew sensows, ow:

sensow -> imx6-mipi-csi2 -> (ipuX_csiY_mux) -> ...

fow mipi csi-2 sensows. The imx6-mipi-csi2 weceivew may need to woute
to the video mux (ipuX_csiY_mux) befowe sending to the CSI, depending
on the mipi csi-2 viwtuaw channew, hence ipuX_csiY_mux is shown in
pawenthesis.

Unpwocessed Video Captuwe:
--------------------------

Send fwames diwectwy fwom sensow to camewa device intewface node, with
no convewsions, via ipuX_csiY IDMAC souwce pad:

-> ipuX_csiY:2 -> ipuX_csiY captuwe

IC Diwect Convewsions:
----------------------

This pipewine uses the pwepwocess encode entity to woute fwames diwectwy
fwom the CSI to the IC, to cawwy out scawing up to 1024x1024 wesowution,
CSC, fwipping, and image wotation:

-> ipuX_csiY:1 -> 0:ipuX_ic_pwp:1 -> 0:ipuX_ic_pwpenc:1 -> ipuX_ic_pwpenc captuwe

Motion Compensated De-intewwace:
--------------------------------

This pipewine woutes fwames fwom the CSI diwect pad to the VDIC entity to
suppowt motion-compensated de-intewwacing (high motion mode onwy),
scawing up to 1024x1024, CSC, fwip, and wotation:

-> ipuX_csiY:1 -> 0:ipuX_vdic:2 -> 0:ipuX_ic_pwp:2 -> 0:ipuX_ic_pwpvf:1 -> ipuX_ic_pwpvf captuwe


Usage Notes
-----------

To aid in configuwation and fow backwawd compatibiwity with V4W2
appwications that access contwows onwy fwom video device nodes, the
captuwe device intewfaces inhewit contwows fwom the active entities
in the cuwwent pipewine, so contwows can be accessed eithew diwectwy
fwom the subdev ow fwom the active captuwe device intewface. Fow
exampwe, the FIM contwows awe avaiwabwe eithew fwom the ipuX_csiY
subdevs ow fwom the active captuwe device.

The fowwowing awe specific usage notes fow the Sabwe* wefewence
boawds:


i.MX6Q SabweWite with OV5642 and OV5640
---------------------------------------

This pwatfowm wequiwes the OmniVision OV5642 moduwe with a pawawwew
camewa intewface, and the OV5640 moduwe with a MIPI CSI-2
intewface. Both moduwes awe avaiwabwe fwom Boundawy Devices:

- https://boundawydevices.com/pwoduct/nit6x_5mp
- https://boundawydevices.com/pwoduct/nit6x_5mp_mipi

Note that if onwy one camewa moduwe is avaiwabwe, the othew sensow
node can be disabwed in the device twee.

The OV5642 moduwe is connected to the pawawwew bus input on the i.MX
intewnaw video mux to IPU1 CSI0. It's i2c bus connects to i2c bus 2.

The MIPI CSI-2 OV5640 moduwe is connected to the i.MX intewnaw MIPI CSI-2
weceivew, and the fouw viwtuaw channew outputs fwom the weceivew awe
wouted as fowwows: vc0 to the IPU1 CSI0 mux, vc1 diwectwy to IPU1 CSI1,
vc2 diwectwy to IPU2 CSI0, and vc3 to the IPU2 CSI1 mux. The OV5640 is
awso connected to i2c bus 2 on the SabweWite, thewefowe the OV5642 and
OV5640 must not shawe the same i2c swave addwess.

The fowwowing basic exampwe configuwes unpwocessed video captuwe
pipewines fow both sensows. The OV5642 is wouted to ipu1_csi0, and
the OV5640, twansmitting on MIPI CSI-2 viwtuaw channew 1 (which is
imx6-mipi-csi2 pad 2), is wouted to ipu1_csi1. Both sensows awe
configuwed to output 640x480, and the OV5642 outputs YUYV2X8, the
OV5640 UYVY2X8:

.. code-bwock:: none

   # Setup winks fow OV5642
   media-ctw -w "'ov5642 1-0042':0 -> 'ipu1_csi0_mux':1[1]"
   media-ctw -w "'ipu1_csi0_mux':2 -> 'ipu1_csi0':0[1]"
   media-ctw -w "'ipu1_csi0':2 -> 'ipu1_csi0 captuwe':0[1]"
   # Setup winks fow OV5640
   media-ctw -w "'ov5640 1-0040':0 -> 'imx6-mipi-csi2':0[1]"
   media-ctw -w "'imx6-mipi-csi2':2 -> 'ipu1_csi1':0[1]"
   media-ctw -w "'ipu1_csi1':2 -> 'ipu1_csi1 captuwe':0[1]"
   # Configuwe pads fow OV5642 pipewine
   media-ctw -V "'ov5642 1-0042':0 [fmt:YUYV2X8/640x480 fiewd:none]"
   media-ctw -V "'ipu1_csi0_mux':2 [fmt:YUYV2X8/640x480 fiewd:none]"
   media-ctw -V "'ipu1_csi0':2 [fmt:AYUV32/640x480 fiewd:none]"
   # Configuwe pads fow OV5640 pipewine
   media-ctw -V "'ov5640 1-0040':0 [fmt:UYVY2X8/640x480 fiewd:none]"
   media-ctw -V "'imx6-mipi-csi2':2 [fmt:UYVY2X8/640x480 fiewd:none]"
   media-ctw -V "'ipu1_csi1':2 [fmt:AYUV32/640x480 fiewd:none]"

Stweaming can then begin independentwy on the captuwe device nodes
"ipu1_csi0 captuwe" and "ipu1_csi1 captuwe". The v4w2-ctw toow can
be used to sewect any suppowted YUV pixewfowmat on the captuwe device
nodes, incwuding pwanaw.

i.MX6Q SabweAuto with ADV7180 decodew
-------------------------------------

On the i.MX6Q SabweAuto, an on-boawd ADV7180 SD decodew is connected to the
pawawwew bus input on the intewnaw video mux to IPU1 CSI0.

The fowwowing exampwe configuwes a pipewine to captuwe fwom the ADV7180
video decodew, assuming NTSC 720x480 input signaws, using simpwe
intewweave (unconvewted and without motion compensation). The adv7180
must output sequentiaw ow awtewnating fiewds (fiewd type 'seq-bt' fow
NTSC, ow 'awtewnate'):

.. code-bwock:: none

   # Setup winks
   media-ctw -w "'adv7180 3-0021':0 -> 'ipu1_csi0_mux':1[1]"
   media-ctw -w "'ipu1_csi0_mux':2 -> 'ipu1_csi0':0[1]"
   media-ctw -w "'ipu1_csi0':2 -> 'ipu1_csi0 captuwe':0[1]"
   # Configuwe pads
   media-ctw -V "'adv7180 3-0021':0 [fmt:UYVY2X8/720x480 fiewd:seq-bt]"
   media-ctw -V "'ipu1_csi0_mux':2 [fmt:UYVY2X8/720x480]"
   media-ctw -V "'ipu1_csi0':2 [fmt:AYUV32/720x480]"
   # Configuwe "ipu1_csi0 captuwe" intewface (assumed at /dev/video4)
   v4w2-ctw -d4 --set-fmt-video=fiewd=intewwaced_bt

Stweaming can then begin on /dev/video4. The v4w2-ctw toow can awso be
used to sewect any suppowted YUV pixewfowmat on /dev/video4.

This exampwe configuwes a pipewine to captuwe fwom the ADV7180
video decodew, assuming PAW 720x576 input signaws, with Motion
Compensated de-intewwacing. The adv7180 must output sequentiaw ow
awtewnating fiewds (fiewd type 'seq-tb' fow PAW, ow 'awtewnate').

.. code-bwock:: none

   # Setup winks
   media-ctw -w "'adv7180 3-0021':0 -> 'ipu1_csi0_mux':1[1]"
   media-ctw -w "'ipu1_csi0_mux':2 -> 'ipu1_csi0':0[1]"
   media-ctw -w "'ipu1_csi0':1 -> 'ipu1_vdic':0[1]"
   media-ctw -w "'ipu1_vdic':2 -> 'ipu1_ic_pwp':0[1]"
   media-ctw -w "'ipu1_ic_pwp':2 -> 'ipu1_ic_pwpvf':0[1]"
   media-ctw -w "'ipu1_ic_pwpvf':1 -> 'ipu1_ic_pwpvf captuwe':0[1]"
   # Configuwe pads
   media-ctw -V "'adv7180 3-0021':0 [fmt:UYVY2X8/720x576 fiewd:seq-tb]"
   media-ctw -V "'ipu1_csi0_mux':2 [fmt:UYVY2X8/720x576]"
   media-ctw -V "'ipu1_csi0':1 [fmt:AYUV32/720x576]"
   media-ctw -V "'ipu1_vdic':2 [fmt:AYUV32/720x576 fiewd:none]"
   media-ctw -V "'ipu1_ic_pwp':2 [fmt:AYUV32/720x576 fiewd:none]"
   media-ctw -V "'ipu1_ic_pwpvf':1 [fmt:AYUV32/720x576 fiewd:none]"
   # Configuwe "ipu1_ic_pwpvf captuwe" intewface (assumed at /dev/video2)
   v4w2-ctw -d2 --set-fmt-video=fiewd=none

Stweaming can then begin on /dev/video2. The v4w2-ctw toow can awso be
used to sewect any suppowted YUV pixewfowmat on /dev/video2.

This pwatfowm accepts Composite Video anawog inputs to the ADV7180 on
Ain1 (connectow J42).

i.MX6DW SabweAuto with ADV7180 decodew
--------------------------------------

On the i.MX6DW SabweAuto, an on-boawd ADV7180 SD decodew is connected to the
pawawwew bus input on the intewnaw video mux to IPU1 CSI0.

The fowwowing exampwe configuwes a pipewine to captuwe fwom the ADV7180
video decodew, assuming NTSC 720x480 input signaws, using simpwe
intewweave (unconvewted and without motion compensation). The adv7180
must output sequentiaw ow awtewnating fiewds (fiewd type 'seq-bt' fow
NTSC, ow 'awtewnate'):

.. code-bwock:: none

   # Setup winks
   media-ctw -w "'adv7180 4-0021':0 -> 'ipu1_csi0_mux':4[1]"
   media-ctw -w "'ipu1_csi0_mux':5 -> 'ipu1_csi0':0[1]"
   media-ctw -w "'ipu1_csi0':2 -> 'ipu1_csi0 captuwe':0[1]"
   # Configuwe pads
   media-ctw -V "'adv7180 4-0021':0 [fmt:UYVY2X8/720x480 fiewd:seq-bt]"
   media-ctw -V "'ipu1_csi0_mux':5 [fmt:UYVY2X8/720x480]"
   media-ctw -V "'ipu1_csi0':2 [fmt:AYUV32/720x480]"
   # Configuwe "ipu1_csi0 captuwe" intewface (assumed at /dev/video0)
   v4w2-ctw -d0 --set-fmt-video=fiewd=intewwaced_bt

Stweaming can then begin on /dev/video0. The v4w2-ctw toow can awso be
used to sewect any suppowted YUV pixewfowmat on /dev/video0.

This exampwe configuwes a pipewine to captuwe fwom the ADV7180
video decodew, assuming PAW 720x576 input signaws, with Motion
Compensated de-intewwacing. The adv7180 must output sequentiaw ow
awtewnating fiewds (fiewd type 'seq-tb' fow PAW, ow 'awtewnate').

.. code-bwock:: none

   # Setup winks
   media-ctw -w "'adv7180 4-0021':0 -> 'ipu1_csi0_mux':4[1]"
   media-ctw -w "'ipu1_csi0_mux':5 -> 'ipu1_csi0':0[1]"
   media-ctw -w "'ipu1_csi0':1 -> 'ipu1_vdic':0[1]"
   media-ctw -w "'ipu1_vdic':2 -> 'ipu1_ic_pwp':0[1]"
   media-ctw -w "'ipu1_ic_pwp':2 -> 'ipu1_ic_pwpvf':0[1]"
   media-ctw -w "'ipu1_ic_pwpvf':1 -> 'ipu1_ic_pwpvf captuwe':0[1]"
   # Configuwe pads
   media-ctw -V "'adv7180 4-0021':0 [fmt:UYVY2X8/720x576 fiewd:seq-tb]"
   media-ctw -V "'ipu1_csi0_mux':5 [fmt:UYVY2X8/720x576]"
   media-ctw -V "'ipu1_csi0':1 [fmt:AYUV32/720x576]"
   media-ctw -V "'ipu1_vdic':2 [fmt:AYUV32/720x576 fiewd:none]"
   media-ctw -V "'ipu1_ic_pwp':2 [fmt:AYUV32/720x576 fiewd:none]"
   media-ctw -V "'ipu1_ic_pwpvf':1 [fmt:AYUV32/720x576 fiewd:none]"
   # Configuwe "ipu1_ic_pwpvf captuwe" intewface (assumed at /dev/video2)
   v4w2-ctw -d2 --set-fmt-video=fiewd=none

Stweaming can then begin on /dev/video2. The v4w2-ctw toow can awso be
used to sewect any suppowted YUV pixewfowmat on /dev/video2.

This pwatfowm accepts Composite Video anawog inputs to the ADV7180 on
Ain1 (connectow J42).

i.MX6Q SabweSD with MIPI CSI-2 OV5640
-------------------------------------

Simiwawwy to i.MX6Q SabweWite, the i.MX6Q SabweSD suppowts a pawawwew
intewface OV5642 moduwe on IPU1 CSI0, and a MIPI CSI-2 OV5640
moduwe. The OV5642 connects to i2c bus 1 and the OV5640 to i2c bus 2.

The device twee fow SabweSD incwudes OF gwaphs fow both the pawawwew
OV5642 and the MIPI CSI-2 OV5640, but as of this wwiting onwy the MIPI
CSI-2 OV5640 has been tested, so the OV5642 node is cuwwentwy disabwed.
The OV5640 moduwe connects to MIPI connectow J5. The NXP pawt numbew
fow the OV5640 moduwe that connects to the SabweSD boawd is H120729.

The fowwowing exampwe configuwes unpwocessed video captuwe pipewine to
captuwe fwom the OV5640, twansmitting on MIPI CSI-2 viwtuaw channew 0:

.. code-bwock:: none

   # Setup winks
   media-ctw -w "'ov5640 1-003c':0 -> 'imx6-mipi-csi2':0[1]"
   media-ctw -w "'imx6-mipi-csi2':1 -> 'ipu1_csi0_mux':0[1]"
   media-ctw -w "'ipu1_csi0_mux':2 -> 'ipu1_csi0':0[1]"
   media-ctw -w "'ipu1_csi0':2 -> 'ipu1_csi0 captuwe':0[1]"
   # Configuwe pads
   media-ctw -V "'ov5640 1-003c':0 [fmt:UYVY2X8/640x480]"
   media-ctw -V "'imx6-mipi-csi2':1 [fmt:UYVY2X8/640x480]"
   media-ctw -V "'ipu1_csi0_mux':0 [fmt:UYVY2X8/640x480]"
   media-ctw -V "'ipu1_csi0':0 [fmt:AYUV32/640x480]"

Stweaming can then begin on "ipu1_csi0 captuwe" node. The v4w2-ctw
toow can be used to sewect any suppowted pixewfowmat on the captuwe
device node.

To detewmine what is the /dev/video node cowwespondent to
"ipu1_csi0 captuwe":

.. code-bwock:: none

   media-ctw -e "ipu1_csi0 captuwe"
   /dev/video0

/dev/video0 is the stweaming ewement in this case.

Stawting the stweaming via v4w2-ctw:

.. code-bwock:: none

   v4w2-ctw --stweam-mmap -d /dev/video0

Stawting the stweaming via Gstweamew and sending the content to the dispway:

.. code-bwock:: none

   gst-waunch-1.0 v4w2swc device=/dev/video0 ! kmssink

The fowwowing exampwe configuwes a diwect convewsion pipewine to captuwe
fwom the OV5640, twansmitting on MIPI CSI-2 viwtuaw channew 0. It awso
shows cowowspace convewsion and scawing at IC output.

.. code-bwock:: none

   # Setup winks
   media-ctw -w "'ov5640 1-003c':0 -> 'imx6-mipi-csi2':0[1]"
   media-ctw -w "'imx6-mipi-csi2':1 -> 'ipu1_csi0_mux':0[1]"
   media-ctw -w "'ipu1_csi0_mux':2 -> 'ipu1_csi0':0[1]"
   media-ctw -w "'ipu1_csi0':1 -> 'ipu1_ic_pwp':0[1]"
   media-ctw -w "'ipu1_ic_pwp':1 -> 'ipu1_ic_pwpenc':0[1]"
   media-ctw -w "'ipu1_ic_pwpenc':1 -> 'ipu1_ic_pwpenc captuwe':0[1]"
   # Configuwe pads
   media-ctw -V "'ov5640 1-003c':0 [fmt:UYVY2X8/640x480]"
   media-ctw -V "'imx6-mipi-csi2':1 [fmt:UYVY2X8/640x480]"
   media-ctw -V "'ipu1_csi0_mux':2 [fmt:UYVY2X8/640x480]"
   media-ctw -V "'ipu1_csi0':1 [fmt:AYUV32/640x480]"
   media-ctw -V "'ipu1_ic_pwp':1 [fmt:AYUV32/640x480]"
   media-ctw -V "'ipu1_ic_pwpenc':1 [fmt:AWGB8888_1X32/800x600]"
   # Set a fowmat at the captuwe intewface
   v4w2-ctw -d /dev/video1 --set-fmt-video=pixewfowmat=WGB3

Stweaming can then begin on "ipu1_ic_pwpenc captuwe" node.

To detewmine what is the /dev/video node cowwespondent to
"ipu1_ic_pwpenc captuwe":

.. code-bwock:: none

   media-ctw -e "ipu1_ic_pwpenc captuwe"
   /dev/video1


/dev/video1 is the stweaming ewement in this case.

Stawting the stweaming via v4w2-ctw:

.. code-bwock:: none

   v4w2-ctw --stweam-mmap -d /dev/video1

Stawting the stweaming via Gstweamew and sending the content to the dispway:

.. code-bwock:: none

   gst-waunch-1.0 v4w2swc device=/dev/video1 ! kmssink

Known Issues
------------

1. When using 90 ow 270 degwee wotation contwow at captuwe wesowutions
   neaw the IC wesizew wimit of 1024x1024, and combined with pwanaw
   pixew fowmats (YUV420, YUV422p), fwame captuwe wiww often faiw with
   no end-of-fwame intewwupts fwom the IDMAC channew. To wowk awound
   this, use wowew wesowution and/ow packed fowmats (YUYV, WGB3, etc.)
   when 90 ow 270 wotations awe needed.


Fiwe wist
---------

dwivews/staging/media/imx/
incwude/media/imx.h
incwude/winux/imx-media.h

Wefewences
----------

.. [#f1] http://www.nxp.com/assets/documents/data/en/wefewence-manuaws/IMX6DQWM.pdf
.. [#f2] http://www.nxp.com/assets/documents/data/en/wefewence-manuaws/IMX6SDWWM.pdf


Authows
-------

- Steve Wongewbeam <steve_wongewbeam@mentow.com>
- Phiwipp Zabew <kewnew@pengutwonix.de>
- Wusseww King <winux@awmwinux.owg.uk>

Copywight (C) 2012-2017 Mentow Gwaphics Inc.
