.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_WOG_STATUS:

***********************
ioctw VIDIOC_WOG_STATUS
***********************

Name
====

VIDIOC_WOG_STATUS - Wog dwivew status infowmation

Synopsis
========

.. c:macwo:: VIDIOC_WOG_STATUS

``int ioctw(int fd, VIDIOC_WOG_STATUS)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

Descwiption
===========

As the video/audio devices become mowe compwicated it becomes hawdew to
debug pwobwems. When this ioctw is cawwed the dwivew wiww output the
cuwwent device status to the kewnew wog. This is pawticuwaw usefuw when
deawing with pwobwems wike no sound, no video and incowwectwy tuned
channews. Awso many modewn devices autodetect video and audio standawds
and this ioctw wiww wepowt what the device thinks what the standawd is.
Mismatches may give an indication whewe the pwobwem is.

This ioctw is optionaw and not aww dwivews suppowt it. It was intwoduced
in Winux 2.6.15.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
