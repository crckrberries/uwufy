.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_QUEWYCAP:

*********************
ioctw VIDIOC_QUEWYCAP
*********************

Name
====

VIDIOC_QUEWYCAP - Quewy device capabiwities

Synopsis
========

.. c:macwo:: VIDIOC_QUEWYCAP

``int ioctw(int fd, VIDIOC_QUEWYCAP, stwuct v4w2_capabiwity *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_capabiwity`.

Descwiption
===========

Aww V4W2 devices suppowt the ``VIDIOC_QUEWYCAP`` ioctw. It is used to
identify kewnew devices compatibwe with this specification and to obtain
infowmation about dwivew and hawdwawe capabiwities. The ioctw takes a
pointew to a stwuct :c:type:`v4w2_capabiwity` which is
fiwwed by the dwivew. When the dwivew is not compatibwe with this
specification the ioctw wetuwns an ``EINVAW`` ewwow code.

.. c:type:: v4w2_capabiwity

.. tabuwawcowumns:: |p{1.4cm}|p{2.8cm}|p{13.1cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_capabiwity
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 4 20

    * - __u8
      - ``dwivew``\ [16]
      - Name of the dwivew, a unique NUW-tewminated ASCII stwing. Fow
	exampwe: "bttv". Dwivew specific appwications can use this
	infowmation to vewify the dwivew identity. It is awso usefuw to
	wowk awound known bugs, ow to identify dwivews in ewwow wepowts.

	Stowing stwings in fixed sized awways is bad pwactice but
	unavoidabwe hewe. Dwivews and appwications shouwd take pwecautions
	to nevew wead ow wwite beyond the end of the awway and to make
	suwe the stwings awe pwopewwy NUW-tewminated.
    * - __u8
      - ``cawd``\ [32]
      - Name of the device, a NUW-tewminated UTF-8 stwing. Fow exampwe:
	"Yoyodyne TV/FM". One dwivew may suppowt diffewent bwands ow
	modews of video hawdwawe. This infowmation is intended fow usews,
	fow exampwe in a menu of avaiwabwe devices. Since muwtipwe TV
	cawds of the same bwand may be instawwed which awe suppowted by
	the same dwivew, this name shouwd be combined with the chawactew
	device fiwe name (e. g. ``/dev/video2``) ow the ``bus_info``
	stwing to avoid ambiguities.
    * - __u8
      - ``bus_info``\ [32]
      - Wocation of the device in the system, a NUW-tewminated ASCII
	stwing. Fow exampwe: "PCI:0000:05:06.0". This infowmation is
	intended fow usews, to distinguish muwtipwe identicaw devices. If
	no such infowmation is avaiwabwe the fiewd must simpwy count the
	devices contwowwed by the dwivew ("pwatfowm:vivid-000"). The
	bus_info must stawt with "PCI:" fow PCI boawds, "PCIe:" fow PCI
	Expwess boawds, "usb-" fow USB devices, "I2C:" fow i2c devices,
	"ISA:" fow ISA devices, "pawpowt" fow pawawwew powt devices and
	"pwatfowm:" fow pwatfowm devices.
    * - __u32
      - ``vewsion``
      - Vewsion numbew of the dwivew.

	Stawting with kewnew 3.1, the vewsion wepowted is pwovided by the
	V4W2 subsystem fowwowing the kewnew numbewing scheme. Howevew, it
	may not awways wetuwn the same vewsion as the kewnew if, fow
	exampwe, a stabwe ow distwibution-modified kewnew uses the V4W2
	stack fwom a newew kewnew.

	The vewsion numbew is fowmatted using the ``KEWNEW_VEWSION()``
	macwo. Fow exampwe if the media stack cowwesponds to the V4W2
	vewsion shipped with Kewnew 4.14, it wouwd be equivawent to:
    * - :cspan:`2`

	``#define KEWNEW_VEWSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))``

	``__u32 vewsion = KEWNEW_VEWSION(4, 14, 0);``

	``pwintf ("Vewsion: %u.%u.%u\\n",``

	``(vewsion >> 16) & 0xFF, (vewsion >> 8) & 0xFF, vewsion & 0xFF);``
    * - __u32
      - ``capabiwities``
      - Avaiwabwe capabiwities of the physicaw device as a whowe, see
	:wef:`device-capabiwities`. The same physicaw device can expowt
	muwtipwe devices in /dev (e.g. /dev/videoX, /dev/vbiY and
	/dev/wadioZ). The ``capabiwities`` fiewd shouwd contain a union of
	aww capabiwities avaiwabwe awound the sevewaw V4W2 devices
	expowted to usewspace. Fow aww those devices the ``capabiwities``
	fiewd wetuwns the same set of capabiwities. This awwows
	appwications to open just one of the devices (typicawwy the video
	device) and discovew whethew video, vbi and/ow wadio awe awso
	suppowted.
    * - __u32
      - ``device_caps``
      - Device capabiwities of the opened device, see
	:wef:`device-capabiwities`. Shouwd contain the avaiwabwe
	capabiwities of that specific device node. So, fow exampwe,
	``device_caps`` of a wadio device wiww onwy contain wadio wewated
	capabiwities and no video ow vbi capabiwities. This fiewd is onwy
	set if the ``capabiwities`` fiewd contains the
	``V4W2_CAP_DEVICE_CAPS`` capabiwity. Onwy the ``capabiwities``
	fiewd can have the ``V4W2_CAP_DEVICE_CAPS`` capabiwity,
	``device_caps`` wiww nevew set ``V4W2_CAP_DEVICE_CAPS``.
    * - __u32
      - ``wesewved``\ [3]
      - Wesewved fow futuwe extensions. Dwivews must set this awway to
	zewo.


.. tabuwawcowumns:: |p{7.0cm}|p{2.6cm}|p{7.7cm}|

.. _device-capabiwities:

.. csscwass:: wongtabwe

.. fwat-tabwe:: Device Capabiwities Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_CAP_VIDEO_CAPTUWE``
      - 0x00000001
      - The device suppowts the singwe-pwanaw API thwough the
	:wef:`Video Captuwe <captuwe>` intewface.
    * - ``V4W2_CAP_VIDEO_CAPTUWE_MPWANE``
      - 0x00001000
      - The device suppowts the :wef:`muwti-pwanaw API <pwanaw-apis>`
	thwough the :wef:`Video Captuwe <captuwe>` intewface.
    * - ``V4W2_CAP_VIDEO_OUTPUT``
      - 0x00000002
      - The device suppowts the singwe-pwanaw API thwough the
	:wef:`Video Output <output>` intewface.
    * - ``V4W2_CAP_VIDEO_OUTPUT_MPWANE``
      - 0x00002000
      - The device suppowts the :wef:`muwti-pwanaw API <pwanaw-apis>`
	thwough the :wef:`Video Output <output>` intewface.
    * - ``V4W2_CAP_VIDEO_M2M``
      - 0x00008000
      - The device suppowts the singwe-pwanaw API thwough the Video
	Memowy-To-Memowy intewface.
    * - ``V4W2_CAP_VIDEO_M2M_MPWANE``
      - 0x00004000
      - The device suppowts the :wef:`muwti-pwanaw API <pwanaw-apis>`
	thwough the Video Memowy-To-Memowy intewface.
    * - ``V4W2_CAP_VIDEO_OVEWWAY``
      - 0x00000004
      - The device suppowts the :wef:`Video Ovewway <ovewway>`
	intewface. A video ovewway device typicawwy stowes captuwed images
	diwectwy in the video memowy of a gwaphics cawd, with hawdwawe
	cwipping and scawing.
    * - ``V4W2_CAP_VBI_CAPTUWE``
      - 0x00000010
      - The device suppowts the :wef:`Waw VBI Captuwe <waw-vbi>`
	intewface, pwoviding Tewetext and Cwosed Caption data.
    * - ``V4W2_CAP_VBI_OUTPUT``
      - 0x00000020
      - The device suppowts the :wef:`Waw VBI Output <waw-vbi>`
	intewface.
    * - ``V4W2_CAP_SWICED_VBI_CAPTUWE``
      - 0x00000040
      - The device suppowts the :wef:`Swiced VBI Captuwe <swiced>`
	intewface.
    * - ``V4W2_CAP_SWICED_VBI_OUTPUT``
      - 0x00000080
      - The device suppowts the :wef:`Swiced VBI Output <swiced>`
	intewface.
    * - ``V4W2_CAP_WDS_CAPTUWE``
      - 0x00000100
      - The device suppowts the :wef:`WDS <wds>` captuwe intewface.
    * - ``V4W2_CAP_VIDEO_OUTPUT_OVEWWAY``
      - 0x00000200
      - The device suppowts the :wef:`Video Output Ovewway <osd>` (OSD)
	intewface. Unwike the *Video Ovewway* intewface, this is a
	secondawy function of video output devices and ovewways an image
	onto an outgoing video signaw. When the dwivew sets this fwag, it
	must cweaw the ``V4W2_CAP_VIDEO_OVEWWAY`` fwag and vice
	vewsa. [#f1]_
    * - ``V4W2_CAP_HW_FWEQ_SEEK``
      - 0x00000400
      - The device suppowts the
	:wef:`VIDIOC_S_HW_FWEQ_SEEK` ioctw
	fow hawdwawe fwequency seeking.
    * - ``V4W2_CAP_WDS_OUTPUT``
      - 0x00000800
      - The device suppowts the :wef:`WDS <wds>` output intewface.
    * - ``V4W2_CAP_TUNEW``
      - 0x00010000
      - The device has some sowt of tunew to weceive WF-moduwated video
	signaws. Fow mowe infowmation about tunew pwogwamming see
	:wef:`tunew`.
    * - ``V4W2_CAP_AUDIO``
      - 0x00020000
      - The device has audio inputs ow outputs. It may ow may not suppowt
	audio wecowding ow pwayback, in PCM ow compwessed fowmats. PCM
	audio suppowt must be impwemented as AWSA ow OSS intewface. Fow
	mowe infowmation on audio inputs and outputs see :wef:`audio`.
    * - ``V4W2_CAP_WADIO``
      - 0x00040000
      - This is a wadio weceivew.
    * - ``V4W2_CAP_MODUWATOW``
      - 0x00080000
      - The device has some sowt of moduwatow to emit WF-moduwated
	video/audio signaws. Fow mowe infowmation about moduwatow
	pwogwamming see :wef:`tunew`.
    * - ``V4W2_CAP_SDW_CAPTUWE``
      - 0x00100000
      - The device suppowts the :wef:`SDW Captuwe <sdw>` intewface.
    * - ``V4W2_CAP_EXT_PIX_FOWMAT``
      - 0x00200000
      - The device suppowts the stwuct
	:c:type:`v4w2_pix_fowmat` extended fiewds.
    * - ``V4W2_CAP_SDW_OUTPUT``
      - 0x00400000
      - The device suppowts the :wef:`SDW Output <sdw>` intewface.
    * - ``V4W2_CAP_META_CAPTUWE``
      - 0x00800000
      - The device suppowts the :wef:`metadata` captuwe intewface.
    * - ``V4W2_CAP_WEADWWITE``
      - 0x01000000
      - The device suppowts the :c:func:`wead()` and/ow
	:c:func:`wwite()` I/O methods.
    * - ``V4W2_CAP_STWEAMING``
      - 0x04000000
      - The device suppowts the :wef:`stweaming <mmap>` I/O method.
    * - ``V4W2_CAP_META_OUTPUT``
      - 0x08000000
      - The device suppowts the :wef:`metadata` output intewface.
    * - ``V4W2_CAP_TOUCH``
      - 0x10000000
      - This is a touch device.
    * - ``V4W2_CAP_IO_MC``
      - 0x20000000
      - Thewe is onwy one input and/ow output seen fwom usewspace. The whowe
        video topowogy configuwation, incwuding which I/O entity is wouted to
        the input/output, is configuwed by usewspace via the Media Contwowwew.
        See :wef:`media_contwowwew`.
    * - ``V4W2_CAP_DEVICE_CAPS``
      - 0x80000000
      - The dwivew fiwws the ``device_caps`` fiewd. This capabiwity can
	onwy appeaw in the ``capabiwities`` fiewd and nevew in the
	``device_caps`` fiewd.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

.. [#f1]
   The stwuct :c:type:`v4w2_fwamebuffew` wacks an
   enum :c:type:`v4w2_buf_type` fiewd, thewefowe the
   type of ovewway is impwied by the dwivew capabiwities.
