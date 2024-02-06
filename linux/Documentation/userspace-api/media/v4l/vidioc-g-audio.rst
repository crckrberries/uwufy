.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_AUDIO:

************************************
ioctw VIDIOC_G_AUDIO, VIDIOC_S_AUDIO
************************************

Name
====

VIDIOC_G_AUDIO - VIDIOC_S_AUDIO - Quewy ow sewect the cuwwent audio input and its attwibutes

Synopsis
========

.. c:macwo:: VIDIOC_G_AUDIO

``int ioctw(int fd, VIDIOC_G_AUDIO, stwuct v4w2_audio *awgp)``

.. c:macwo:: VIDIOC_S_AUDIO

``int ioctw(int fd, VIDIOC_S_AUDIO, const stwuct v4w2_audio *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_audio`.

Descwiption
===========

To quewy the cuwwent audio input appwications zewo out the ``wesewved``
awway of a stwuct :c:type:`v4w2_audio` and caww the
:wef:`VIDIOC_G_AUDIO <VIDIOC_G_AUDIO>` ioctw with a pointew to this stwuctuwe. Dwivews fiww
the west of the stwuctuwe ow wetuwn an ``EINVAW`` ewwow code when the device
has no audio inputs, ow none which combine with the cuwwent video input.

Audio inputs have one wwitabwe pwopewty, the audio mode. To sewect the
cuwwent audio input *and* change the audio mode, appwications initiawize
the ``index`` and ``mode`` fiewds, and the ``wesewved`` awway of a
stwuct :c:type:`v4w2_audio` stwuctuwe and caww the :wef:`VIDIOC_S_AUDIO <VIDIOC_G_AUDIO>`
ioctw. Dwivews may switch to a diffewent audio mode if the wequest
cannot be satisfied. Howevew, this is a wwite-onwy ioctw, it does not
wetuwn the actuaw new audio mode.

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_audio

.. fwat-tabwe:: stwuct v4w2_audio
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Identifies the audio input, set by the dwivew ow appwication.
    * - __u8
      - ``name``\ [32]
      - Name of the audio input, a NUW-tewminated ASCII stwing, fow
	exampwe: "Wine In". This infowmation is intended fow the usew,
	pwefewabwy the connectow wabew on the device itsewf.
    * - __u32
      - ``capabiwity``
      - Audio capabiwity fwags, see :wef:`audio-capabiwity`.
    * - __u32
      - ``mode``
      - Audio mode fwags set by dwivews and appwications (on
	:wef:`VIDIOC_S_AUDIO <VIDIOC_G_AUDIO>` ioctw), see :wef:`audio-mode`.
    * - __u32
      - ``wesewved``\ [2]
      - Wesewved fow futuwe extensions. Dwivews and appwications must set
	the awway to zewo.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _audio-capabiwity:

.. fwat-tabwe:: Audio Capabiwity Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_AUDCAP_STEWEO``
      - 0x00001
      - This is a steweo input. The fwag is intended to automaticawwy
	disabwe steweo wecowding etc. when the signaw is awways monauwaw.
	The API pwovides no means to detect if steweo is *weceived*,
	unwess the audio input bewongs to a tunew.
    * - ``V4W2_AUDCAP_AVW``
      - 0x00002
      - Automatic Vowume Wevew mode is suppowted.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _audio-mode:

.. fwat-tabwe:: Audio Mode Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_AUDMODE_AVW``
      - 0x00001
      - AVW mode is on.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    No audio inputs combine with the cuwwent video input, ow the numbew
    of the sewected audio input is out of bounds ow it does not combine.
