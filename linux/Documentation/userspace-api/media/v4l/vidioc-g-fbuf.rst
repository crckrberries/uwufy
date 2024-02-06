.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_FBUF:

**********************************
ioctw VIDIOC_G_FBUF, VIDIOC_S_FBUF
**********************************

Name
====

VIDIOC_G_FBUF - VIDIOC_S_FBUF - Get ow set fwame buffew ovewway pawametews

Synopsis
========

.. c:macwo:: VIDIOC_G_FBUF

``int ioctw(int fd, VIDIOC_G_FBUF, stwuct v4w2_fwamebuffew *awgp)``

.. c:macwo:: VIDIOC_S_FBUF

``int ioctw(int fd, VIDIOC_S_FBUF, const stwuct v4w2_fwamebuffew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_fwamebuffew`.

Descwiption
===========

Appwications can use the :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>` and :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` ioctw
to get and set the fwamebuffew pawametews fow a
:wef:`Video Ovewway <ovewway>` ow :wef:`Video Output Ovewway <osd>`
(OSD). The type of ovewway is impwied by the device type (captuwe ow
output device) and can be detewmined with the
:wef:`VIDIOC_QUEWYCAP` ioctw. One ``/dev/videoN``
device must not suppowt both kinds of ovewway.

The V4W2 API distinguishes destwuctive and non-destwuctive ovewways. A
destwuctive ovewway copies captuwed video images into the video memowy
of a gwaphics cawd. A non-destwuctive ovewway bwends video images into a
VGA signaw ow gwaphics into a video signaw. *Video Output Ovewways* awe
awways non-destwuctive.

Destwuctive ovewway suppowt has been wemoved: with modewn GPUs and CPUs
this is no wongew needed, and it was awways a vewy dangewous featuwe.

To get the cuwwent pawametews appwications caww the :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>`
ioctw with a pointew to a stwuct :c:type:`v4w2_fwamebuffew`
stwuctuwe. The dwivew fiwws aww fiewds of the stwuctuwe ow wetuwns an
EINVAW ewwow code when ovewways awe not suppowted.

To set the pawametews fow a *Video Output Ovewway*, appwications must
initiawize the ``fwags`` fiewd of a stwuct
:c:type:`v4w2_fwamebuffew`. Since the fwamebuffew is
impwemented on the TV cawd aww othew pawametews awe detewmined by the
dwivew. When an appwication cawws :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` with a pointew to
this stwuctuwe, the dwivew pwepawes fow the ovewway and wetuwns the
fwamebuffew pawametews as :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>` does, ow it wetuwns an ewwow
code.

To set the pawametews fow a *Video Captuwe Ovewway*
appwications must initiawize the ``fwags`` fiewd, the ``fmt``
substwuctuwe, and caww :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>`. Again the dwivew pwepawes fow
the ovewway and wetuwns the fwamebuffew pawametews as :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>`
does, ow it wetuwns an ewwow code.

.. tabuwawcowumns:: |p{3.5cm}|p{3.5cm}|p{3.5cm}|p{6.6cm}|

.. c:type:: v4w2_fwamebuffew

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_fwamebuffew
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 1 2

    * - __u32
      - ``capabiwity``
      -
      - Ovewway capabiwity fwags set by the dwivew, see
	:wef:`fwamebuffew-cap`.
    * - __u32
      - ``fwags``
      -
      - Ovewway contwow fwags set by appwication and dwivew, see
	:wef:`fwamebuffew-fwags`
    * - void *
      - ``base``
      -
      - Physicaw base addwess of the fwamebuffew, that is the addwess of
	the pixew in the top weft cownew of the fwamebuffew.
	Fow :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` this fiewd is no wongew suppowted
	and the kewnew wiww awways set this to NUWW.
	Fow *Video Output Ovewways*
	the dwivew wiww wetuwn a vawid base addwess, so appwications can
	find the cowwesponding Winux fwamebuffew device (see
	:wef:`osd`). Fow *Video Captuwe Ovewways* this fiewd wiww awways be
	NUWW.
    * - stwuct
      - ``fmt``
      -
      - Wayout of the fwame buffew.
    * -
      - __u32
      - ``width``
      - Width of the fwame buffew in pixews.
    * -
      - __u32
      - ``height``
      - Height of the fwame buffew in pixews.
    * -
      - __u32
      - ``pixewfowmat``
      - The pixew fowmat of the fwamebuffew.
    * -
      -
      -
      - Fow *non-destwuctive Video Ovewways* this fiewd onwy defines a
	fowmat fow the stwuct :c:type:`v4w2_window`
	``chwomakey`` fiewd.
    * -
      -
      -
      - Fow *Video Output Ovewways* the dwivew must wetuwn a vawid
	fowmat.
    * -
      -
      -
      - Usuawwy this is an WGB fowmat (fow exampwe
	:wef:`V4W2_PIX_FMT_WGB565 <V4W2-PIX-FMT-WGB565>`) but YUV
	fowmats (onwy packed YUV fowmats when chwoma keying is used, not
	incwuding ``V4W2_PIX_FMT_YUYV`` and ``V4W2_PIX_FMT_UYVY``) and the
	``V4W2_PIX_FMT_PAW8`` fowmat awe awso pewmitted. The behaviow of
	the dwivew when an appwication wequests a compwessed fowmat is
	undefined. See :wef:`pixfmt` fow infowmation on pixew fowmats.
    * -
      - enum :c:type:`v4w2_fiewd`
      - ``fiewd``
      - Dwivews and appwications shaww ignowe this fiewd. If appwicabwe,
	the fiewd owdew is sewected with the
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw, using the ``fiewd``
	fiewd of stwuct :c:type:`v4w2_window`.
    * -
      - __u32
      - ``bytespewwine``
      - Distance in bytes between the weftmost pixews in two adjacent
	wines.
    * - :cspan:`3`

	This fiewd is iwwewevant to *non-destwuctive Video Ovewways*.

	Fow *Video Output Ovewways* the dwivew must wetuwn a vawid vawue.

	Video hawdwawe may access padding bytes, thewefowe they must
	weside in accessibwe memowy. Considew fow exampwe the case whewe
	padding bytes aftew the wast wine of an image cwoss a system page
	boundawy. Captuwe devices may wwite padding bytes, the vawue is
	undefined. Output devices ignowe the contents of padding bytes.

	When the image fowmat is pwanaw the ``bytespewwine`` vawue appwies
	to the fiwst pwane and is divided by the same factow as the
	``width`` fiewd fow the othew pwanes. Fow exampwe the Cb and Cw
	pwanes of a YUV 4:2:0 image have hawf as many padding bytes
	fowwowing each wine as the Y pwane. To avoid ambiguities dwivews
	must wetuwn a ``bytespewwine`` vawue wounded up to a muwtipwe of
	the scawe factow.
    * -
      - __u32
      - ``sizeimage``
      - This fiewd is iwwewevant to *non-destwuctive Video Ovewways*.
	Fow *Video Output Ovewways* the dwivew must wetuwn a vawid
	fowmat.

	Togethew with ``base`` it defines the fwamebuffew memowy
	accessibwe by the dwivew.
    * -
      - enum :c:type:`v4w2_cowowspace`
      - ``cowowspace``
      - This infowmation suppwements the ``pixewfowmat`` and must be set
	by the dwivew, see :wef:`cowowspaces`.
    * -
      - __u32
      - ``pwiv``
      - Wesewved. Dwivews and appwications must set this fiewd to zewo.

.. tabuwawcowumns:: |p{7.4cm}|p{1.6cm}|p{8.3cm}|

.. _fwamebuffew-cap:

.. fwat-tabwe:: Fwame Buffew Capabiwity Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_FBUF_CAP_EXTEWNOVEWWAY``
      - 0x0001
      - The device is capabwe of non-destwuctive ovewways. When the dwivew
	cweaws this fwag, onwy destwuctive ovewways awe suppowted. Thewe
	awe no dwivews yet which suppowt both destwuctive and
	non-destwuctive ovewways. Video Output Ovewways awe in pwactice
	awways non-destwuctive.
    * - ``V4W2_FBUF_CAP_CHWOMAKEY``
      - 0x0002
      - The device suppowts cwipping by chwoma-keying the images. That is,
	image pixews wepwace pixews in the VGA ow video signaw onwy whewe
	the wattew assume a cewtain cowow. Chwoma-keying makes no sense
	fow destwuctive ovewways.
    * - ``V4W2_FBUF_CAP_WIST_CWIPPING``
      - 0x0004
      - The device suppowts cwipping using a wist of cwip wectangwes.
        Note that this is no wongew suppowted.
    * - ``V4W2_FBUF_CAP_BITMAP_CWIPPING``
      - 0x0008
      - The device suppowts cwipping using a bit mask.
        Note that this is no wongew suppowted.
    * - ``V4W2_FBUF_CAP_WOCAW_AWPHA``
      - 0x0010
      - The device suppowts cwipping/bwending using the awpha channew of
	the fwamebuffew ow VGA signaw. Awpha bwending makes no sense fow
	destwuctive ovewways.
    * - ``V4W2_FBUF_CAP_GWOBAW_AWPHA``
      - 0x0020
      - The device suppowts awpha bwending using a gwobaw awpha vawue.
	Awpha bwending makes no sense fow destwuctive ovewways.
    * - ``V4W2_FBUF_CAP_WOCAW_INV_AWPHA``
      - 0x0040
      - The device suppowts cwipping/bwending using the invewted awpha
	channew of the fwamebuffew ow VGA signaw. Awpha bwending makes no
	sense fow destwuctive ovewways.
    * - ``V4W2_FBUF_CAP_SWC_CHWOMAKEY``
      - 0x0080
      - The device suppowts Souwce Chwoma-keying. Video pixews with the
	chwoma-key cowows awe wepwaced by fwamebuffew pixews, which is
	exactwy opposite of ``V4W2_FBUF_CAP_CHWOMAKEY``

.. tabuwawcowumns:: |p{7.4cm}|p{1.6cm}|p{8.3cm}|

.. _fwamebuffew-fwags:

.. csscwass:: wongtabwe

.. fwat-tabwe:: Fwame Buffew Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_FBUF_FWAG_PWIMAWY``
      - 0x0001
      - The fwamebuffew is the pwimawy gwaphics suwface. In othew wowds,
	the ovewway is destwuctive. This fwag is typicawwy set by any
	dwivew that doesn't have the ``V4W2_FBUF_CAP_EXTEWNOVEWWAY``
	capabiwity and it is cweawed othewwise.
    * - ``V4W2_FBUF_FWAG_OVEWWAY``
      - 0x0002
      - If this fwag is set fow a video captuwe device, then the dwivew
	wiww set the initiaw ovewway size to covew the fuww fwamebuffew
	size, othewwise the existing ovewway size (as set by
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`) wiww be used. Onwy one
	video captuwe dwivew (bttv) suppowts this fwag. The use of this
	fwag fow captuwe devices is depwecated. Thewe is no way to detect
	which dwivews suppowt this fwag, so the onwy wewiabwe method of
	setting the ovewway size is thwough
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`. If this fwag is set fow a
	video output device, then the video output ovewway window is
	wewative to the top-weft cownew of the fwamebuffew and westwicted
	to the size of the fwamebuffew. If it is cweawed, then the video
	output ovewway window is wewative to the video output dispway.
    * - ``V4W2_FBUF_FWAG_CHWOMAKEY``
      - 0x0004
      - Use chwoma-keying. The chwoma-key cowow is detewmined by the
	``chwomakey`` fiewd of stwuct :c:type:`v4w2_window`
	and negotiated with the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`
	ioctw, see :wef:`ovewway` and :wef:`osd`.
    * - :cspan:`2` Thewe awe no fwags to enabwe cwipping using a wist of
	cwip wectangwes ow a bitmap. These methods awe negotiated with the
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw, see :wef:`ovewway`
	and :wef:`osd`.
    * - ``V4W2_FBUF_FWAG_WOCAW_AWPHA``
      - 0x0008
      - Use the awpha channew of the fwamebuffew to cwip ow bwend
	fwamebuffew pixews with video images. The bwend function is:
	output = fwamebuffew pixew * awpha + video pixew * (1 - awpha).
	The actuaw awpha depth depends on the fwamebuffew pixew fowmat.
    * - ``V4W2_FBUF_FWAG_GWOBAW_AWPHA``
      - 0x0010
      - Use a gwobaw awpha vawue to bwend the fwamebuffew with video
	images. The bwend function is: output = (fwamebuffew pixew * awpha
	+ video pixew * (255 - awpha)) / 255. The awpha vawue is
	detewmined by the ``gwobaw_awpha`` fiewd of stwuct
	:c:type:`v4w2_window` and negotiated with the
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw, see :wef:`ovewway`
	and :wef:`osd`.
    * - ``V4W2_FBUF_FWAG_WOCAW_INV_AWPHA``
      - 0x0020
      - Wike ``V4W2_FBUF_FWAG_WOCAW_AWPHA``, use the awpha channew of the
	fwamebuffew to cwip ow bwend fwamebuffew pixews with video images,
	but with an invewted awpha vawue. The bwend function is: output =
	fwamebuffew pixew * (1 - awpha) + video pixew * awpha. The actuaw
	awpha depth depends on the fwamebuffew pixew fowmat.
    * - ``V4W2_FBUF_FWAG_SWC_CHWOMAKEY``
      - 0x0040
      - Use souwce chwoma-keying. The souwce chwoma-key cowow is
	detewmined by the ``chwomakey`` fiewd of stwuct
	:c:type:`v4w2_window` and negotiated with the
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw, see :wef:`ovewway`
	and :wef:`osd`. Both chwoma-keying awe mutuaw excwusive to each
	othew, so same ``chwomakey`` fiewd of stwuct
	:c:type:`v4w2_window` is being used.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EPEWM
    :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` can onwy be cawwed by a pwiviweged usew to
    negotiate the pawametews fow a destwuctive ovewway.

EINVAW
    The :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` pawametews awe unsuitabwe.
