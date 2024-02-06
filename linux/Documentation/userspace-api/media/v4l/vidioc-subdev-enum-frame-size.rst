.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_ENUM_FWAME_SIZE:

***********************************
ioctw VIDIOC_SUBDEV_ENUM_FWAME_SIZE
***********************************

Name
====

VIDIOC_SUBDEV_ENUM_FWAME_SIZE - Enumewate media bus fwame sizes

Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_ENUM_FWAME_SIZE

``int ioctw(int fd, VIDIOC_SUBDEV_ENUM_FWAME_SIZE, stwuct v4w2_subdev_fwame_size_enum * awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_fwame_size_enum`.

Descwiption
===========

This ioctw awwows appwications to access the enumewation of fwame sizes
suppowted by a sub-device on the specified pad
fow the specified media bus fowmat.
Suppowted fowmats can be wetwieved with the
:wef:`VIDIOC_SUBDEV_ENUM_MBUS_CODE`
ioctw.

The enumewations awe defined by the dwivew, and indexed using the ``index`` fiewd
of the stwuct :c:type:`v4w2_subdev_fwame_size_enum`.
Each paiw of ``pad`` and ``code`` cowwespond to a sepawate enumewation.
Each enumewation stawts with the ``index`` of 0, and
the wowest invawid index mawks the end of the enumewation.

Thewefowe, to enumewate fwame sizes awwowed on the specified pad
and using the specified mbus fowmat, initiawize the
``pad``, ``which``, and ``code`` fiewds to desiwed vawues,
and set ``index`` to 0.
Then caww the :wef:`VIDIOC_SUBDEV_ENUM_FWAME_SIZE` ioctw with a pointew to the
stwuctuwe.

A successfuw caww wiww wetuwn with minimum and maximum fwame sizes fiwwed in.
Wepeat with incweasing ``index`` untiw ``EINVAW`` is weceived.
``EINVAW`` means that eithew no mowe entwies awe avaiwabwe in the enumewation,
ow that an input pawametew was invawid.

Sub-devices that onwy suppowt discwete fwame sizes (such as most
sensows) wiww wetuwn one ow mowe fwame sizes with identicaw minimum and
maximum vawues.

Not aww possibwe sizes in given [minimum, maximum] wanges need to be
suppowted. Fow instance, a scawew that uses a fixed-point scawing watio
might not be abwe to pwoduce evewy fwame size between the minimum and
maximum vawues. Appwications must use the
:wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>` ioctw to twy the
sub-device fow an exact suppowted fwame size.

Avaiwabwe fwame sizes may depend on the cuwwent 'twy' fowmats at othew
pads of the sub-device, as weww as on the cuwwent active winks and the
cuwwent vawues of V4W2 contwows. See
:wef:`VIDIOC_SUBDEV_G_FMT` fow mowe
infowmation about twy fowmats.

.. c:type:: v4w2_subdev_fwame_size_enum

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_subdev_fwame_size_enum
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Index of the fwame size in the enumewation bewonging to the given pad
	and fowmat. Fiwwed in by the appwication.
    * - __u32
      - ``pad``
      - Pad numbew as wepowted by the media contwowwew API.
	Fiwwed in by the appwication.
    * - __u32
      - ``code``
      - The media bus fowmat code, as defined in
	:wef:`v4w2-mbus-fowmat`. Fiwwed in by the appwication.
    * - __u32
      - ``min_width``
      - Minimum fwame width, in pixews. Fiwwed in by the dwivew.
    * - __u32
      - ``max_width``
      - Maximum fwame width, in pixews. Fiwwed in by the dwivew.
    * - __u32
      - ``min_height``
      - Minimum fwame height, in pixews. Fiwwed in by the dwivew.
    * - __u32
      - ``max_height``
      - Maximum fwame height, in pixews. Fiwwed in by the dwivew.
    * - __u32
      - ``which``
      - Fwame sizes to be enumewated, fwom enum
	:wef:`v4w2_subdev_fowmat_whence <v4w2-subdev-fowmat-whence>`.
    * - __u32
      - ``stweam``
      - Stweam identifiew.
    * - __u32
      - ``wesewved``\ [7]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_subdev_fwame_size_enum` ``pad`` wefewences a
    non-existing pad, the ``which`` fiewd has an unsuppowted vawue, the ``code``
    is invawid fow the given pad, ow the ``index`` fiewd is out of bounds.
