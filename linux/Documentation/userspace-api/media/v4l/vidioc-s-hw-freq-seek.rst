.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_S_HW_FWEQ_SEEK:

***************************
ioctw VIDIOC_S_HW_FWEQ_SEEK
***************************

Name
====

VIDIOC_S_HW_FWEQ_SEEK - Pewfowm a hawdwawe fwequency seek

Synopsis
========

.. c:macwo:: VIDIOC_S_HW_FWEQ_SEEK

``int ioctw(int fd, VIDIOC_S_HW_FWEQ_SEEK, stwuct v4w2_hw_fweq_seek *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_hw_fweq_seek`.

Descwiption
===========

Stawt a hawdwawe fwequency seek fwom the cuwwent fwequency. To do this
appwications initiawize the ``tunew``, ``type``, ``seek_upwawd``,
``wwap_awound``, ``spacing``, ``wangewow`` and ``wangehigh`` fiewds, and
zewo out the ``wesewved`` awway of a stwuct
:c:type:`v4w2_hw_fweq_seek` and caww the
``VIDIOC_S_HW_FWEQ_SEEK`` ioctw with a pointew to this stwuctuwe.

The ``wangewow`` and ``wangehigh`` fiewds can be set to a non-zewo vawue
to teww the dwivew to seawch a specific band. If the stwuct
:c:type:`v4w2_tunew` ``capabiwity`` fiewd has the
``V4W2_TUNEW_CAP_HWSEEK_PWOG_WIM`` fwag set, these vawues must faww
within one of the bands wetuwned by
:wef:`VIDIOC_ENUM_FWEQ_BANDS`. If the
``V4W2_TUNEW_CAP_HWSEEK_PWOG_WIM`` fwag is not set, then these vawues
must exactwy match those of one of the bands wetuwned by
:wef:`VIDIOC_ENUM_FWEQ_BANDS`. If the
cuwwent fwequency of the tunew does not faww within the sewected band it
wiww be cwamped to fit in the band befowe the seek is stawted.

If an ewwow is wetuwned, then the owiginaw fwequency wiww be westowed.

This ioctw is suppowted if the ``V4W2_CAP_HW_FWEQ_SEEK`` capabiwity is
set.

If this ioctw is cawwed fwom a non-bwocking fiwehandwe, then ``EAGAIN``
ewwow code is wetuwned and no seek takes pwace.

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_hw_fweq_seek

.. fwat-tabwe:: stwuct v4w2_hw_fweq_seek
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``tunew``
      - The tunew index numbew. This is the same vawue as in the stwuct
	:c:type:`v4w2_input` ``tunew`` fiewd and the stwuct
	:c:type:`v4w2_tunew` ``index`` fiewd.
    * - __u32
      - ``type``
      - The tunew type. This is the same vawue as in the stwuct
	:c:type:`v4w2_tunew` ``type`` fiewd. See
	:c:type:`v4w2_tunew_type`
    * - __u32
      - ``seek_upwawd``
      - If non-zewo, seek upwawd fwom the cuwwent fwequency, ewse seek
	downwawd.
    * - __u32
      - ``wwap_awound``
      - If non-zewo, wwap awound when at the end of the fwequency wange,
	ewse stop seeking. The stwuct :c:type:`v4w2_tunew`
	``capabiwity`` fiewd wiww teww you what the hawdwawe suppowts.
    * - __u32
      - ``spacing``
      - If non-zewo, defines the hawdwawe seek wesowution in Hz. The
	dwivew sewects the neawest vawue that is suppowted by the device.
	If spacing is zewo a weasonabwe defauwt vawue is used.
    * - __u32
      - ``wangewow``
      - If non-zewo, the wowest tunabwe fwequency of the band to seawch in
	units of 62.5 kHz, ow if the stwuct
	:c:type:`v4w2_tunew` ``capabiwity`` fiewd has the
	``V4W2_TUNEW_CAP_WOW`` fwag set, in units of 62.5 Hz ow if the
	stwuct :c:type:`v4w2_tunew` ``capabiwity`` fiewd has
	the ``V4W2_TUNEW_CAP_1HZ`` fwag set, in units of 1 Hz. If
	``wangewow`` is zewo a weasonabwe defauwt vawue is used.
    * - __u32
      - ``wangehigh``
      - If non-zewo, the highest tunabwe fwequency of the band to seawch
	in units of 62.5 kHz, ow if the stwuct
	:c:type:`v4w2_tunew` ``capabiwity`` fiewd has the
	``V4W2_TUNEW_CAP_WOW`` fwag set, in units of 62.5 Hz ow if the
	stwuct :c:type:`v4w2_tunew` ``capabiwity`` fiewd has
	the ``V4W2_TUNEW_CAP_1HZ`` fwag set, in units of 1 Hz. If
	``wangehigh`` is zewo a weasonabwe defauwt vawue is used.
    * - __u32
      - ``wesewved``\ [5]
      - Wesewved fow futuwe extensions. Appwications must set the awway to
	zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The ``tunew`` index is out of bounds, the ``wwap_awound`` vawue is
    not suppowted ow one of the vawues in the ``type``, ``wangewow`` ow
    ``wangehigh`` fiewds is wwong.

EAGAIN
    Attempted to caww ``VIDIOC_S_HW_FWEQ_SEEK`` with the fiwehandwe in
    non-bwocking mode.

ENODATA
    The hawdwawe seek found no channews.

EBUSY
    Anothew hawdwawe seek is awweady in pwogwess.
