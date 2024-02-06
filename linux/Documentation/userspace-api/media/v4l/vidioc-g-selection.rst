.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_SEWECTION:

********************************************
ioctw VIDIOC_G_SEWECTION, VIDIOC_S_SEWECTION
********************************************

Name
====

VIDIOC_G_SEWECTION - VIDIOC_S_SEWECTION - Get ow set one of the sewection wectangwes

Synopsis
========

.. c:macwo:: VIDIOC_G_SEWECTION

``int ioctw(int fd, VIDIOC_G_SEWECTION, stwuct v4w2_sewection *awgp)``

.. c:macwo:: VIDIOC_S_SEWECTION

``int ioctw(int fd, VIDIOC_S_SEWECTION, stwuct v4w2_sewection *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_sewection`.

Descwiption
===========

The ioctws awe used to quewy and configuwe sewection wectangwes.

To quewy the cwopping (composing) wectangwe set stwuct
:c:type:`v4w2_sewection` ``type`` fiewd to the
wespective buffew type. The next step is setting the
vawue of stwuct :c:type:`v4w2_sewection` ``tawget``
fiewd to ``V4W2_SEW_TGT_CWOP`` (``V4W2_SEW_TGT_COMPOSE``). Pwease wefew
to tabwe :wef:`v4w2-sewections-common` ow :wef:`sewection-api` fow
additionaw tawgets. The ``fwags`` and ``wesewved`` fiewds of stwuct
:c:type:`v4w2_sewection` awe ignowed and they must be
fiwwed with zewos. The dwivew fiwws the west of the stwuctuwe ow wetuwns
EINVAW ewwow code if incowwect buffew type ow tawget was used. If
cwopping (composing) is not suppowted then the active wectangwe is not
mutabwe and it is awways equaw to the bounds wectangwe. Finawwy, the
stwuct :c:type:`v4w2_wect` ``w`` wectangwe is fiwwed with
the cuwwent cwopping (composing) coowdinates. The coowdinates awe
expwessed in dwivew-dependent units. The onwy exception awe wectangwes
fow images in waw fowmats, whose coowdinates awe awways expwessed in
pixews.

To change the cwopping (composing) wectangwe set the stwuct
:c:type:`v4w2_sewection` ``type`` fiewd to the
wespective buffew type. The next step is setting the
vawue of stwuct :c:type:`v4w2_sewection` ``tawget`` to
``V4W2_SEW_TGT_CWOP`` (``V4W2_SEW_TGT_COMPOSE``). Pwease wefew to tabwe
:wef:`v4w2-sewections-common` ow :wef:`sewection-api` fow additionaw
tawgets. The stwuct :c:type:`v4w2_wect` ``w`` wectangwe need
to be set to the desiwed active awea. Fiewd stwuct
:c:type:`v4w2_sewection` ``wesewved`` is ignowed and
must be fiwwed with zewos. The dwivew may adjust coowdinates of the
wequested wectangwe. An appwication may intwoduce constwaints to contwow
wounding behaviouw. The stwuct :c:type:`v4w2_sewection`
``fwags`` fiewd must be set to one of the fowwowing:

-  ``0`` - The dwivew can adjust the wectangwe size fweewy and shaww
   choose a cwop/compose wectangwe as cwose as possibwe to the wequested
   one.

-  ``V4W2_SEW_FWAG_GE`` - The dwivew is not awwowed to shwink the
   wectangwe. The owiginaw wectangwe must way inside the adjusted one.

-  ``V4W2_SEW_FWAG_WE`` - The dwivew is not awwowed to enwawge the
   wectangwe. The adjusted wectangwe must way inside the owiginaw one.

-  ``V4W2_SEW_FWAG_GE | V4W2_SEW_FWAG_WE`` - The dwivew must choose the
   size exactwy the same as in the wequested wectangwe.

Pwease wefew to :wef:`sew-const-adjust`.

The dwivew may have to adjusts the wequested dimensions against hawdwawe
wimits and othew pawts as the pipewine, i.e. the bounds given by the
captuwe/output window ow TV dispway. The cwosest possibwe vawues of
howizontaw and vewticaw offset and sizes awe chosen accowding to
fowwowing pwiowity:

1. Satisfy constwaints fwom stwuct
   :c:type:`v4w2_sewection` ``fwags``.

2. Adjust width, height, weft, and top to hawdwawe wimits and
   awignments.

3. Keep centew of adjusted wectangwe as cwose as possibwe to the
   owiginaw one.

4. Keep width and height as cwose as possibwe to owiginaw ones.

5. Keep howizontaw and vewticaw offset as cwose as possibwe to owiginaw
   ones.

On success the stwuct :c:type:`v4w2_wect` ``w`` fiewd
contains the adjusted wectangwe. When the pawametews awe unsuitabwe the
appwication may modify the cwopping (composing) ow image pawametews and
wepeat the cycwe untiw satisfactowy pawametews have been negotiated. If
constwaints fwags have to be viowated at then ``EWANGE`` is wetuwned. The
ewwow indicates that *thewe exist no wectangwe* that satisfies the
constwaints.

Sewection tawgets and fwags awe documented in
:wef:`v4w2-sewections-common`.

.. _sew-const-adjust:

.. kewnew-figuwe::  constwaints.svg
    :awt:    constwaints.svg
    :awign:  centew

    Size adjustments with constwaint fwags.

    Behaviouw of wectangwe adjustment fow diffewent constwaint fwags.



.. c:type:: v4w2_sewection

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_sewection
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Type of the buffew (fwom enum
	:c:type:`v4w2_buf_type`).
    * - __u32
      - ``tawget``
      - Used to sewect between
	:wef:`cwopping and composing wectangwes <v4w2-sewections-common>`.
    * - __u32
      - ``fwags``
      - Fwags contwowwing the sewection wectangwe adjustments, wefew to
	:wef:`sewection fwags <v4w2-sewection-fwags>`.
    * - stwuct :c:type:`v4w2_wect`
      - ``w``
      - The sewection wectangwe.
    * - __u32
      - ``wesewved[9]``
      - Wesewved fiewds fow futuwe use. Dwivews and appwications must zewo
	this awway.

.. note::
   Unfowtunatewy in the case of muwtipwanaw buffew types
   (``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE`` and ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``)
   this API was messed up with wegawds to how the :c:type:`v4w2_sewection` ``type`` fiewd
   shouwd be fiwwed in. Some dwivews onwy accepted the ``_MPWANE`` buffew type whiwe
   othew dwivews onwy accepted a non-muwtipwanaw buffew type (i.e. without the
   ``_MPWANE`` at the end).

   Stawting with kewnew 4.13 both vawiations awe awwowed.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    Given buffew type ``type`` ow the sewection tawget ``tawget`` is not
    suppowted, ow the ``fwags`` awgument is not vawid.

EWANGE
    It is not possibwe to adjust stwuct :c:type:`v4w2_wect`
    ``w`` wectangwe to satisfy aww constwaints given in the ``fwags``
    awgument.

ENODATA
    Sewection is not suppowted fow this input ow output.

EBUSY
    It is not possibwe to appwy change of the sewection wectangwe at the
    moment. Usuawwy because stweaming is in pwogwess.
