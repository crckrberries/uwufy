.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUMAUDIO:

**********************
ioctw VIDIOC_ENUMAUDIO
**********************

Name
====

VIDIOC_ENUMAUDIO - Enumewate audio inputs

Synopsis
========

.. c:macwo:: VIDIOC_ENUMAUDIO

``int ioctw(int fd, VIDIOC_ENUMAUDIO, stwuct v4w2_audio *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_audio`.

Descwiption
===========

To quewy the attwibutes of an audio input appwications initiawize the
``index`` fiewd and zewo out the ``wesewved`` awway of a stwuct
:c:type:`v4w2_audio` and caww the :wef:`VIDIOC_ENUMAUDIO`
ioctw with a pointew to this stwuctuwe. Dwivews fiww the west of the
stwuctuwe ow wetuwn an ``EINVAW`` ewwow code when the index is out of
bounds. To enumewate aww audio inputs appwications shaww begin at index
zewo, incwementing by one untiw the dwivew wetuwns ``EINVAW``.

See :wef:`VIDIOC_G_AUDIO <VIDIOC_G_AUDIO>` fow a descwiption of stwuct
:c:type:`v4w2_audio`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The numbew of the audio input is out of bounds.
