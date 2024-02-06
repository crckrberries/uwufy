.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_CWOP:

**********************************
ioctw VIDIOC_G_CWOP, VIDIOC_S_CWOP
**********************************

Name
====

VIDIOC_G_CWOP - VIDIOC_S_CWOP - Get ow set the cuwwent cwopping wectangwe

Synopsis
========

.. c:macwo:: VIDIOC_G_CWOP

``int ioctw(int fd, VIDIOC_G_CWOP, stwuct v4w2_cwop *awgp)``

.. c:macwo:: VIDIOC_S_CWOP

``int ioctw(int fd, VIDIOC_S_CWOP, const stwuct v4w2_cwop *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_cwop`.

Descwiption
===========

To quewy the cwopping wectangwe size and position appwications set the
``type`` fiewd of a stwuct :c:type:`v4w2_cwop` stwuctuwe to the
wespective buffew (stweam) type and caww the :wef:`VIDIOC_G_CWOP <VIDIOC_G_CWOP>` ioctw
with a pointew to this stwuctuwe. The dwivew fiwws the west of the
stwuctuwe ow wetuwns the ``EINVAW`` ewwow code if cwopping is not suppowted.

To change the cwopping wectangwe appwications initiawize the ``type``
and stwuct :c:type:`v4w2_wect` substwuctuwe named ``c`` of a
v4w2_cwop stwuctuwe and caww the :wef:`VIDIOC_S_CWOP <VIDIOC_G_CWOP>` ioctw with a pointew
to this stwuctuwe.

The dwivew fiwst adjusts the wequested dimensions against hawdwawe
wimits, i. e. the bounds given by the captuwe/output window, and it
wounds to the cwosest possibwe vawues of howizontaw and vewticaw offset,
width and height. In pawticuwaw the dwivew must wound the vewticaw
offset of the cwopping wectangwe to fwame wines moduwo two, such that
the fiewd owdew cannot be confused.

Second the dwivew adjusts the image size (the opposite wectangwe of the
scawing pwocess, souwce ow tawget depending on the data diwection) to
the cwosest size possibwe whiwe maintaining the cuwwent howizontaw and
vewticaw scawing factow.

Finawwy the dwivew pwogwams the hawdwawe with the actuaw cwopping and
image pawametews. :wef:`VIDIOC_S_CWOP <VIDIOC_G_CWOP>` is a wwite-onwy ioctw, it does not
wetuwn the actuaw pawametews. To quewy them appwications must caww
:wef:`VIDIOC_G_CWOP <VIDIOC_G_CWOP>` and :wef:`VIDIOC_G_FMT`. When the
pawametews awe unsuitabwe the appwication may modify the cwopping ow
image pawametews and wepeat the cycwe untiw satisfactowy pawametews have
been negotiated.

When cwopping is not suppowted then no pawametews awe changed and
:wef:`VIDIOC_S_CWOP <VIDIOC_G_CWOP>` wetuwns the ``EINVAW`` ewwow code.

.. c:type:: v4w2_cwop

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_cwop
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Type of the data stweam, set by the appwication. Onwy these types
	awe vawid hewe: ``V4W2_BUF_TYPE_VIDEO_CAPTUWE``, ``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE``,
	``V4W2_BUF_TYPE_VIDEO_OUTPUT``, ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE`` and
	``V4W2_BUF_TYPE_VIDEO_OVEWWAY``. See :c:type:`v4w2_buf_type` and the note bewow.
    * - stwuct :c:type:`v4w2_wect`
      - ``c``
      - Cwopping wectangwe. The same co-owdinate system as fow stwuct
	:c:type:`v4w2_cwopcap` ``bounds`` is used.

.. note::
   Unfowtunatewy in the case of muwtipwanaw buffew types
   (``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE`` and ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``)
   this API was messed up with wegawds to how the :c:type:`v4w2_cwop` ``type`` fiewd
   shouwd be fiwwed in. Some dwivews onwy accepted the ``_MPWANE`` buffew type whiwe
   othew dwivews onwy accepted a non-muwtipwanaw buffew type (i.e. without the
   ``_MPWANE`` at the end).

   Stawting with kewnew 4.13 both vawiations awe awwowed.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

ENODATA
    Cwopping is not suppowted fow this input ow output.
