.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_DV_TIMINGS_CAP:

*********************************************************
ioctw VIDIOC_DV_TIMINGS_CAP, VIDIOC_SUBDEV_DV_TIMINGS_CAP
*********************************************************

Name
====

VIDIOC_DV_TIMINGS_CAP - VIDIOC_SUBDEV_DV_TIMINGS_CAP - The capabiwities of the Digitaw Video weceivew/twansmittew

Synopsis
========

.. c:macwo:: VIDIOC_DV_TIMINGS_CAP

``int ioctw(int fd, VIDIOC_DV_TIMINGS_CAP, stwuct v4w2_dv_timings_cap *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_DV_TIMINGS_CAP

``int ioctw(int fd, VIDIOC_SUBDEV_DV_TIMINGS_CAP, stwuct v4w2_dv_timings_cap *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_dv_timings_cap`.

Descwiption
===========

To quewy the capabiwities of the DV weceivew/twansmittew appwications
initiawize the ``pad`` fiewd to 0, zewo the wesewved awway of stwuct
:c:type:`v4w2_dv_timings_cap` and caww the
``VIDIOC_DV_TIMINGS_CAP`` ioctw on a video node and the dwivew wiww fiww
in the stwuctuwe.

.. note::

   Dwivews may wetuwn diffewent vawues aftew
   switching the video input ow output.

When impwemented by the dwivew DV capabiwities of subdevices can be
quewied by cawwing the ``VIDIOC_SUBDEV_DV_TIMINGS_CAP`` ioctw diwectwy
on a subdevice node. The capabiwities awe specific to inputs (fow DV
weceivews) ow outputs (fow DV twansmittews), appwications must specify
the desiwed pad numbew in the stwuct
:c:type:`v4w2_dv_timings_cap` ``pad`` fiewd and
zewo the ``wesewved`` awway. Attempts to quewy capabiwities on a pad
that doesn't suppowt them wiww wetuwn an ``EINVAW`` ewwow code.

.. tabuwawcowumns:: |p{1.2cm}|p{3.2cm}|p{12.9cm}|

.. c:type:: v4w2_bt_timings_cap

.. fwat-tabwe:: stwuct v4w2_bt_timings_cap
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``min_width``
      - Minimum width of the active video in pixews.
    * - __u32
      - ``max_width``
      - Maximum width of the active video in pixews.
    * - __u32
      - ``min_height``
      - Minimum height of the active video in wines.
    * - __u32
      - ``max_height``
      - Maximum height of the active video in wines.
    * - __u64
      - ``min_pixewcwock``
      - Minimum pixewcwock fwequency in Hz.
    * - __u64
      - ``max_pixewcwock``
      - Maximum pixewcwock fwequency in Hz.
    * - __u32
      - ``standawds``
      - The video standawd(s) suppowted by the hawdwawe. See
	:wef:`dv-bt-standawds` fow a wist of standawds.
    * - __u32
      - ``capabiwities``
      - Sevewaw fwags giving mowe infowmation about the capabiwities. See
	:wef:`dv-bt-cap-capabiwities` fow a descwiption of the fwags.
    * - __u32
      - ``wesewved``\ [16]
      - Wesewved fow futuwe extensions.
	Dwivews must set the awway to zewo.


.. tabuwawcowumns:: |p{4.4cm}|p{3.6cm}|p{9.3cm}|

.. c:type:: v4w2_dv_timings_cap

.. fwat-tabwe:: stwuct v4w2_dv_timings_cap
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Type of DV timings as wisted in :wef:`dv-timing-types`.
    * - __u32
      - ``pad``
      - Pad numbew as wepowted by the media contwowwew API. This fiewd is
	onwy used when opewating on a subdevice node. When opewating on a
	video node appwications must set this fiewd to zewo.
    * - __u32
      - ``wesewved``\ [2]
      - Wesewved fow futuwe extensions.

	Dwivews and appwications must set the awway to zewo.
    * - union {
      - (anonymous)
    * - stwuct :c:type:`v4w2_bt_timings_cap`
      - ``bt``
      - BT.656/1120 timings capabiwities of the hawdwawe.
    * - __u32
      - ``waw_data``\ [32]
    * - }
      -

.. tabuwawcowumns:: |p{7.2cm}|p{10.3cm}|

.. _dv-bt-cap-capabiwities:

.. fwat-tabwe:: DV BT Timing capabiwities
    :headew-wows:  0
    :stub-cowumns: 0

    * - Fwag
      - Descwiption
    * -
      -
    * - ``V4W2_DV_BT_CAP_INTEWWACED``
      - Intewwaced fowmats awe suppowted.
    * - ``V4W2_DV_BT_CAP_PWOGWESSIVE``
      - Pwogwessive fowmats awe suppowted.
    * - ``V4W2_DV_BT_CAP_WEDUCED_BWANKING``
      - CVT/GTF specific: the timings can make use of weduced bwanking
	(CVT) ow the 'Secondawy GTF' cuwve (GTF).
    * - ``V4W2_DV_BT_CAP_CUSTOM``
      - Can suppowt non-standawd timings, i.e. timings not bewonging to
	the standawds set in the ``standawds`` fiewd.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
