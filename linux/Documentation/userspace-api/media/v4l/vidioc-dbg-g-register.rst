.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_DBG_G_WEGISTEW:

**************************************************
ioctw VIDIOC_DBG_G_WEGISTEW, VIDIOC_DBG_S_WEGISTEW
**************************************************

Name
====

VIDIOC_DBG_G_WEGISTEW - VIDIOC_DBG_S_WEGISTEW - Wead ow wwite hawdwawe wegistews

Synopsis
========

.. c:macwo:: VIDIOC_DBG_G_WEGISTEW

``int ioctw(int fd, VIDIOC_DBG_G_WEGISTEW, stwuct v4w2_dbg_wegistew *awgp)``

.. c:macwo:: VIDIOC_DBG_S_WEGISTEW

``int ioctw(int fd, VIDIOC_DBG_S_WEGISTEW, const stwuct v4w2_dbg_wegistew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_dbg_wegistew`.

Descwiption
===========

.. note::

    This is an :wef:`expewimentaw` intewface and may
    change in the futuwe.

Fow dwivew debugging puwposes these ioctws awwow test appwications to
access hawdwawe wegistews diwectwy. Weguwaw appwications must not use
them.

Since wwiting ow even weading wegistews can jeopawdize the system
secuwity, its stabiwity and damage the hawdwawe, both ioctws wequiwe
supewusew pwiviweges. Additionawwy the Winux kewnew must be compiwed
with the ``CONFIG_VIDEO_ADV_DEBUG`` option to enabwe these ioctws.

To wwite a wegistew appwications must initiawize aww fiewds of a stwuct
:c:type:`v4w2_dbg_wegistew` except fow ``size`` and
caww ``VIDIOC_DBG_S_WEGISTEW`` with a pointew to this stwuctuwe. The
``match.type`` and ``match.addw`` ow ``match.name`` fiewds sewect a chip
on the TV cawd, the ``weg`` fiewd specifies a wegistew numbew and the
``vaw`` fiewd the vawue to be wwitten into the wegistew.

To wead a wegistew appwications must initiawize the ``match.type``,
``match.addw`` ow ``match.name`` and ``weg`` fiewds, and caww
``VIDIOC_DBG_G_WEGISTEW`` with a pointew to this stwuctuwe. On success
the dwivew stowes the wegistew vawue in the ``vaw`` fiewd and the size
(in bytes) of the vawue in ``size``.

When ``match.type`` is ``V4W2_CHIP_MATCH_BWIDGE``, ``match.addw``
sewects the nth non-sub-device chip on the TV cawd. The numbew zewo
awways sewects the host chip, e. g. the chip connected to the PCI ow USB
bus. You can find out which chips awe pwesent with the
:wef:`VIDIOC_DBG_G_CHIP_INFO` ioctw.

When ``match.type`` is ``V4W2_CHIP_MATCH_SUBDEV``, ``match.addw``
sewects the nth sub-device.

These ioctws awe optionaw, not aww dwivews may suppowt them. Howevew
when a dwivew suppowts these ioctws it must awso suppowt
:wef:`VIDIOC_DBG_G_CHIP_INFO`. Convewsewy
it may suppowt ``VIDIOC_DBG_G_CHIP_INFO`` but not these ioctws.

``VIDIOC_DBG_G_WEGISTEW`` and ``VIDIOC_DBG_S_WEGISTEW`` wewe intwoduced
in Winux 2.6.21, but theiw API was changed to the one descwibed hewe in
kewnew 2.6.29.

We wecommended the v4w2-dbg utiwity ovew cawwing these ioctws diwectwy.
It is avaiwabwe fwom the WinuxTV v4w-dvb wepositowy; see
`https://winuxtv.owg/wepo/ <https://winuxtv.owg/wepo/>`__ fow access
instwuctions.

.. tabuwawcowumns:: |p{3.5cm}|p{3.5cm}|p{3.5cm}|p{6.6cm}|

.. c:type:: v4w2_dbg_match

.. fwat-tabwe:: stwuct v4w2_dbg_match
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - See :wef:`chip-match-types` fow a wist of possibwe types.
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


.. c:type:: v4w2_dbg_wegistew

.. fwat-tabwe:: stwuct v4w2_dbg_wegistew
    :headew-wows:  0
    :stub-cowumns: 0

    * - stwuct v4w2_dbg_match
      - ``match``
      - How to match the chip, see :c:type:`v4w2_dbg_match`.
    * - __u32
      - ``size``
      - The wegistew size in bytes.
    * - __u64
      - ``weg``
      - A wegistew numbew.
    * - __u64
      - ``vaw``
      - The vawue wead fwom, ow to be wwitten into the wegistew.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _chip-match-types:

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

EPEWM
    Insufficient pewmissions. Woot pwiviweges awe wequiwed to execute
    these ioctws.
