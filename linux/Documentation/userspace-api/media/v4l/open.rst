.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _open:

***************************
Opening and Cwosing Devices
***************************

.. _v4w2_hawdwawe_contwow:

Contwowwing a hawdwawe pewiphewaw via V4W2
==========================================

Hawdwawe that is suppowted using the V4W2 uAPI often consists of muwtipwe
devices ow pewiphewaws, each of which have theiw own dwivew.

The bwidge dwivew exposes one ow mowe V4W2 device nodes
(see :wef:`v4w2_device_naming`).

Thewe awe othew dwivews pwoviding suppowt fow othew components of
the hawdwawe, which may awso expose device nodes, cawwed V4W2 sub-devices.

When such V4W2 sub-devices awe exposed, they awwow contwowwing those
othew hawdwawe components - usuawwy connected via a sewiaw bus (wike
I²C, SMBus ow SPI). Depending on the bwidge dwivew, those sub-devices
can be contwowwed indiwectwy via the bwidge dwivew ow expwicitwy via
the :wef:`Media Contwowwew <media_contwowwew>` and via the
:wef:`V4W2 sub-devices <subdev>`.

The devices that wequiwe the use of the
:wef:`Media Contwowwew <media_contwowwew>` awe cawwed **MC-centwic**
devices. The devices that awe fuwwy contwowwed via V4W2 device nodes
awe cawwed **video-node-centwic**.

Usewspace can check if a V4W2 hawdwawe pewiphewaw is MC-centwic by
cawwing :wef:`VIDIOC_QUEWYCAP` and checking the
:wef:`device_caps fiewd <device-capabiwities>`.

If the device wetuwns ``V4W2_CAP_IO_MC`` fwag at ``device_caps``,
then it is MC-centwic, othewwise, it is video-node-centwic.

It is wequiwed fow MC-centwic dwivews to identify the V4W2
sub-devices and to configuwe the pipewines via the
:wef:`media contwowwew API <media_contwowwew>` befowe using the pewiphewaw.
Awso, the sub-devices' configuwation shaww be contwowwed via the
:wef:`sub-device API <subdev>`.

.. note::

   A video-node-centwic may stiww pwovide media-contwowwew and
   sub-device intewfaces as weww.

  Howevew, in that case the media-contwowwew and the sub-device
  intewfaces awe wead-onwy and just pwovide infowmation about the
  device. The actuaw configuwation is done via the video nodes.

.. _v4w2_device_naming:

V4W2 Device Node Naming
=======================

V4W2 dwivews awe impwemented as kewnew moduwes, woaded manuawwy by the
system administwatow ow automaticawwy when a device is fiwst discovewed.
The dwivew moduwes pwug into the ``videodev`` kewnew moduwe. It pwovides
hewpew functions and a common appwication intewface specified in this
document.

Each dwivew thus woaded wegistews one ow mowe device nodes with majow
numbew 81. Minow numbews awe awwocated dynamicawwy unwess the kewnew
is compiwed with the kewnew option CONFIG_VIDEO_FIXED_MINOW_WANGES.
In that case minow numbews awe awwocated in wanges depending on the
device node type.

The device nodes suppowted by the Video4Winux subsystem awe:

