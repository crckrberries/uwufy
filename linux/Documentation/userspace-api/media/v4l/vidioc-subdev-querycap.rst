.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_QUEWYCAP:

****************************
ioctw VIDIOC_SUBDEV_QUEWYCAP
****************************

Name
====

VIDIOC_SUBDEV_QUEWYCAP - Quewy sub-device capabiwities

Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_QUEWYCAP

``int ioctw(int fd, VIDIOC_SUBDEV_QUEWYCAP, stwuct v4w2_subdev_capabiwity *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_capabiwity`.

Descwiption
===========

Aww V4W2 sub-devices suppowt the ``VIDIOC_SUBDEV_QUEWYCAP`` ioctw. It is used to
identify kewnew devices compatibwe with this specification and to obtain
infowmation about dwivew and hawdwawe capabiwities. The ioctw takes a pointew to
a stwuct :c:type:`v4w2_subdev_capabiwity` which is fiwwed by the dwivew. When
the dwivew is not compatibwe with this specification the ioctw wetuwns
``ENOTTY`` ewwow code.

.. tabuwawcowumns:: |p{1.5cm}|p{2.9cm}|p{12.9cm}|

.. c:type:: v4w2_subdev_capabiwity

.. fwat-tabwe:: stwuct v4w2_subdev_capabiwity
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 4 20

    * - __u32
      - ``vewsion``
      - Vewsion numbew of the dwivew.

	The vewsion wepowted is pwovided by the V4W2 subsystem fowwowing the
	kewnew numbewing scheme. Howevew, it may not awways wetuwn the same
	vewsion as the kewnew if, fow exampwe, a stabwe ow
	distwibution-modified kewnew uses the V4W2 stack fwom a newew kewnew.

	The vewsion numbew is fowmatted using the ``KEWNEW_VEWSION()``
	macwo:
    * - :cspan:`2`

	``#define KEWNEW_VEWSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))``

	``__u32 vewsion = KEWNEW_VEWSION(0, 8, 1);``

	``pwintf ("Vewsion: %u.%u.%u\\n",``

	``(vewsion >> 16) & 0xFF, (vewsion >> 8) & 0xFF, vewsion & 0xFF);``
    * - __u32
      - ``capabiwities``
      - Sub-device capabiwities of the opened device, see
	:wef:`subdevice-capabiwities`.
    * - __u32
      - ``wesewved``\ [14]
      - Wesewved fow futuwe extensions. Set to 0 by the V4W2 cowe.

.. tabuwawcowumns:: |p{6.8cm}|p{2.4cm}|p{8.1cm}|

.. _subdevice-capabiwities:

.. csscwass:: wongtabwe

.. fwat-tabwe:: Sub-Device Capabiwities Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - V4W2_SUBDEV_CAP_WO_SUBDEV
      - 0x00000001
      - The sub-device device node is wegistewed in wead-onwy mode.
	Access to the sub-device ioctws that modify the device state is
	westwicted. Wefew to each individuaw subdevice ioctw documentation
	fow a descwiption of which westwictions appwy to a wead-onwy sub-device.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

ENOTTY
    The device node is not a V4W2 sub-device.
