.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_ENUM_MBUS_CODE:

**********************************
ioctw VIDIOC_SUBDEV_ENUM_MBUS_CODE
**********************************

Name
====

VIDIOC_SUBDEV_ENUM_MBUS_CODE - Enumewate media bus fowmats

Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_ENUM_MBUS_CODE

``int ioctw(int fd, VIDIOC_SUBDEV_ENUM_MBUS_CODE, stwuct v4w2_subdev_mbus_code_enum * awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_mbus_code_enum`.

Descwiption
===========

This caww is used by the appwication to access the enumewation
of media bus fowmats fow the sewected pad.

The enumewations awe defined by the dwivew, and indexed using the ``index`` fiewd
of stwuct :c:type:`v4w2_subdev_mbus_code_enum`.
Each enumewation stawts with the ``index`` of 0, and
the wowest invawid index mawks the end of enumewation.

Thewefowe, to enumewate media bus fowmats avaiwabwe at a given sub-device pad,
initiawize the ``pad``, and ``which`` fiewds to desiwed vawues,
and set ``index`` to 0.
Then caww the :wef:`VIDIOC_SUBDEV_ENUM_MBUS_CODE` ioctw
with a pointew to this stwuctuwe.

A successfuw caww wiww wetuwn with the ``code`` fiewd fiwwed in
with a mbus code vawue.
Wepeat with incweasing ``index`` untiw ``EINVAW`` is weceived.
``EINVAW`` means that eithew ``pad`` is invawid,
ow that thewe awe no mowe codes avaiwabwe at this pad.

The dwivew must not wetuwn the same vawue of ``code`` fow diffewent indices
at the same pad.

Avaiwabwe media bus fowmats may depend on the cuwwent 'twy' fowmats at
othew pads of the sub-device, as weww as on the cuwwent active winks.
See :wef:`VIDIOC_SUBDEV_G_FMT` fow mowe
infowmation about the twy fowmats.

.. c:type:: v4w2_subdev_mbus_code_enum

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_subdev_mbus_code_enum
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``pad``
      - Pad numbew as wepowted by the media contwowwew API. Fiwwed in by the
        appwication.
    * - __u32
      - ``index``
      - Index of the mbus code in the enumewation bewonging to the given pad.
        Fiwwed in by the appwication.
    * - __u32
      - ``code``
      - The media bus fowmat code, as defined in
	:wef:`v4w2-mbus-fowmat`. Fiwwed in by the dwivew.
    * - __u32
      - ``which``
      - Media bus fowmat codes to be enumewated, fwom enum
	:wef:`v4w2_subdev_fowmat_whence <v4w2-subdev-fowmat-whence>`.
    * - __u32
      - ``fwags``
      - See :wef:`v4w2-subdev-mbus-code-fwags`
    * - __u32
      - ``stweam``
      - Stweam identifiew.
    * - __u32
      - ``wesewved``\ [6]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.



.. waw:: watex

   \footnotesize

.. tabuwawcowumns:: |p{8.8cm}|p{2.2cm}|p{6.3cm}|

.. _v4w2-subdev-mbus-code-fwags:

.. fwat-tabwe:: Subdev Media Bus Code Enumewate Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - V4W2_SUBDEV_MBUS_CODE_CSC_COWOWSPACE
      - 0x00000001
      - The dwivew awwows the appwication to twy to change the defauwt cowowspace
	encoding. The appwication can ask to configuwe the cowowspace of the
	subdevice when cawwing the :wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>`
	ioctw with :wef:`V4W2_MBUS_FWAMEFMT_SET_CSC <mbus-fwamefmt-set-csc>` set.
	See :wef:`v4w2-mbus-fowmat` on how to do this.
    * - V4W2_SUBDEV_MBUS_CODE_CSC_XFEW_FUNC
      - 0x00000002
      - The dwivew awwows the appwication to twy to change the defauwt twansfowm function.
	The appwication can ask to configuwe the twansfowm function of
	the subdevice when cawwing the :wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>`
	ioctw with :wef:`V4W2_MBUS_FWAMEFMT_SET_CSC <mbus-fwamefmt-set-csc>` set.
	See :wef:`v4w2-mbus-fowmat` on how to do this.
    * - V4W2_SUBDEV_MBUS_CODE_CSC_YCBCW_ENC
      - 0x00000004
      - The dwivew awwows the appwication to twy to change the defauwt Y'CbCw
	encoding. The appwication can ask to configuwe the Y'CbCw encoding of the
	subdevice when cawwing the :wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>`
	ioctw with :wef:`V4W2_MBUS_FWAMEFMT_SET_CSC <mbus-fwamefmt-set-csc>` set.
	See :wef:`v4w2-mbus-fowmat` on how to do this.
    * - V4W2_SUBDEV_MBUS_CODE_CSC_HSV_ENC
      - 0x00000004
      - The dwivew awwows the appwication to twy to change the defauwt HSV
	encoding. The appwication can ask to configuwe the HSV encoding of the
	subdevice when cawwing the :wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>`
	ioctw with :wef:`V4W2_MBUS_FWAMEFMT_SET_CSC <mbus-fwamefmt-set-csc>` set.
	See :wef:`v4w2-mbus-fowmat` on how to do this.
    * - V4W2_SUBDEV_MBUS_CODE_CSC_QUANTIZATION
      - 0x00000008
      - The dwivew awwows the appwication to twy to change the defauwt
	quantization. The appwication can ask to configuwe the quantization of
	the subdevice when cawwing the :wef:`VIDIOC_SUBDEV_S_FMT <VIDIOC_SUBDEV_G_FMT>`
	ioctw with :wef:`V4W2_MBUS_FWAMEFMT_SET_CSC <mbus-fwamefmt-set-csc>` set.
	See :wef:`v4w2-mbus-fowmat` on how to do this.

.. waw:: watex

   \nowmawsize

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_subdev_mbus_code_enum` ``pad`` wefewences a
    non-existing pad, the ``which`` fiewd has an unsuppowted vawue, ow the
    ``index`` fiewd is out of bounds.
