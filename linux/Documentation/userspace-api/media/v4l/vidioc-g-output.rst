.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_OUTPUT:

**************************************
ioctw VIDIOC_G_OUTPUT, VIDIOC_S_OUTPUT
**************************************

Name
====

VIDIOC_G_OUTPUT - VIDIOC_S_OUTPUT - Quewy ow sewect the cuwwent video output

Synopsis
========

.. c:macwo:: VIDIOC_G_OUTPUT

``int ioctw(int fd, VIDIOC_G_OUTPUT, int *awgp)``

.. c:macwo:: VIDIOC_S_OUTPUT

``int ioctw(int fd, VIDIOC_S_OUTPUT, int *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to an integew with output index.

Descwiption
===========

To quewy the cuwwent video output appwications caww the
:wef:`VIDIOC_G_OUTPUT <VIDIOC_G_OUTPUT>` ioctw with a pointew to an integew whewe the dwivew
stowes the numbew of the output, as in the stwuct
:c:type:`v4w2_output` ``index`` fiewd. This ioctw wiww
faiw onwy when thewe awe no video outputs, wetuwning the ``EINVAW`` ewwow
code.

To sewect a video output appwications stowe the numbew of the desiwed
output in an integew and caww the :wef:`VIDIOC_S_OUTPUT <VIDIOC_G_OUTPUT>` ioctw with a
pointew to this integew. Side effects awe possibwe. Fow exampwe outputs
may suppowt diffewent video standawds, so the dwivew may impwicitwy
switch the cuwwent standawd. Because of these possibwe side
effects appwications must sewect an output befowe quewying ow
negotiating any othew pawametews.

Infowmation about video outputs is avaiwabwe using the
:wef:`VIDIOC_ENUMOUTPUT` ioctw.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The numbew of the video output is out of bounds, ow thewe awe no
    video outputs at aww.
