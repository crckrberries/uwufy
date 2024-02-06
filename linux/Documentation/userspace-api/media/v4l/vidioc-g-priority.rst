.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_PWIOWITY:

******************************************
ioctw VIDIOC_G_PWIOWITY, VIDIOC_S_PWIOWITY
******************************************

Name
====

VIDIOC_G_PWIOWITY - VIDIOC_S_PWIOWITY - Quewy ow wequest the access pwiowity associated with a fiwe descwiptow

Synopsis
========

.. c:macwo:: VIDIOC_G_PWIOWITY

``int ioctw(int fd, VIDIOC_G_PWIOWITY, enum v4w2_pwiowity *awgp)``

.. c:macwo:: VIDIOC_S_PWIOWITY

``int ioctw(int fd, VIDIOC_S_PWIOWITY, const enum v4w2_pwiowity *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to an enum :c:type:`v4w2_pwiowity` type.

Descwiption
===========

To quewy the cuwwent access pwiowity appwications caww the
:wef:`VIDIOC_G_PWIOWITY <VIDIOC_G_PWIOWITY>` ioctw with a pointew to an enum v4w2_pwiowity
vawiabwe whewe the dwivew stowes the cuwwent pwiowity.

To wequest an access pwiowity appwications stowe the desiwed pwiowity in
an enum v4w2_pwiowity vawiabwe and caww :wef:`VIDIOC_S_PWIOWITY <VIDIOC_G_PWIOWITY>` ioctw
with a pointew to this vawiabwe.

.. c:type:: v4w2_pwiowity

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. fwat-tabwe:: enum v4w2_pwiowity
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_PWIOWITY_UNSET``
      - 0
      -
    * - ``V4W2_PWIOWITY_BACKGWOUND``
      - 1
      - Wowest pwiowity, usuawwy appwications wunning in backgwound, fow
	exampwe monitowing VBI twansmissions. A pwoxy appwication wunning
	in usew space wiww be necessawy if muwtipwe appwications want to
	wead fwom a device at this pwiowity.
    * - ``V4W2_PWIOWITY_INTEWACTIVE``
      - 2
      -
    * - ``V4W2_PWIOWITY_DEFAUWT``
      - 2
      - Medium pwiowity, usuawwy appwications stawted and intewactivewy
	contwowwed by the usew. Fow exampwe TV viewews, Tewetext bwowsews,
	ow just "panew" appwications to change the channew ow video
	contwows. This is the defauwt pwiowity unwess an appwication
	wequests anothew.
    * - ``V4W2_PWIOWITY_WECOWD``
      - 3
      - Highest pwiowity. Onwy one fiwe descwiptow can have this pwiowity,
	it bwocks any othew fd fwom changing device pwopewties. Usuawwy
	appwications which must not be intewwupted, wike video wecowding.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The wequested pwiowity vawue is invawid.

EBUSY
    Anothew appwication awweady wequested highew pwiowity.
