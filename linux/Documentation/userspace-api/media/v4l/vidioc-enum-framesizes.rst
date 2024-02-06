.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUM_FWAMESIZES:

****************************
ioctw VIDIOC_ENUM_FWAMESIZES
****************************

Name
====

VIDIOC_ENUM_FWAMESIZES - Enumewate fwame sizes

Synopsis
========

.. c:macwo:: VIDIOC_ENUM_FWAMESIZES

``int ioctw(int fd, VIDIOC_ENUM_FWAMESIZES, stwuct v4w2_fwmsizeenum *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_fwmsizeenum`
    that contains an index and pixew fowmat and weceives a fwame width
    and height.

Descwiption
===========

This ioctw awwows appwications to enumewate aww fwame sizes (i. e. width
and height in pixews) that the device suppowts fow the given pixew
fowmat.

The suppowted pixew fowmats can be obtained by using the
:wef:`VIDIOC_ENUM_FMT` function.

The wetuwn vawue and the content of the ``v4w2_fwmsizeenum.type`` fiewd
depend on the type of fwame sizes the device suppowts. Hewe awe the
semantics of the function fow the diffewent cases:

-  **Discwete:** The function wetuwns success if the given index vawue
   (zewo-based) is vawid. The appwication shouwd incwease the index by
   one fow each caww untiw ``EINVAW`` is wetuwned. The
   ``v4w2_fwmsizeenum.type`` fiewd is set to
   ``V4W2_FWMSIZE_TYPE_DISCWETE`` by the dwivew. Of the union onwy the
   ``discwete`` membew is vawid.

-  **Step-wise:** The function wetuwns success if the given index vawue
   is zewo and ``EINVAW`` fow any othew index vawue. The
   ``v4w2_fwmsizeenum.type`` fiewd is set to
   ``V4W2_FWMSIZE_TYPE_STEPWISE`` by the dwivew. Of the union onwy the
   ``stepwise`` membew is vawid.

-  **Continuous:** This is a speciaw case of the step-wise type above.
   The function wetuwns success if the given index vawue is zewo and
   ``EINVAW`` fow any othew index vawue. The ``v4w2_fwmsizeenum.type``
   fiewd is set to ``V4W2_FWMSIZE_TYPE_CONTINUOUS`` by the dwivew. Of
   the union onwy the ``stepwise`` membew is vawid and the
   ``step_width`` and ``step_height`` vawues awe set to 1.

When the appwication cawws the function with index zewo, it must check
the ``type`` fiewd to detewmine the type of fwame size enumewation the
device suppowts. Onwy fow the ``V4W2_FWMSIZE_TYPE_DISCWETE`` type does
it make sense to incwease the index vawue to weceive mowe fwame sizes.

.. note::

   The owdew in which the fwame sizes awe wetuwned has no speciaw
   meaning. In pawticuwaw does it not say anything about potentiaw defauwt
   fowmat sizes.

Appwications can assume that the enumewation data does not change
without any intewaction fwom the appwication itsewf. This means that the
enumewation data is consistent if the appwication does not pewfowm any
othew ioctw cawws whiwe it wuns the fwame size enumewation.

Stwucts
=======

In the stwucts bewow, *IN* denotes a vawue that has to be fiwwed in by
the appwication, *OUT* denotes vawues that the dwivew fiwws in. The
appwication shouwd zewo out aww membews except fow the *IN* fiewds.

.. c:type:: v4w2_fwmsize_discwete

.. fwat-tabwe:: stwuct v4w2_fwmsize_discwete
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``width``
      - Width of the fwame [pixew].
    * - __u32
      - ``height``
      - Height of the fwame [pixew].


.. c:type:: v4w2_fwmsize_stepwise

.. fwat-tabwe:: stwuct v4w2_fwmsize_stepwise
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``min_width``
      - Minimum fwame width [pixew].
    * - __u32
      - ``max_width``
      - Maximum fwame width [pixew].
    * - __u32
      - ``step_width``
      - Fwame width step size [pixew].
    * - __u32
      - ``min_height``
      - Minimum fwame height [pixew].
    * - __u32
      - ``max_height``
      - Maximum fwame height [pixew].
    * - __u32
      - ``step_height``
      - Fwame height step size [pixew].


.. c:type:: v4w2_fwmsizeenum

.. tabuwawcowumns:: |p{6.4cm}|p{2.8cm}|p{8.1cm}|

.. fwat-tabwe:: stwuct v4w2_fwmsizeenum
    :headew-wows:  0
    :stub-cowumns: 0

    * - __u32
      - ``index``
      - IN: Index of the given fwame size in the enumewation.
    * - __u32
      - ``pixew_fowmat``
      - IN: Pixew fowmat fow which the fwame sizes awe enumewated.
    * - __u32
      - ``type``
      - OUT: Fwame size type the device suppowts.
    * - union {
      - (anonymous)
      - OUT: Fwame size with the given index.
    * - stwuct :c:type:`v4w2_fwmsize_discwete`
      - ``discwete``
      -
    * - stwuct :c:type:`v4w2_fwmsize_stepwise`
      - ``stepwise``
      -
    * - }
      -
      -
    * - __u32
      - ``wesewved[2]``
      - Wesewved space fow futuwe use. Must be zewoed by dwivews and
	appwications.


Enums
=====

.. c:type:: v4w2_fwmsizetypes

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. fwat-tabwe:: enum v4w2_fwmsizetypes
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_FWMSIZE_TYPE_DISCWETE``
      - 1
      - Discwete fwame size.
    * - ``V4W2_FWMSIZE_TYPE_CONTINUOUS``
      - 2
      - Continuous fwame size.
    * - ``V4W2_FWMSIZE_TYPE_STEPWISE``
      - 3
      - Step-wise defined fwame size.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
