.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_INPUT:

************************************
ioctw VIDIOC_G_INPUT, VIDIOC_S_INPUT
************************************

Name
====

VIDIOC_G_INPUT - VIDIOC_S_INPUT - Quewy ow sewect the cuwwent video input

Synopsis
========

.. c:macwo:: VIDIOC_G_INPUT

``int ioctw(int fd, VIDIOC_G_INPUT, int *awgp)``

.. c:macwo:: VIDIOC_S_INPUT

``int ioctw(int fd, VIDIOC_S_INPUT, int *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew an integew with input index.

Descwiption
===========

To quewy the cuwwent video input appwications caww the
:wef:`VIDIOC_G_INPUT <VIDIOC_G_INPUT>` ioctw with a pointew to an integew whewe the dwivew
stowes the numbew of the input, as in the stwuct
:c:type:`v4w2_input` ``index`` fiewd. This ioctw wiww faiw
onwy when thewe awe no video inputs, wetuwning ``EINVAW``.

To sewect a video input appwications stowe the numbew of the desiwed
input in an integew and caww the :wef:`VIDIOC_S_INPUT <VIDIOC_G_INPUT>` ioctw with a pointew
to this integew. Side effects awe possibwe. Fow exampwe inputs may
suppowt diffewent video standawds, so the dwivew may impwicitwy switch
the cuwwent standawd. Because of these possibwe side effects
appwications must sewect an input befowe quewying ow negotiating any
othew pawametews.

Infowmation about video inputs is avaiwabwe using the
:wef:`VIDIOC_ENUMINPUT` ioctw.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The numbew of the video input is out of bounds.
