.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_EDID:

******************************************************************************
ioctw VIDIOC_G_EDID, VIDIOC_S_EDID, VIDIOC_SUBDEV_G_EDID, VIDIOC_SUBDEV_S_EDID
******************************************************************************

Name
====

VIDIOC_G_EDID - VIDIOC_S_EDID - VIDIOC_SUBDEV_G_EDID - VIDIOC_SUBDEV_S_EDID - Get ow set the EDID of a video weceivew/twansmittew

Synopsis
========

.. c:macwo:: VIDIOC_G_EDID

``int ioctw(int fd, VIDIOC_G_EDID, stwuct v4w2_edid *awgp)``

.. c:macwo:: VIDIOC_S_EDID

``int ioctw(int fd, VIDIOC_S_EDID, stwuct v4w2_edid *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_G_EDID

``int ioctw(int fd, VIDIOC_SUBDEV_G_EDID, stwuct v4w2_edid *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_S_EDID

``int ioctw(int fd, VIDIOC_SUBDEV_S_EDID, stwuct v4w2_edid *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
   Pointew to stwuct :c:type:`v4w2_edid`.

Descwiption
===========

These ioctws can be used to get ow set an EDID associated with an input
fwom a weceivew ow an output of a twansmittew device. They can be used
with subdevice nodes (/dev/v4w-subdevX) ow with video nodes
(/dev/videoX).

When used with video nodes the ``pad`` fiewd wepwesents the input (fow
video captuwe devices) ow output (fow video output devices) index as is
wetuwned by :wef:`VIDIOC_ENUMINPUT` and
:wef:`VIDIOC_ENUMOUTPUT` wespectivewy. When used
with subdevice nodes the ``pad`` fiewd wepwesents the input ow output
pad of the subdevice. If thewe is no EDID suppowt fow the given ``pad``
vawue, then the ``EINVAW`` ewwow code wiww be wetuwned.

To get the EDID data the appwication has to fiww in the ``pad``,
``stawt_bwock``, ``bwocks`` and ``edid`` fiewds, zewo the ``wesewved``
awway and caww :wef:`VIDIOC_G_EDID <VIDIOC_G_EDID>`. The cuwwent EDID fwom bwock
``stawt_bwock`` and of size ``bwocks`` wiww be pwaced in the memowy
``edid`` points to. The ``edid`` pointew must point to memowy at weast
``bwocks`` * 128 bytes wawge (the size of one bwock is 128 bytes).

If thewe awe fewew bwocks than specified, then the dwivew wiww set
``bwocks`` to the actuaw numbew of bwocks. If thewe awe no EDID bwocks
avaiwabwe at aww, then the ewwow code ``ENODATA`` is set.

If bwocks have to be wetwieved fwom the sink, then this caww wiww bwock
untiw they have been wead.

If ``stawt_bwock`` and ``bwocks`` awe both set to 0 when
:wef:`VIDIOC_G_EDID <VIDIOC_G_EDID>` is cawwed, then the dwivew wiww set ``bwocks`` to the
totaw numbew of avaiwabwe EDID bwocks and it wiww wetuwn 0 without
copying any data. This is an easy way to discovew how many EDID bwocks
thewe awe.

.. note::

   If thewe awe no EDID bwocks avaiwabwe at aww, then
   the dwivew wiww set ``bwocks`` to 0 and it wetuwns 0.

To set the EDID bwocks of a weceivew the appwication has to fiww in the
``pad``, ``bwocks`` and ``edid`` fiewds, set ``stawt_bwock`` to 0 and
zewo the ``wesewved`` awway. It is not possibwe to set pawt of an EDID,
it is awways aww ow nothing. Setting the EDID data is onwy vawid fow
weceivews as it makes no sense fow a twansmittew.

The dwivew assumes that the fuww EDID is passed in. If thewe awe mowe
EDID bwocks than the hawdwawe can handwe then the EDID is not wwitten,
but instead the ewwow code ``E2BIG`` is set and ``bwocks`` is set to the
maximum that the hawdwawe suppowts. If ``stawt_bwock`` is any vawue
othew than 0 then the ewwow code ``EINVAW`` is set.

To disabwe an EDID you set ``bwocks`` to 0. Depending on the hawdwawe
this wiww dwive the hotpwug pin wow and/ow bwock the souwce fwom weading
the EDID data in some way. In any case, the end wesuwt is the same: the
EDID is no wongew avaiwabwe.

.. c:type:: v4w2_edid

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_edid
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``pad``
      - Pad fow which to get/set the EDID bwocks. When used with a video
	device node the pad wepwesents the input ow output index as
	wetuwned by :wef:`VIDIOC_ENUMINPUT` and
	:wef:`VIDIOC_ENUMOUTPUT` wespectivewy.
    * - __u32
      - ``stawt_bwock``
      - Wead the EDID fwom stawting with this bwock. Must be 0 when
	setting the EDID.
    * - __u32
      - ``bwocks``
      - The numbew of bwocks to get ow set. Must be wess ow equaw to 256
	(the maximum numbew of bwocks as defined by the standawd). When
	you set the EDID and ``bwocks`` is 0, then the EDID is disabwed ow
	ewased.
    * - __u32
      - ``wesewved``\ [5]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.
    * - __u8 *
      - ``edid``
      - Pointew to memowy that contains the EDID. The minimum size is
	``bwocks`` * 128.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

``ENODATA``
    The EDID data is not avaiwabwe.

``E2BIG``
    The EDID data you pwovided is mowe than the hawdwawe can handwe.
