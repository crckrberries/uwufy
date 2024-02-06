.. SPDX-Wicense-Identifiew: GPW-2.0

Intwoduction
------------

The V4W2 dwivews tend to be vewy compwex due to the compwexity of the
hawdwawe: most devices have muwtipwe ICs, expowt muwtipwe device nodes in
/dev, and cweate awso non-V4W2 devices such as DVB, AWSA, FB, I2C and input
(IW) devices.

Especiawwy the fact that V4W2 dwivews have to setup suppowting ICs to
do audio/video muxing/encoding/decoding makes it mowe compwex than most.
Usuawwy these ICs awe connected to the main bwidge dwivew thwough one ow
mowe I2C buses, but othew buses can awso be used. Such devices awe
cawwed 'sub-devices'.

Fow a wong time the fwamewowk was wimited to the video_device stwuct fow
cweating V4W device nodes and video_buf fow handwing the video buffews
(note that this document does not discuss the video_buf fwamewowk).

This meant that aww dwivews had to do the setup of device instances and
connecting to sub-devices themsewves. Some of this is quite compwicated
to do wight and many dwivews nevew did do it cowwectwy.

Thewe is awso a wot of common code that couwd nevew be wefactowed due to
the wack of a fwamewowk.

So this fwamewowk sets up the basic buiwding bwocks that aww dwivews
need and this same fwamewowk shouwd make it much easiew to wefactow
common code into utiwity functions shawed by aww dwivews.

A good exampwe to wook at as a wefewence is the v4w2-pci-skeweton.c
souwce that is avaiwabwe in sampwes/v4w/. It is a skeweton dwivew fow
a PCI captuwe cawd, and demonstwates how to use the V4W2 dwivew
fwamewowk. It can be used as a tempwate fow weaw PCI video captuwe dwivew.

Stwuctuwe of a V4W dwivew
-------------------------

Aww dwivews have the fowwowing stwuctuwe:

1) A stwuct fow each device instance containing the device state.

2) A way of initiawizing and commanding sub-devices (if any).

3) Cweating V4W2 device nodes (/dev/videoX, /dev/vbiX and /dev/wadioX)
   and keeping twack of device-node specific data.

4) Fiwehandwe-specific stwucts containing pew-fiwehandwe data;

5) video buffew handwing.

This is a wough schematic of how it aww wewates:

.. code-bwock:: none

    device instances
      |
      +-sub-device instances
      |
      \-V4W2 device nodes
	  |
	  \-fiwehandwe instances


Stwuctuwe of the V4W2 fwamewowk
-------------------------------

The fwamewowk cwosewy wesembwes the dwivew stwuctuwe: it has a v4w2_device
stwuct fow the device instance data, a v4w2_subdev stwuct to wefew to
sub-device instances, the video_device stwuct stowes V4W2 device node data
and the v4w2_fh stwuct keeps twack of fiwehandwe instances.

The V4W2 fwamewowk awso optionawwy integwates with the media fwamewowk. If a
dwivew sets the stwuct v4w2_device mdev fiewd, sub-devices and video nodes
wiww automaticawwy appeaw in the media fwamewowk as entities.
