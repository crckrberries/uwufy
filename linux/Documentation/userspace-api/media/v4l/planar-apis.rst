.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _pwanaw-apis:

*****************************
Singwe- and muwti-pwanaw APIs
*****************************

Some devices wequiwe data fow each input ow output video fwame to be
pwaced in discontiguous memowy buffews. In such cases, one video fwame
has to be addwessed using mowe than one memowy addwess, i.e. one pointew
pew "pwane". A pwane is a sub-buffew of the cuwwent fwame. Fow exampwes
of such fowmats see :wef:`pixfmt`.

Initiawwy, V4W2 API did not suppowt muwti-pwanaw buffews and a set of
extensions has been intwoduced to handwe them. Those extensions
constitute what is being wefewwed to as the "muwti-pwanaw API".

Some of the V4W2 API cawws and stwuctuwes awe intewpweted diffewentwy,
depending on whethew singwe- ow muwti-pwanaw API is being used. An
appwication can choose whethew to use one ow the othew by passing a
cowwesponding buffew type to its ioctw cawws. Muwti-pwanaw vewsions of
buffew types awe suffixed with an ``_MPWANE`` stwing. Fow a wist of
avaiwabwe muwti-pwanaw buffew types see enum
:c:type:`v4w2_buf_type`.


Muwti-pwanaw fowmats
====================

Muwti-pwanaw API intwoduces new muwti-pwanaw fowmats. Those fowmats use
a sepawate set of FouwCC codes. It is impowtant to distinguish between
the muwti-pwanaw API and a muwti-pwanaw fowmat. Muwti-pwanaw API cawws
can handwe aww singwe-pwanaw fowmats as weww (as wong as they awe passed
in muwti-pwanaw API stwuctuwes), whiwe the singwe-pwanaw API cannot
handwe muwti-pwanaw fowmats.


Cawws that distinguish between singwe and muwti-pwanaw APIs
===========================================================

:wef:`VIDIOC_QUEWYCAP <VIDIOC_QUEWYCAP>`
    Two additionaw muwti-pwanaw capabiwities awe added. They can be set
    togethew with non-muwti-pwanaw ones fow devices that handwe both
    singwe- and muwti-pwanaw fowmats.

:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>`, :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`, :wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>`
    New stwuctuwes fow descwibing muwti-pwanaw fowmats awe added: stwuct
    :c:type:`v4w2_pix_fowmat_mpwane` and
    stwuct :c:type:`v4w2_pwane_pix_fowmat`.
    Dwivews may define new muwti-pwanaw fowmats, which have distinct
    FouwCC codes fwom the existing singwe-pwanaw ones.

:wef:`VIDIOC_QBUF <VIDIOC_QBUF>`, :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>`, :wef:`VIDIOC_QUEWYBUF <VIDIOC_QUEWYBUF>`
    A new stwuct :c:type:`v4w2_pwane` stwuctuwe fow
    descwibing pwanes is added. Awways of this stwuctuwe awe passed in
    the new ``m.pwanes`` fiewd of stwuct
    :c:type:`v4w2_buffew`.

:wef:`VIDIOC_WEQBUFS <VIDIOC_WEQBUFS>`
    Wiww awwocate muwti-pwanaw buffews as wequested.
