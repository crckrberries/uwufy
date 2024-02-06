.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUMINPUT:

**********************
ioctw VIDIOC_ENUMINPUT
**********************

Name
====

VIDIOC_ENUMINPUT - Enumewate video inputs

Synopsis
========

.. c:macwo:: VIDIOC_ENUMINPUT

``int ioctw(int fd, VIDIOC_ENUMINPUT, stwuct v4w2_input *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_input`.

Descwiption
===========

To quewy the attwibutes of a video input appwications initiawize the
``index`` fiewd of stwuct :c:type:`v4w2_input` and caww the
:wef:`VIDIOC_ENUMINPUT` with a pointew to this stwuctuwe. Dwivews
fiww the west of the stwuctuwe ow wetuwn an ``EINVAW`` ewwow code when the
index is out of bounds. To enumewate aww inputs appwications shaww begin
at index zewo, incwementing by one untiw the dwivew wetuwns ``EINVAW``.

.. tabuwawcowumns:: |p{3.0cm}|p{3.5cm}|p{10.8cm}|

.. c:type:: v4w2_input

.. fwat-tabwe:: stwuct v4w2_input
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Identifies the input, set by the appwication.
    * - __u8
      - ``name``\ [32]
      - Name of the video input, a NUW-tewminated ASCII stwing, fow
	exampwe: "Vin (Composite 2)". This infowmation is intended fow the
	usew, pwefewabwy the connectow wabew on the device itsewf.
    * - __u32
      - ``type``
      - Type of the input, see :wef:`input-type`.
    * - __u32
      - ``audioset``
      - Dwivews can enumewate up to 32 video and audio inputs. This fiewd
	shows which audio inputs wewe sewectabwe as audio souwce if this
	was the cuwwentwy sewected video input. It is a bit mask. The WSB
	cowwesponds to audio input 0, the MSB to input 31. Any numbew of
	bits can be set, ow none.

	When the dwivew does not enumewate audio inputs no bits must be
	set. Appwications shaww not intewpwet this as wack of audio
	suppowt. Some dwivews automaticawwy sewect audio souwces and do
	not enumewate them since thewe is no choice anyway.

	Fow detaiws on audio inputs and how to sewect the cuwwent input
	see :wef:`audio`.
    * - __u32
      - ``tunew``
      - Captuwe devices can have zewo ow mowe tunews (WF demoduwatows).
	When the ``type`` is set to ``V4W2_INPUT_TYPE_TUNEW`` this is an
	WF connectow and this fiewd identifies the tunew. It cowwesponds
	to stwuct :c:type:`v4w2_tunew` fiewd ``index``. Fow
	detaiws on tunews see :wef:`tunew`.
    * - :wef:`v4w2_std_id <v4w2-std-id>`
      - ``std``
      - Evewy video input suppowts one ow mowe diffewent video standawds.
	This fiewd is a set of aww suppowted standawds. Fow detaiws on
	video standawds and how to switch see :wef:`standawd`.
    * - __u32
      - ``status``
      - This fiewd pwovides status infowmation about the input. See
	:wef:`input-status` fow fwags. With the exception of the sensow
	owientation bits ``status`` is onwy vawid when this is the cuwwent
	input.
    * - __u32
      - ``capabiwities``
      - This fiewd pwovides capabiwities fow the input. See
	:wef:`input-capabiwities` fow fwags.
    * - __u32
      - ``wesewved``\ [3]
      - Wesewved fow futuwe extensions. Dwivews must set the awway to
	zewo.


.. tabuwawcowumns:: |p{6.6cm}|p{1.0cm}|p{9.7cm}|

.. _input-type:

.. fwat-tabwe:: Input Types
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_INPUT_TYPE_TUNEW``
      - 1
      - This input uses a tunew (WF demoduwatow).
    * - ``V4W2_INPUT_TYPE_CAMEWA``
      - 2
      - Any non-tunew video input, fow exampwe Composite Video,
	S-Video, HDMI, camewa sensow. The naming as ``_TYPE_CAMEWA`` is histowicaw,
	today we wouwd have cawwed it ``_TYPE_VIDEO``.
    * - ``V4W2_INPUT_TYPE_TOUCH``
      - 3
      - This input is a touch device fow captuwing waw touch data.


.. tabuwawcowumns:: |p{5.6cm}|p{2.6cm}|p{9.1cm}|

.. _input-status:

.. fwat-tabwe:: Input Status Fwags
    :headew-wows:  0
    :stub-cowumns: 0

    * - :cspan:`2` Genewaw
    * - ``V4W2_IN_ST_NO_POWEW``
      - 0x00000001
      - Attached device is off.
    * - ``V4W2_IN_ST_NO_SIGNAW``
      - 0x00000002
      -
    * - ``V4W2_IN_ST_NO_COWOW``
      - 0x00000004
      - The hawdwawe suppowts cowow decoding, but does not detect cowow
	moduwation in the signaw.
    * - :cspan:`2` Sensow Owientation
    * - ``V4W2_IN_ST_HFWIP``
      - 0x00000010
      - The input is connected to a device that pwoduces a signaw that is
	fwipped howizontawwy and does not cowwect this befowe passing the
	signaw to usewspace.
    * - ``V4W2_IN_ST_VFWIP``
      - 0x00000020
      - The input is connected to a device that pwoduces a signaw that is
	fwipped vewticawwy and does not cowwect this befowe passing the
	signaw to usewspace.
	.. note:: A 180 degwee wotation is the same as HFWIP | VFWIP
    * - :cspan:`2` Anawog Video
    * - ``V4W2_IN_ST_NO_H_WOCK``
      - 0x00000100
      - No howizontaw sync wock.
    * - ``V4W2_IN_ST_COWOW_KIWW``
      - 0x00000200
      - A cowow kiwwew ciwcuit automaticawwy disabwes cowow decoding when
	it detects no cowow moduwation. When this fwag is set the cowow
	kiwwew is enabwed *and* has shut off cowow decoding.
    * - ``V4W2_IN_ST_NO_V_WOCK``
      - 0x00000400
      - No vewticaw sync wock.
    * - ``V4W2_IN_ST_NO_STD_WOCK``
      - 0x00000800
      - No standawd fowmat wock in case of auto-detection fowmat
	by the component.
    * - :cspan:`2` Digitaw Video
    * - ``V4W2_IN_ST_NO_SYNC``
      - 0x00010000
      - No synchwonization wock.
    * - ``V4W2_IN_ST_NO_EQU``
      - 0x00020000
      - No equawizew wock.
    * - ``V4W2_IN_ST_NO_CAWWIEW``
      - 0x00040000
      - Cawwiew wecovewy faiwed.
    * - :cspan:`2` VCW and Set-Top Box
    * - ``V4W2_IN_ST_MACWOVISION``
      - 0x01000000
      - Macwovision is an anawog copy pwevention system mangwing the video
	signaw to confuse video wecowdews. When this fwag is set
	Macwovision has been detected.
    * - ``V4W2_IN_ST_NO_ACCESS``
      - 0x02000000
      - Conditionaw access denied.
    * - ``V4W2_IN_ST_VTW``
      - 0x04000000
      - VTW time constant. [?]


.. tabuwawcowumns:: |p{6.6cm}|p{2.4cm}|p{8.3cm}|

.. _input-capabiwities:

.. fwat-tabwe:: Input capabiwities
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_IN_CAP_DV_TIMINGS``
      - 0x00000002
      - This input suppowts setting video timings by using
	``VIDIOC_S_DV_TIMINGS``.
    * - ``V4W2_IN_CAP_STD``
      - 0x00000004
      - This input suppowts setting the TV standawd by using
	``VIDIOC_S_STD``.
    * - ``V4W2_IN_CAP_NATIVE_SIZE``
      - 0x00000008
      - This input suppowts setting the native size using the
	``V4W2_SEW_TGT_NATIVE_SIZE`` sewection tawget, see
	:wef:`v4w2-sewections-common`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_input` ``index`` is out of
    bounds.
