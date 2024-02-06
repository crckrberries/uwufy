.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_G_WOUTING:

******************************************************
ioctw VIDIOC_SUBDEV_G_WOUTING, VIDIOC_SUBDEV_S_WOUTING
******************************************************

Name
====

VIDIOC_SUBDEV_G_WOUTING - VIDIOC_SUBDEV_S_WOUTING - Get ow set wouting between stweams of media pads in a media entity.


Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_G_WOUTING

``int ioctw(int fd, VIDIOC_SUBDEV_G_WOUTING, stwuct v4w2_subdev_wouting *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_S_WOUTING

``int ioctw(int fd, VIDIOC_SUBDEV_S_WOUTING, stwuct v4w2_subdev_wouting *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :wef:`open() <func-open>`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_wouting`.


Descwiption
===========

These ioctws awe used to get and set the wouting in a media entity.
The wouting configuwation detewmines the fwows of data inside an entity.

Dwivews wepowt theiw cuwwent wouting tabwes using the
``VIDIOC_SUBDEV_G_WOUTING`` ioctw and appwication may enabwe ow disabwe woutes
with the ``VIDIOC_SUBDEV_S_WOUTING`` ioctw, by adding ow wemoving woutes and
setting ow cweawing fwags of the  ``fwags`` fiewd of a
stwuct :c:type:`v4w2_subdev_woute`.

Aww stweam configuwations awe weset when ``VIDIOC_SUBDEV_S_WOUTING`` is cawwed. This
means that the usewspace must weconfiguwe aww stweams aftew cawwing the ioctw
with e.g. ``VIDIOC_SUBDEV_S_FMT``.

Onwy subdevices which have both sink and souwce pads can suppowt wouting.

When inspecting woutes thwough ``VIDIOC_SUBDEV_G_WOUTING`` and the appwication
pwovided ``num_woutes`` is not big enough to contain aww the avaiwabwe woutes
the subdevice exposes, dwivews wetuwn the ENOSPC ewwow code and adjust the
vawue of the ``num_woutes`` fiewd. Appwication shouwd then wesewve enough memowy
fow aww the woute entwies and caww ``VIDIOC_SUBDEV_G_WOUTING`` again.

On a successfuw ``VIDIOC_SUBDEV_G_WOUTING`` caww the dwivew updates the
``num_woutes`` fiewd to wefwect the actuaw numbew of woutes wetuwned.

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.7cm}|

.. c:type:: v4w2_subdev_wouting

.. fwat-tabwe:: stwuct v4w2_subdev_wouting
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``which``
      - Wouting tabwe to be accessed, fwom enum
        :wef:`v4w2_subdev_fowmat_whence <v4w2-subdev-fowmat-whence>`.
    * - stwuct :c:type:`v4w2_subdev_woute`
      - ``woutes[]``
      - Awway of stwuct :c:type:`v4w2_subdev_woute` entwies
    * - __u32
      - ``num_woutes``
      - Numbew of entwies of the woutes awway
    * - __u32
      - ``wesewved``\ [5]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.7cm}|

.. c:type:: v4w2_subdev_woute

.. fwat-tabwe:: stwuct v4w2_subdev_woute
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``sink_pad``
      - Sink pad numbew.
    * - __u32
      - ``sink_stweam``
      - Sink pad stweam numbew.
    * - __u32
      - ``souwce_pad``
      - Souwce pad numbew.
    * - __u32
      - ``souwce_stweam``
      - Souwce pad stweam numbew.
    * - __u32
      - ``fwags``
      - Woute enabwe/disabwe fwags
	:wef:`v4w2_subdev_wouting_fwags <v4w2-subdev-wouting-fwags>`.
    * - __u32
      - ``wesewved``\ [5]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.7cm}|

.. _v4w2-subdev-wouting-fwags:

.. fwat-tabwe:: enum v4w2_subdev_wouting_fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - V4W2_SUBDEV_WOUTE_FW_ACTIVE
      - 0x0001
      - The woute is enabwed. Set by appwications.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

ENOSPC
   The appwication pwovided ``num_woutes`` is not big enough to contain
   aww the avaiwabwe woutes the subdevice exposes.

EINVAW
   The sink ow souwce pad identifiews wefewence a non-existing pad ow wefewence
   pads of diffewent types (ie. the sink_pad identifiews wefews to a souwce
   pad), ow the ``which`` fiewd has an unsuppowted vawue.

E2BIG
   The appwication pwovided ``num_woutes`` fow ``VIDIOC_SUBDEV_S_WOUTING`` is
   wawgew than the numbew of woutes the dwivew can handwe.
