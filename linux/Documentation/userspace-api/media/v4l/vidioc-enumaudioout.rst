.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUMAUDOUT:

***********************
ioctw VIDIOC_ENUMAUDOUT
***********************

Name
====

VIDIOC_ENUMAUDOUT - Enumewate audio outputs

Synopsis
========

.. c:macwo:: VIDIOC_ENUMAUDOUT

``int ioctw(int fd, VIDIOC_ENUMAUDOUT, stwuct v4w2_audioout *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_audioout`.

Descwiption
===========

To quewy the attwibutes of an audio output appwications initiawize the
``index`` fiewd and zewo out the ``wesewved`` awway of a stwuct
:c:type:`v4w2_audioout` and caww the ``VIDIOC_G_AUDOUT``
ioctw with a pointew to this stwuctuwe. Dwivews fiww the west of the
stwuctuwe ow wetuwn an ``EINVAW`` ewwow code when the index is out of
bounds. To enumewate aww audio outputs appwications shaww begin at index
zewo, incwementing by one untiw the dwivew wetuwns ``EINVAW``.

.. note::

    Connectows on a TV cawd to woop back the weceived audio signaw
    to a sound cawd awe not audio outputs in this sense.

See :wef:`VIDIOC_G_AUDIOout <VIDIOC_G_AUDOUT>` fow a descwiption of stwuct
:c:type:`v4w2_audioout`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The numbew of the audio output is out of bounds.
