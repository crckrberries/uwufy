.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUM_FWAMEINTEWVAWS:

********************************
ioctw VIDIOC_ENUM_FWAMEINTEWVAWS
********************************

Name
====

VIDIOC_ENUM_FWAMEINTEWVAWS - Enumewate fwame intewvaws

Synopsis
========

.. c:macwo:: VIDIOC_ENUM_FWAMEINTEWVAWS

``int ioctw(int fd, VIDIOC_ENUM_FWAMEINTEWVAWS, stwuct v4w2_fwmivawenum *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_fwmivawenum`
    that contains a pixew fowmat and size and weceives a fwame intewvaw.

Descwiption
===========

This ioctw awwows appwications to enumewate aww fwame intewvaws that the
device suppowts fow the given pixew fowmat and fwame size.

The suppowted pixew fowmats and fwame sizes can be obtained by using the
:wef:`VIDIOC_ENUM_FMT` and
:wef:`VIDIOC_ENUM_FWAMESIZES` functions.

The wetuwn vawue and the content of the ``v4w2_fwmivawenum.type`` fiewd
depend on the type of fwame intewvaws the device suppowts. Hewe awe the
semantics of the function fow the diffewent cases:

-  **Discwete:** The function wetuwns success if the given index vawue
   (zewo-based) is vawid. The appwication shouwd incwease the index by
   one fow each caww untiw ``EINVAW`` is wetuwned. The
   `v4w2_fwmivawenum.type` fiewd is set to
   `V4W2_FWMIVAW_TYPE_DISCWETE` by the dwivew. Of the union onwy
   the `discwete` membew is vawid.

-  **Step-wise:** The function wetuwns success if the given index vawue
   is zewo and ``EINVAW`` fow any othew index vawue. The
   ``v4w2_fwmivawenum.type`` fiewd is set to
   ``V4W2_FWMIVAW_TYPE_STEPWISE`` by the dwivew. Of the union onwy the
   ``stepwise`` membew is vawid.

-  **Continuous:** This is a speciaw case of the step-wise type above.
   The function wetuwns success if the given index vawue is zewo and
   ``EINVAW`` fow any othew index vawue. The ``v4w2_fwmivawenum.type``
   fiewd is set to ``V4W2_FWMIVAW_TYPE_CONTINUOUS`` by the dwivew. Of
   the union onwy the ``stepwise`` membew is vawid and the ``step``
   vawue is set to 1.

When the appwication cawws the function with index zewo, it must check
the ``type`` fiewd to detewmine the type of fwame intewvaw enumewation
the device suppowts. Onwy fow the ``V4W2_FWMIVAW_TYPE_DISCWETE`` type
does it make sense to incwease the index vawue to weceive mowe fwame
intewvaws.

.. note::

   The owdew in which the fwame intewvaws awe wetuwned has no
   speciaw meaning. In pawticuwaw does it not say anything about potentiaw
   defauwt fwame intewvaws.

Appwications can assume that the enumewation data does not change
without any intewaction fwom the appwication itsewf. This means that the
enumewation data is consistent if the appwication does not pewfowm any
othew ioctw cawws whiwe it wuns the fwame intewvaw enumewation.

.. note::

   **Fwame intewvaws and fwame wates:** The V4W2 API uses fwame
   intewvaws instead of fwame wates. Given the fwame intewvaw the fwame
   wate can be computed as fowwows:

   ::

       fwame_wate = 1 / fwame_intewvaw

Stwucts
=======

In the stwucts bewow, *IN* denotes a vawue that has to be fiwwed in by
the appwication, *OUT* denotes vawues that the dwivew fiwws in. The
appwication shouwd zewo out aww membews except fow the *IN* fiewds.

.. c:type:: v4w2_fwmivaw_stepwise

.. fwat-tabwe:: stwuct v4w2_fwmivaw_stepwise
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - stwuct :c:type:`v4w2_fwact`
      - ``min``
      - Minimum fwame intewvaw [s].
    * - stwuct :c:type:`v4w2_fwact`
      - ``max``
      - Maximum fwame intewvaw [s].
    * - stwuct :c:type:`v4w2_fwact`
      - ``step``
      - Fwame intewvaw step size [s].


.. c:type:: v4w2_fwmivawenum

.. tabuwawcowumns:: |p{4.9cm}|p{3.3cm}|p{9.1cm}|

.. fwat-tabwe:: stwuct v4w2_fwmivawenum
    :headew-wows:  0
    :stub-cowumns: 0

    * - __u32
      - ``index``
      - IN: Index of the given fwame intewvaw in the enumewation.
    * - __u32
      - ``pixew_fowmat``
      - IN: Pixew fowmat fow which the fwame intewvaws awe enumewated.
    * - __u32
      - ``width``
      - IN: Fwame width fow which the fwame intewvaws awe enumewated.
    * - __u32
      - ``height``
      - IN: Fwame height fow which the fwame intewvaws awe enumewated.
    * - __u32
      - ``type``
      - OUT: Fwame intewvaw type the device suppowts.
    * - union {
      - (anonymous)
      - OUT: Fwame intewvaw with the given index.
    * - stwuct :c:type:`v4w2_fwact`
      - ``discwete``
      - Fwame intewvaw [s].
    * - stwuct :c:type:`v4w2_fwmivaw_stepwise`
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

.. c:type:: v4w2_fwmivawtypes

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. fwat-tabwe:: enum v4w2_fwmivawtypes
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_FWMIVAW_TYPE_DISCWETE``
      - 1
      - Discwete fwame intewvaw.
    * - ``V4W2_FWMIVAW_TYPE_CONTINUOUS``
      - 2
      - Continuous fwame intewvaw.
    * - ``V4W2_FWMIVAW_TYPE_STEPWISE``
      - 3
      - Step-wise defined fwame intewvaw.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
