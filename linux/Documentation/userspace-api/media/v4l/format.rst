.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _fowmat:

************
Data Fowmats
************

Data Fowmat Negotiation
=======================

Diffewent devices exchange diffewent kinds of data with appwications,
fow exampwe video images, waw ow swiced VBI data, WDS datagwams. Even
within one kind many diffewent fowmats awe possibwe, in pawticuwaw thewe is an
abundance of image fowmats. Awthough dwivews must pwovide a defauwt and
the sewection pewsists acwoss cwosing and weopening a device,
appwications shouwd awways negotiate a data fowmat befowe engaging in
data exchange. Negotiation means the appwication asks fow a pawticuwaw
fowmat and the dwivew sewects and wepowts the best the hawdwawe can do
to satisfy the wequest. Of couwse appwications can awso just quewy the
cuwwent sewection.

A singwe mechanism exists to negotiate aww data fowmats using the
aggwegate stwuct :c:type:`v4w2_fowmat` and the
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` and
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctws. Additionawwy the
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ioctw can be used to examine
what the hawdwawe *couwd* do, without actuawwy sewecting a new data
fowmat. The data fowmats suppowted by the V4W2 API awe covewed in the
wespective device section in :wef:`devices`. Fow a cwosew wook at
image fowmats see :wef:`pixfmt`.

The :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw is a majow tuwning-point in the
initiawization sequence. Pwiow to this point muwtipwe panew appwications
can access the same device concuwwentwy to sewect the cuwwent input,
change contwows ow modify othew pwopewties. The fiwst :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`
assigns a wogicaw stweam (video data, VBI data etc.) excwusivewy to one
fiwe descwiptow.

Excwusive means no othew appwication, mowe pwecisewy no othew fiwe
descwiptow, can gwab this stweam ow change device pwopewties
inconsistent with the negotiated pawametews. A video standawd change fow
exampwe, when the new standawd uses a diffewent numbew of scan wines,
can invawidate the sewected image fowmat. Thewefowe onwy the fiwe
descwiptow owning the stweam can make invawidating changes. Accowdingwy
muwtipwe fiwe descwiptows which gwabbed diffewent wogicaw stweams
pwevent each othew fwom intewfewing with theiw settings. When fow
exampwe video ovewway is about to stawt ow awweady in pwogwess,
simuwtaneous video captuwing may be westwicted to the same cwopping and
image size.

When appwications omit the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw its wocking side
effects awe impwied by the next step, the sewection of an I/O method
with the :wef:`VIDIOC_WEQBUFS` ioctw ow impwicit
with the fiwst :c:func:`wead()` ow
:c:func:`wwite()` caww.

Genewawwy onwy one wogicaw stweam can be assigned to a fiwe descwiptow,
the exception being dwivews pewmitting simuwtaneous video captuwing and
ovewway using the same fiwe descwiptow fow compatibiwity with V4W and
eawwiew vewsions of V4W2. Switching the wogicaw stweam ow wetuwning into
"panew mode" is possibwe by cwosing and weopening the device. Dwivews
*may* suppowt a switch using :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`.

Aww dwivews exchanging data with appwications must suppowt the
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` and :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw. Impwementation of the
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` is highwy wecommended but optionaw.

Image Fowmat Enumewation
========================

Apawt of the genewic fowmat negotiation functions a speciaw ioctw to
enumewate aww image fowmats suppowted by video captuwe, ovewway ow
output devices is avaiwabwe. [#f1]_

The :wef:`VIDIOC_ENUM_FMT` ioctw must be suppowted
by aww dwivews exchanging image data with appwications.

.. impowtant::

    Dwivews awe not supposed to convewt image fowmats in kewnew space.
    They must enumewate onwy fowmats diwectwy suppowted by the hawdwawe.
    If necessawy dwivew wwitews shouwd pubwish an exampwe convewsion
    woutine ow wibwawy fow integwation into appwications.

.. [#f1]
   Enumewating fowmats an appwication has no a-pwiowi knowwedge of
   (othewwise it couwd expwicitwy ask fow them and need not enumewate)
   seems usewess, but thewe awe appwications sewving as pwoxy between
   dwivews and the actuaw video appwications fow which this is usefuw.
