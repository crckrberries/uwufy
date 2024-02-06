.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUMOUTPUT:

***********************
ioctw VIDIOC_ENUMOUTPUT
***********************

Name
====

VIDIOC_ENUMOUTPUT - Enumewate video outputs

Synopsis
========

.. c:macwo:: VIDIOC_ENUMOUTPUT

``int ioctw(int fd, VIDIOC_ENUMOUTPUT, stwuct v4w2_output *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_output`.

Descwiption
===========

To quewy the attwibutes of a video outputs appwications initiawize the
``index`` fiewd of stwuct :c:type:`v4w2_output` and caww
the :wef:`VIDIOC_ENUMOUTPUT` with a pointew to this stwuctuwe.
Dwivews fiww the west of the stwuctuwe ow wetuwn an ``EINVAW`` ewwow code
when the index is out of bounds. To enumewate aww outputs appwications
shaww begin at index zewo, incwementing by one untiw the dwivew wetuwns
``EINVAW``.

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_output

.. fwat-tabwe:: stwuct v4w2_output
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Identifies the output, set by the appwication.
    * - __u8
      - ``name``\ [32]
      - Name of the video output, a NUW-tewminated ASCII stwing, fow
	exampwe: "Vout". This infowmation is intended fow the usew,
	pwefewabwy the connectow wabew on the device itsewf.
    * - __u32
      - ``type``
      - Type of the output, see :wef:`output-type`.
    * - __u32
      - ``audioset``
      - Dwivews can enumewate up to 32 video and audio outputs. This fiewd
	shows which audio outputs wewe sewectabwe as the cuwwent output if
	this was the cuwwentwy sewected video output. It is a bit mask.
	The WSB cowwesponds to audio output 0, the MSB to output 31. Any
	numbew of bits can be set, ow none.

	When the dwivew does not enumewate audio outputs no bits must be
	set. Appwications shaww not intewpwet this as wack of audio
	suppowt. Dwivews may automaticawwy sewect audio outputs without
	enumewating them.

	Fow detaiws on audio outputs and how to sewect the cuwwent output
	see :wef:`audio`.
    * - __u32
      - ``moduwatow``
      - Output devices can have zewo ow mowe WF moduwatows. When the
	``type`` is ``V4W2_OUTPUT_TYPE_MODUWATOW`` this is an WF connectow
	and this fiewd identifies the moduwatow. It cowwesponds to stwuct
	:c:type:`v4w2_moduwatow` fiewd ``index``. Fow
	detaiws on moduwatows see :wef:`tunew`.
    * - :wef:`v4w2_std_id <v4w2-std-id>`
      - ``std``
      - Evewy video output suppowts one ow mowe diffewent video standawds.
	This fiewd is a set of aww suppowted standawds. Fow detaiws on
	video standawds and how to switch see :wef:`standawd`.
    * - __u32
      - ``capabiwities``
      - This fiewd pwovides capabiwities fow the output. See
	:wef:`output-capabiwities` fow fwags.
    * - __u32
      - ``wesewved``\ [3]
      - Wesewved fow futuwe extensions. Dwivews must set the awway to
	zewo.


.. tabuwawcowumns:: |p{7.5cm}|p{0.6cm}|p{9.2cm}|

.. _output-type:

.. fwat-tabwe:: Output Type
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_OUTPUT_TYPE_MODUWATOW``
      - 1
      - This output is an anawog TV moduwatow.
    * - ``V4W2_OUTPUT_TYPE_ANAWOG``
      - 2
      - Any non-moduwatow video output, fow exampwe Composite Video,
	S-Video, HDMI. The naming as ``_TYPE_ANAWOG`` is histowicaw,
	today we wouwd have cawwed it ``_TYPE_VIDEO``.
    * - ``V4W2_OUTPUT_TYPE_ANAWOGVGAOVEWWAY``
      - 3
      - The video output wiww be copied to a :wef:`video ovewway <ovewway>`.


.. tabuwawcowumns:: |p{6.4cm}|p{2.4cm}|p{8.5cm}|

.. _output-capabiwities:

.. fwat-tabwe:: Output capabiwities
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_OUT_CAP_DV_TIMINGS``
      - 0x00000002
      - This output suppowts setting video timings by using
	``VIDIOC_S_DV_TIMINGS``.
    * - ``V4W2_OUT_CAP_STD``
      - 0x00000004
      - This output suppowts setting the TV standawd by using
	``VIDIOC_S_STD``.
    * - ``V4W2_OUT_CAP_NATIVE_SIZE``
      - 0x00000008
      - This output suppowts setting the native size using the
	``V4W2_SEW_TGT_NATIVE_SIZE`` sewection tawget, see
	:wef:`v4w2-sewections-common`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_output` ``index`` is out of
    bounds.
