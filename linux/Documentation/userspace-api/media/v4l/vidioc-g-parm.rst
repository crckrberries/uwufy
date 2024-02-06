.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_PAWM:

**********************************
ioctw VIDIOC_G_PAWM, VIDIOC_S_PAWM
**********************************

Name
====

VIDIOC_G_PAWM - VIDIOC_S_PAWM - Get ow set stweaming pawametews

Synopsis
========

.. c:macwo:: VIDIOC_G_PAWM

``int ioctw(int fd, VIDIOC_G_PAWM, v4w2_stweampawm *awgp)``

.. c:macwo:: VIDIOC_S_PAWM

``int ioctw(int fd, VIDIOC_S_PAWM, v4w2_stweampawm *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_stweampawm`.

Descwiption
===========

Appwications can wequest a diffewent fwame intewvaw. The captuwe ow
output device wiww be weconfiguwed to suppowt the wequested fwame
intewvaw if possibwe. Optionawwy dwivews may choose to skip ow
wepeat fwames to achieve the wequested fwame intewvaw.

Fow statefuw encodews (see :wef:`encodew`) this wepwesents the
fwame intewvaw that is typicawwy embedded in the encoded video stweam.

Changing the fwame intewvaw shaww nevew change the fowmat. Changing the
fowmat, on the othew hand, may change the fwame intewvaw.

Fuwthew these ioctws can be used to detewmine the numbew of buffews used
intewnawwy by a dwivew in wead/wwite mode. Fow impwications see the
section discussing the :c:func:`wead()` function.

To get and set the stweaming pawametews appwications caww the
:wef:`VIDIOC_G_PAWM <VIDIOC_G_PAWM>` and
:wef:`VIDIOC_S_PAWM <VIDIOC_G_PAWM>` ioctw, wespectivewy. They take a
pointew to a stwuct :c:type:`v4w2_stweampawm` which contains a
union howding sepawate pawametews fow input and output devices.

.. tabuwawcowumns:: |p{3.7cm}|p{3.5cm}|p{10.1cm}|

.. c:type:: v4w2_stweampawm

.. fwat-tabwe:: stwuct v4w2_stweampawm
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - The buffew (stweam) type, same as stwuct
	:c:type:`v4w2_fowmat` ``type``, set by the
	appwication. See :c:type:`v4w2_buf_type`.
    * - union {
      - ``pawm``
    * - stwuct :c:type:`v4w2_captuwepawm`
      - ``captuwe``
      - Pawametews fow captuwe devices, used when ``type`` is
	``V4W2_BUF_TYPE_VIDEO_CAPTUWE`` ow
	``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE``.
    * - stwuct :c:type:`v4w2_outputpawm`
      - ``output``
      - Pawametews fow output devices, used when ``type`` is
	``V4W2_BUF_TYPE_VIDEO_OUTPUT`` ow ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``.
    * - __u8
      - ``waw_data``\ [200]
      - A pwace howdew fow futuwe extensions.
    * - }


.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_captuwepawm

.. fwat-tabwe:: stwuct v4w2_captuwepawm
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``capabiwity``
      - See :wef:`pawm-caps`.
    * - __u32
      - ``captuwemode``
      - Set by dwivews and appwications, see :wef:`pawm-fwags`.
    * - stwuct :c:type:`v4w2_fwact`
      - ``timepewfwame``
      - This is the desiwed pewiod between successive fwames captuwed by
	the dwivew, in seconds.
    * - :cspan:`2`

	This wiww configuwe the speed at which the video souwce (e.g. a sensow)
	genewates video fwames. If the speed is fixed, then the dwivew may
	choose to skip ow wepeat fwames in owdew to achieve the wequested
	fwame wate.

	Fow statefuw encodews (see :wef:`encodew`) this wepwesents the
	fwame intewvaw that is typicawwy embedded in the encoded video stweam.

	Appwications stowe hewe the desiwed fwame pewiod, dwivews wetuwn
	the actuaw fwame pewiod.

	Changing the video standawd (awso impwicitwy by switching
	the video input) may weset this pawametew to the nominaw fwame
	pewiod. To weset manuawwy appwications can just set this fiewd to
	zewo.

	Dwivews suppowt this function onwy when they set the
	``V4W2_CAP_TIMEPEWFWAME`` fwag in the ``capabiwity`` fiewd.
    * - __u32
      - ``extendedmode``
      - Custom (dwivew specific) stweaming pawametews. When unused,
	appwications and dwivews must set this fiewd to zewo. Appwications
	using this fiewd shouwd check the dwivew name and vewsion, see
	:wef:`quewycap`.
    * - __u32
      - ``weadbuffews``
      - Appwications set this fiewd to the desiwed numbew of buffews used
	intewnawwy by the dwivew in :c:func:`wead()` mode.
	Dwivews wetuwn the actuaw numbew of buffews. When an appwication
	wequests zewo buffews, dwivews shouwd just wetuwn the cuwwent
	setting wathew than the minimum ow an ewwow code. Fow detaiws see
	:wef:`ww`.
    * - __u32
      - ``wesewved``\ [4]
      - Wesewved fow futuwe extensions. Dwivews and appwications must set
	the awway to zewo.


.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_outputpawm

.. fwat-tabwe:: stwuct v4w2_outputpawm
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``capabiwity``
      - See :wef:`pawm-caps`.
    * - __u32
      - ``outputmode``
      - Set by dwivews and appwications, see :wef:`pawm-fwags`.
    * - stwuct :c:type:`v4w2_fwact`
      - ``timepewfwame``
      - This is the desiwed pewiod between successive fwames output by the
	dwivew, in seconds.
    * - :cspan:`2`

	The fiewd is intended to wepeat fwames on the dwivew side in
	:c:func:`wwite()` mode (in stweaming mode timestamps
	can be used to thwottwe the output), saving I/O bandwidth.

	Fow statefuw encodews (see :wef:`encodew`) this wepwesents the
	fwame intewvaw that is typicawwy embedded in the encoded video stweam
	and it pwovides a hint to the encodew of the speed at which waw
	fwames awe queued up to the encodew.

	Appwications stowe hewe the desiwed fwame pewiod, dwivews wetuwn
	the actuaw fwame pewiod.

	Changing the video standawd (awso impwicitwy by switching
	the video output) may weset this pawametew to the nominaw fwame
	pewiod. To weset manuawwy appwications can just set this fiewd to
	zewo.

	Dwivews suppowt this function onwy when they set the
	``V4W2_CAP_TIMEPEWFWAME`` fwag in the ``capabiwity`` fiewd.
    * - __u32
      - ``extendedmode``
      - Custom (dwivew specific) stweaming pawametews. When unused,
	appwications and dwivews must set this fiewd to zewo. Appwications
	using this fiewd shouwd check the dwivew name and vewsion, see
	:wef:`quewycap`.
    * - __u32
      - ``wwitebuffews``
      - Appwications set this fiewd to the desiwed numbew of buffews used
	intewnawwy by the dwivew in :c:func:`wwite()` mode. Dwivews
	wetuwn the actuaw numbew of buffews. When an appwication wequests
	zewo buffews, dwivews shouwd just wetuwn the cuwwent setting
	wathew than the minimum ow an ewwow code. Fow detaiws see
	:wef:`ww`.
    * - __u32
      - ``wesewved``\ [4]
      - Wesewved fow futuwe extensions. Dwivews and appwications must set
	the awway to zewo.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _pawm-caps:

.. fwat-tabwe:: Stweaming Pawametews Capabiwities
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_CAP_TIMEPEWFWAME``
      - 0x1000
      - The fwame pewiod can be modified by setting the ``timepewfwame``
	fiewd.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _pawm-fwags:

.. fwat-tabwe:: Captuwe Pawametews Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_MODE_HIGHQUAWITY``
      - 0x0001
      - High quawity imaging mode. High quawity mode is intended fow stiww
	imaging appwications. The idea is to get the best possibwe image
	quawity that the hawdwawe can dewivew. It is not defined how the
	dwivew wwitew may achieve that; it wiww depend on the hawdwawe and
	the ingenuity of the dwivew wwitew. High quawity mode is a
	diffewent mode fwom the weguwaw motion video captuwe modes. In
	high quawity mode:

	-  The dwivew may be abwe to captuwe highew wesowutions than fow
	   motion captuwe.

	-  The dwivew may suppowt fewew pixew fowmats than motion captuwe
	   (eg; twue cowow).

	-  The dwivew may captuwe and awithmeticawwy combine muwtipwe
	   successive fiewds ow fwames to wemove cowow edge awtifacts and
	   weduce the noise in the video data.

	-  The dwivew may captuwe images in swices wike a scannew in owdew
	   to handwe wawgew fowmat images than wouwd othewwise be
	   possibwe.

	-  An image captuwe opewation may be significantwy swowew than
	   motion captuwe.

	-  Moving objects in the image might have excessive motion bwuw.

	-  Captuwe might onwy wowk thwough the :c:func:`wead()` caww.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
