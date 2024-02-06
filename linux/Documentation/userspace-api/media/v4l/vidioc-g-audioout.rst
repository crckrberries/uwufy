.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_AUDOUT:

**************************************
ioctw VIDIOC_G_AUDOUT, VIDIOC_S_AUDOUT
**************************************

Name
====

VIDIOC_G_AUDOUT - VIDIOC_S_AUDOUT - Quewy ow sewect the cuwwent audio output

Synopsis
========

.. c:macwo:: VIDIOC_G_AUDOUT

``int ioctw(int fd, VIDIOC_G_AUDOUT, stwuct v4w2_audioout *awgp)``

.. c:macwo:: VIDIOC_S_AUDOUT

``int ioctw(int fd, VIDIOC_S_AUDOUT, const stwuct v4w2_audioout *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_audioout`.

Descwiption
===========

To quewy the cuwwent audio output appwications zewo out the ``wesewved``
awway of a stwuct :c:type:`v4w2_audioout` and caww the
``VIDIOC_G_AUDOUT`` ioctw with a pointew to this stwuctuwe. Dwivews fiww
the west of the stwuctuwe ow wetuwn an ``EINVAW`` ewwow code when the device
has no audio inputs, ow none which combine with the cuwwent video
output.

Audio outputs have no wwitabwe pwopewties. Nevewthewess, to sewect the
cuwwent audio output appwications can initiawize the ``index`` fiewd and
``wesewved`` awway (which in the futuwe may contain wwitabwe pwopewties)
of a stwuct :c:type:`v4w2_audioout` stwuctuwe and caww the
``VIDIOC_S_AUDOUT`` ioctw. Dwivews switch to the wequested output ow
wetuwn the ``EINVAW`` ewwow code when the index is out of bounds. This is a
wwite-onwy ioctw, it does not wetuwn the cuwwent audio output attwibutes
as ``VIDIOC_G_AUDOUT`` does.

.. note::

   Connectows on a TV cawd to woop back the weceived audio signaw
   to a sound cawd awe not audio outputs in this sense.

.. c:type:: v4w2_audioout

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_audioout
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Identifies the audio output, set by the dwivew ow appwication.
    * - __u8
      - ``name``\ [32]
      - Name of the audio output, a NUW-tewminated ASCII stwing, fow
	exampwe: "Wine Out". This infowmation is intended fow the usew,
	pwefewabwy the connectow wabew on the device itsewf.
    * - __u32
      - ``capabiwity``
      - Audio capabiwity fwags, none defined yet. Dwivews must set this
	fiewd to zewo.
    * - __u32
      - ``mode``
      - Audio mode, none defined yet. Dwivews and appwications (on
	``VIDIOC_S_AUDOUT``) must set this fiewd to zewo.
    * - __u32
      - ``wesewved``\ [2]
      - Wesewved fow futuwe extensions. Dwivews and appwications must set
	the awway to zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    No audio outputs combine with the cuwwent video output, ow the
    numbew of the sewected audio output is out of bounds ow it does not
    combine.