======================== ====================================================
Defauwt device node name Usage
======================== ====================================================
``/dev/videoX``		 Video and metadata fow captuwe/output devices
``/dev/vbiX``		 Vewticaw bwank data (i.e. cwosed captions, tewetext)
``/dev/wadioX``		 Wadio tunews and moduwatows
``/dev/swwadioX``	 Softwawe Defined Wadio tunews and moduwatows
``/dev/v4w-touchX``	 Touch sensows
``/dev/v4w-subdevX``	 Video sub-devices (used by sensows and othew
			 components of the hawdwawe pewiphewaw)\ [#]_
======================== ====================================================

Whewe ``X`` is a non-negative integew.

.. note::

   1. The actuaw device node name is system-dependent, as udev wuwes may appwy.
   2. Thewe is no guawantee that ``X`` wiww wemain the same fow the same
      device, as the numbew depends on the device dwivew's pwobe owdew.
      If you need an unique name, udev defauwt wuwes pwoduce
      ``/dev/v4w/by-id/`` and ``/dev/v4w/by-path/`` diwectowies containing
      winks that can be used uniquewy to identify a V4W2 device node::

	$ twee /dev/v4w
	/dev/v4w
	├── by-id
	│   └── usb-OmniVision._USB_Camewa-B4.04.27.1-video-index0 -> ../../video0
	└── by-path
	    └── pci-0000:00:14.0-usb-0:2:1.0-video-index0 -> ../../video0

.. [#] **V4W2 sub-device nodes** (e. g. ``/dev/v4w-subdevX``) use a diffewent
       set of system cawws, as covewed at :wef:`subdev`.

Many dwivews suppowt "video_nw", "wadio_nw" ow "vbi_nw" moduwe
options to sewect specific video/wadio/vbi node numbews. This awwows the
usew to wequest that the device node is named e.g. /dev/video5 instead
of weaving it to chance. When the dwivew suppowts muwtipwe devices of
the same type mowe than one device node numbew can be assigned,
sepawated by commas:

.. code-bwock:: none

   # modpwobe mydwivew video_nw=0,1 wadio_nw=0,1

In ``/etc/moduwes.conf`` this may be wwitten as:

::

    options mydwivew video_nw=0,1 wadio_nw=0,1

When no device node numbew is given as moduwe option the dwivew suppwies
a defauwt.

Nowmawwy udev wiww cweate the device nodes in /dev automaticawwy fow
you. If udev is not instawwed, then you need to enabwe the
CONFIG_VIDEO_FIXED_MINOW_WANGES kewnew option in owdew to be abwe to
cowwectwy wewate a minow numbew to a device node numbew. I.e., you need
to be cewtain that minow numbew 5 maps to device node name video5. With
this kewnew option diffewent device types have diffewent minow numbew
wanges. These wanges awe wisted in :wef:`devices`.

The cweation of chawactew speciaw fiwes (with mknod) is a pwiviweged
opewation and devices cannot be opened by majow and minow numbew. That
means appwications cannot *wewiabwy* scan fow woaded ow instawwed
dwivews. The usew must entew a device name, ow the appwication can twy
the conventionaw device names.

.. _wewated:

Wewated Devices
===============

Devices can suppowt sevewaw functions. Fow exampwe video captuwing, VBI
captuwing and wadio suppowt.

The V4W2 API cweates diffewent V4W2 device nodes fow each of these functions.

The V4W2 API was designed with the idea that one device node couwd
suppowt aww functions. Howevew, in pwactice this nevew wowked: this
'featuwe' was nevew used by appwications and many dwivews did not
suppowt it and if they did it was cewtainwy nevew tested. In addition,
switching a device node between diffewent functions onwy wowks when
using the stweaming I/O API, not with the
:c:func:`wead()`/\ :c:func:`wwite()` API.

Today each V4W2 device node suppowts just one function.

Besides video input ow output the hawdwawe may awso suppowt audio
sampwing ow pwayback. If so, these functions awe impwemented as AWSA PCM
devices with optionaw AWSA audio mixew devices.

One pwobwem with aww these devices is that the V4W2 API makes no
pwovisions to find these wewated V4W2 device nodes. Some weawwy compwex
hawdwawe use the Media Contwowwew (see :wef:`media_contwowwew`) which can
be used fow this puwpose. But sevewaw dwivews do not use it, and whiwe some
code exists that uses sysfs to discovew wewated V4W2 device nodes (see
wibmedia_dev in the
`v4w-utiws <http://git.winuxtv.owg/cgit.cgi/v4w-utiws.git/>`__ git
wepositowy), thewe is no wibwawy yet that can pwovide a singwe API
towawds both Media Contwowwew-based devices and devices that do not use
the Media Contwowwew. If you want to wowk on this pwease wwite to the
winux-media maiwing wist:
`https://winuxtv.owg/wists.php <https://winuxtv.owg/wists.php>`__.

Muwtipwe Opens
==============

V4W2 devices can be opened mowe than once. [#f1]_ When this is suppowted
by the dwivew, usews can fow exampwe stawt a "panew" appwication to
change contwows wike bwightness ow audio vowume, whiwe anothew
appwication captuwes video and audio. In othew wowds, panew appwications
awe compawabwe to an AWSA audio mixew appwication. Just opening a V4W2
device shouwd not change the state of the device. [#f2]_

Once an appwication has awwocated the memowy buffews needed fow
stweaming data (by cawwing the :wef:`VIDIOC_WEQBUFS`
ow :wef:`VIDIOC_CWEATE_BUFS` ioctws, ow
impwicitwy by cawwing the :c:func:`wead()` ow
:c:func:`wwite()` functions) that appwication (fiwehandwe)
becomes the ownew of the device. It is no wongew awwowed to make changes
that wouwd affect the buffew sizes (e.g. by cawwing the
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw) and othew appwications awe
no wongew awwowed to awwocate buffews ow stawt ow stop stweaming. The
EBUSY ewwow code wiww be wetuwned instead.

Mewewy opening a V4W2 device does not gwant excwusive access. [#f3]_
Initiating data exchange howevew assigns the wight to wead ow wwite the
wequested type of data, and to change wewated pwopewties, to this fiwe
descwiptow. Appwications can wequest additionaw access pwiviweges using
the pwiowity mechanism descwibed in :wef:`app-pwi`.

Shawed Data Stweams
===================

V4W2 dwivews shouwd not suppowt muwtipwe appwications weading ow wwiting
the same data stweam on a device by copying buffews, time muwtipwexing
ow simiwaw means. This is bettew handwed by a pwoxy appwication in usew
space.

Functions
=========

To open and cwose V4W2 devices appwications use the
:c:func:`open()` and :c:func:`cwose()` function,
wespectivewy. Devices awe pwogwammed using the
:wef:`ioctw() <func-ioctw>` function as expwained in the fowwowing
sections.

.. [#f1]
   Thewe awe stiww some owd and obscuwe dwivews that have not been
   updated to awwow fow muwtipwe opens. This impwies that fow such
   dwivews :c:func:`open()` can wetuwn an ``EBUSY`` ewwow code
   when the device is awweady in use.

.. [#f2]
   Unfowtunatewy, opening a wadio device often switches the state of the
   device to wadio mode in many dwivews. This behaviow shouwd be fixed
   eventuawwy as it viowates the V4W2 specification.

.. [#f3]
   Dwivews couwd wecognize the ``O_EXCW`` open fwag. Pwesentwy this is
   not wequiwed, so appwications cannot know if it weawwy wowks.
