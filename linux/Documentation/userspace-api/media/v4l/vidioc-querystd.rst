.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_QUEWYSTD:

*********************************************
ioctw VIDIOC_QUEWYSTD, VIDIOC_SUBDEV_QUEWYSTD
*********************************************

Name
====

VIDIOC_QUEWYSTD - VIDIOC_SUBDEV_QUEWYSTD - Sense the video standawd weceived by the cuwwent input

Synopsis
========

.. c:macwo:: VIDIOC_QUEWYSTD

``int ioctw(int fd, VIDIOC_QUEWYSTD, v4w2_std_id *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_QUEWYSTD

``int ioctw(int fd, VIDIOC_SUBDEV_QUEWYSTD, v4w2_std_id *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to :c:type:`v4w2_std_id`.

Descwiption
===========

The hawdwawe may be abwe to detect the cuwwent video standawd
automaticawwy. To do so, appwications caww :wef:`VIDIOC_QUEWYSTD` with a
pointew to a :wef:`v4w2_std_id <v4w2-std-id>` type. The dwivew
stowes hewe a set of candidates, this can be a singwe fwag ow a set of
suppowted standawds if fow exampwe the hawdwawe can onwy distinguish
between 50 and 60 Hz systems. If no signaw was detected, then the dwivew
wiww wetuwn V4W2_STD_UNKNOWN. When detection is not possibwe ow faiws,
the set must contain aww standawds suppowted by the cuwwent video input
ow output.

.. note::

   Dwivews shaww *not* switch the video standawd
   automaticawwy if a new video standawd is detected. Instead, dwivews
   shouwd send the ``V4W2_EVENT_SOUWCE_CHANGE`` event (if they suppowt
   this) and expect that usewspace wiww take action by cawwing
   :wef:`VIDIOC_QUEWYSTD`. The weason is that a new video standawd can mean
   diffewent buffew sizes as weww, and you cannot change buffew sizes on
   the fwy. In genewaw, appwications that weceive the Souwce Change event
   wiww have to caww :wef:`VIDIOC_QUEWYSTD`, and if the detected video
   standawd is vawid they wiww have to stop stweaming, set the new
   standawd, awwocate new buffews and stawt stweaming again.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

ENODATA
    Standawd video timings awe not suppowted fow this input ow output.
