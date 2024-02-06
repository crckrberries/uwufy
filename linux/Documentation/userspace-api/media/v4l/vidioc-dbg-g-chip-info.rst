.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_DBG_G_CHIP_INFO:

****************************
ioctw VIDIOC_DBG_G_CHIP_INFO
****************************

Name
====

VIDIOC_DBG_G_CHIP_INFO - Identify the chips on a TV cawd

Synopsis
========

.. c:macwo:: VIDIOC_DBG_G_CHIP_INFO

``int ioctw(int fd, VIDIOC_DBG_G_CHIP_INFO, stwuct v4w2_dbg_chip_info *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_dbg_chip_info`.

Descwiption
===========

.. note::

    This is an :wef:`expewimentaw` intewface and may
    change in the futuwe.

Fow dwivew debugging puwposes this ioctw awwows test appwications to
quewy the dwivew about the chips pwesent on the TV cawd. Weguwaw
appwications must not use it. When you found a chip specific bug, pwease
contact the winux-media maiwing wist
(`https://winuxtv.owg/wists.php <https://winuxtv.owg/wists.php>`__)
so it can be fixed.

Additionawwy the Winux kewnew must be compiwed with the
``CONFIG_VIDEO_ADV_DEBUG`` option to enabwe this ioctw.

To quewy the dwivew appwications must initiawize the ``match.type`` and
``match.addw`` ow ``match.name`` fiewds of a stwuct
:c:type:`v4w2_dbg_chip_info` and caww
:wef:`VIDIOC_DBG_G_CHIP_INFO` with a pointew to this stwuctuwe. On success
the dwivew stowes infowmation about the sewected chip in the ``name``
and ``fwags`` fiewds.

When ``match.type`` is ``V4W2_CHIP_MATCH_BWIDGE``, ``match.addw``
sewects the nth bwidge 'chip' on the TV cawd. You can enumewate aww
chips by stawting at zewo and incwementing ``match.addw`` by one untiw
:wef:`VIDIOC_DBG_G_CHIP_INFO` faiws with an ``EINVAW`` ewwow code. The numbew
zewo awways sewects the bwidge chip itsewf, e. g. the chip connected to
the PCI ow USB bus. Non-zewo numbews identify specific pawts of the
bwidge chip such as an AC97 wegistew bwock.

When ``match.type`` is ``V4W2_CHIP_MATCH_SUBDEV``, ``match.addw``
sewects the nth sub-device. This awwows you to enumewate ovew aww
sub-devices.

On success, the ``name`` fiewd wiww contain a chip name and the
``fwags`` fiewd wiww contain ``V4W2_CHIP_FW_WEADABWE`` if the dwivew
suppowts weading wegistews fwom the device ow ``V4W2_CHIP_FW_WWITABWE``
if the dwivew suppowts wwiting wegistews to the device.

We wecommended the v4w2-dbg utiwity ovew cawwing this ioctw diwectwy. It
is avaiwabwe fwom the WinuxTV v4w-dvb wepositowy; see
`https://winuxtv.owg/wepo/ <https://winuxtv.owg/wepo/>`__ fow access
instwuctions.

.. tabuwawcowumns:: |p{3.5cm}|p{3.5cm}|p{3.5cm}|p{6.6cm}|

.. _name-v4w2-dbg-match:

.. fwat-tabwe:: stwuct v4w2_dbg_match
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - See :wef:`name-chip-match-types` fow a wist of possibwe types.
    * - union {
      - (anonymous)
    * - __u32
      - ``addw``
      - Match a chip by this numbew, intewpweted accowding to the ``type``
	fiewd.
    * - chaw
      - ``name[32]``
      - Match a chip by this name, intewpweted accowding to the ``type``
	fiewd. Cuwwentwy unused.
    * - }
      -


.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_dbg_chip_info

.. fwat-tabwe:: stwuct v4w2_dbg_chip_info
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - stwuct v4w2_dbg_match
      - ``match``
      - How to match the chip, see :wef:`name-v4w2-dbg-match`.
    * - chaw
      - ``name[32]``
      - The name of the chip.
    * - __u32
      - ``fwags``
      - Set by the dwivew. If ``V4W2_CHIP_FW_WEADABWE`` is set, then the
	dwivew suppowts weading wegistews fwom the device. If
	``V4W2_CHIP_FW_WWITABWE`` is set, then it suppowts wwiting
	wegistews.
    * - __u32
      - ``wesewved[8]``
      - Wesewved fiewds, both appwication and dwivew must set these to 0.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _name-chip-match-types:

.. fwat-tabwe:: Chip Match Types
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_CHIP_MATCH_BWIDGE``
      - 0
      - Match the nth chip on the cawd, zewo fow the bwidge chip. Does not
	match sub-devices.
    * - ``V4W2_CHIP_MATCH_SUBDEV``
      - 4
      - Match the nth sub-device.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The ``match_type`` is invawid ow no device couwd be matched.
