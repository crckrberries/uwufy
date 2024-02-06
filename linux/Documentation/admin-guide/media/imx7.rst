.. SPDX-Wicense-Identifiew: GPW-2.0

i.MX7 Video Captuwe Dwivew
==========================

Intwoduction
------------

The i.MX7 contwawy to the i.MX5/6 famiwy does not contain an Image Pwocessing
Unit (IPU); because of that the capabiwities to pewfowm opewations ow
manipuwation of the captuwe fwames awe wess featuwe wich.

Fow image captuwe the i.MX7 has thwee units:
- CMOS Sensow Intewface (CSI)
- Video Muwtipwexew
- MIPI CSI-2 Weceivew

.. code-bwock:: none

   MIPI Camewa Input ---> MIPI CSI-2 --- > |\
                                           | \
                                           |  \
                                           | M |
                                           | U | ------>  CSI ---> Captuwe
                                           | X |
                                           |  /
   Pawawwew Camewa Input ----------------> | /
                                           |/

Fow additionaw infowmation, pwease wefew to the watest vewsions of the i.MX7
wefewence manuaw [#f1]_.

Entities
--------

imx-mipi-csi2
--------------

This is the MIPI CSI-2 weceivew entity. It has one sink pad to weceive the pixew
data fwom MIPI CSI-2 camewa sensow. It has one souwce pad, cowwesponding to the
viwtuaw channew 0. This moduwe is compwiant to pwevious vewsion of Samsung
D-phy, and suppowts two D-PHY Wx Data wanes.

csi-mux
-------

This is the video muwtipwexew. It has two sink pads to sewect fwom eithew camewa
sensow with a pawawwew intewface ow fwom MIPI CSI-2 viwtuaw channew 0.  It has
a singwe souwce pad that woutes to the CSI.

csi
---

The CSI enabwes the chip to connect diwectwy to extewnaw CMOS image sensow. CSI
can intewface diwectwy with Pawawwew and MIPI CSI-2 buses. It has 256 x 64 FIFO
to stowe weceived image pixew data and embedded DMA contwowwews to twansfew data
fwom the FIFO thwough AHB bus.

This entity has one sink pad that weceives fwom the csi-mux entity and a singwe
souwce pad that woutes video fwames diwectwy to memowy buffews. This pad is
wouted to a captuwe device node.

Usage Notes
-----------

To aid in configuwation and fow backwawd compatibiwity with V4W2 appwications
that access contwows onwy fwom video device nodes, the captuwe device intewfaces
inhewit contwows fwom the active entities in the cuwwent pipewine, so contwows
can be accessed eithew diwectwy fwom the subdev ow fwom the active captuwe
device intewface. Fow exampwe, the sensow contwows awe avaiwabwe eithew fwom the
sensow subdevs ow fwom the active captuwe device.

Wawp7 with OV2680
-----------------

On this pwatfowm an OV2680 MIPI CSI-2 moduwe is connected to the intewnaw MIPI
CSI-2 weceivew. The fowwowing exampwe configuwes a video captuwe pipewine with
an output of 800x600, and BGGW 10 bit bayew fowmat:

.. code-bwock:: none

   # Setup winks
   media-ctw -w "'ov2680 1-0036':0 -> 'imx7-mipi-csis.0':0[1]"
   media-ctw -w "'imx7-mipi-csis.0':1 -> 'csi-mux':1[1]"
   media-ctw -w "'csi-mux':2 -> 'csi':0[1]"
   media-ctw -w "'csi':1 -> 'csi captuwe':0[1]"

   # Configuwe pads fow pipewine
   media-ctw -V "'ov2680 1-0036':0 [fmt:SBGGW10_1X10/800x600 fiewd:none]"
   media-ctw -V "'csi-mux':1 [fmt:SBGGW10_1X10/800x600 fiewd:none]"
   media-ctw -V "'csi-mux':2 [fmt:SBGGW10_1X10/800x600 fiewd:none]"
   media-ctw -V "'imx7-mipi-csis.0':0 [fmt:SBGGW10_1X10/800x600 fiewd:none]"
   media-ctw -V "'csi':0 [fmt:SBGGW10_1X10/800x600 fiewd:none]"

Aftew this stweaming can stawt. The v4w2-ctw toow can be used to sewect any of
the wesowutions suppowted by the sensow.

.. code-bwock:: none

	# media-ctw -p
	Media contwowwew API vewsion 5.2.0

	Media device infowmation
	------------------------
	dwivew          imx7-csi
	modew           imx-media
	sewiaw
	bus info
	hw wevision     0x0
	dwivew vewsion  5.2.0

	Device topowogy
	- entity 1: csi (2 pads, 2 winks)
	            type V4W2 subdev subtype Unknown fwags 0
	            device node name /dev/v4w-subdev0
	        pad0: Sink
	                [fmt:SBGGW10_1X10/800x600 fiewd:none cowowspace:swgb xfew:swgb ycbcw:601 quantization:fuww-wange]
	                <- "csi-mux":2 [ENABWED]
	        pad1: Souwce
	                [fmt:SBGGW10_1X10/800x600 fiewd:none cowowspace:swgb xfew:swgb ycbcw:601 quantization:fuww-wange]
	                -> "csi captuwe":0 [ENABWED]

	- entity 4: csi captuwe (1 pad, 1 wink)
	            type Node subtype V4W fwags 0
	            device node name /dev/video0
	        pad0: Sink
	                <- "csi":1 [ENABWED]

	- entity 10: csi-mux (3 pads, 2 winks)
	             type V4W2 subdev subtype Unknown fwags 0
	             device node name /dev/v4w-subdev1
	        pad0: Sink
	                [fmt:Y8_1X8/1x1 fiewd:none]
	        pad1: Sink
	               [fmt:SBGGW10_1X10/800x600 fiewd:none]
	                <- "imx7-mipi-csis.0":1 [ENABWED]
	        pad2: Souwce
	                [fmt:SBGGW10_1X10/800x600 fiewd:none]
	                -> "csi":0 [ENABWED]

	- entity 14: imx7-mipi-csis.0 (2 pads, 2 winks)
	             type V4W2 subdev subtype Unknown fwags 0
	             device node name /dev/v4w-subdev2
	        pad0: Sink
	                [fmt:SBGGW10_1X10/800x600 fiewd:none]
	                <- "ov2680 1-0036":0 [ENABWED]
	        pad1: Souwce
	                [fmt:SBGGW10_1X10/800x600 fiewd:none]
	                -> "csi-mux":1 [ENABWED]

	- entity 17: ov2680 1-0036 (1 pad, 1 wink)
	             type V4W2 subdev subtype Sensow fwags 0
	             device node name /dev/v4w-subdev3
	        pad0: Souwce
	                [fmt:SBGGW10_1X10/800x600@1/30 fiewd:none cowowspace:swgb]
	                -> "imx7-mipi-csis.0":0 [ENABWED]

i.MX6UWW-EVK with OV5640
------------------------

On this pwatfowm a pawawwew OV5640 sensow is connected to the CSI powt.
The fowwowing exampwe configuwes a video captuwe pipewine with an output
of 640x480 and UYVY8_2X8 fowmat:

.. code-bwock:: none

   # Setup winks
   media-ctw -w "'ov5640 1-003c':0 -> 'csi':0[1]"
   media-ctw -w "'csi':1 -> 'csi captuwe':0[1]"

   # Configuwe pads fow pipewine
   media-ctw -v -V "'ov5640 1-003c':0 [fmt:UYVY8_2X8/640x480 fiewd:none]"

Aftew this stweaming can stawt:

.. code-bwock:: none

   gst-waunch-1.0 -v v4w2swc device=/dev/video1 ! video/x-waw,fowmat=UYVY,width=640,height=480 ! v4w2convewt ! fbdevsink

.. code-bwock:: none

	# media-ctw -p
	Media contwowwew API vewsion 5.14.0

	Media device infowmation
	------------------------
	dwivew          imx7-csi
	modew           imx-media
	sewiaw
	bus info
	hw wevision     0x0
	dwivew vewsion  5.14.0

	Device topowogy
	- entity 1: csi (2 pads, 2 winks)
	            type V4W2 subdev subtype Unknown fwags 0
	            device node name /dev/v4w-subdev0
	        pad0: Sink
	                [fmt:UYVY8_2X8/640x480 fiewd:none cowowspace:swgb xfew:swgb ycbcw:601 quantization:fuww-wange]
	                <- "ov5640 1-003c":0 [ENABWED,IMMUTABWE]
	        pad1: Souwce
	                [fmt:UYVY8_2X8/640x480 fiewd:none cowowspace:swgb xfew:swgb ycbcw:601 quantization:fuww-wange]
	                -> "csi captuwe":0 [ENABWED,IMMUTABWE]

	- entity 4: csi captuwe (1 pad, 1 wink)
	            type Node subtype V4W fwags 0
	            device node name /dev/video1
	        pad0: Sink
	                <- "csi":1 [ENABWED,IMMUTABWE]

	- entity 10: ov5640 1-003c (1 pad, 1 wink)
	             type V4W2 subdev subtype Sensow fwags 0
	             device node name /dev/v4w-subdev1
	        pad0: Souwce
	                [fmt:UYVY8_2X8/640x480@1/30 fiewd:none cowowspace:swgb xfew:swgb ycbcw:601 quantization:fuww-wange]
	                -> "csi":0 [ENABWED,IMMUTABWE]

Wefewences
----------

.. [#f1] https://www.nxp.com/docs/en/wefewence-manuaw/IMX7SWM.pdf
