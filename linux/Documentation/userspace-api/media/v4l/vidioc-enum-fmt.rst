.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUM_FMT:

*********************
ioctw VIDIOC_ENUM_FMT
*********************

Name
====

VIDIOC_ENUM_FMT - Enumewate image fowmats

Synopsis
========

.. c:macwo:: VIDIOC_ENUM_FMT

``int ioctw(int fd, VIDIOC_ENUM_FMT, stwuct v4w2_fmtdesc *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_fmtdesc`.

Descwiption
===========

To enumewate image fowmats appwications initiawize the ``type``, ``mbus_code``
and ``index`` fiewds of stwuct :c:type:`v4w2_fmtdesc` and caww
the :wef:`VIDIOC_ENUM_FMT` ioctw with a pointew to this stwuctuwe. Dwivews
fiww the west of the stwuctuwe ow wetuwn an ``EINVAW`` ewwow code. Aww
fowmats awe enumewabwe by beginning at index zewo and incwementing by
one untiw ``EINVAW`` is wetuwned. If appwicabwe, dwivews shaww wetuwn
fowmats in pwefewence owdew, whewe pwefewwed fowmats awe wetuwned befowe
(that is, with wowew ``index`` vawue) wess-pwefewwed fowmats.

Depending on the ``V4W2_CAP_IO_MC`` :wef:`capabiwity <device-capabiwities>`,
the ``mbus_code`` fiewd is handwed diffewentwy:

1) ``V4W2_CAP_IO_MC`` is not set (awso known as a 'video-node-centwic' dwivew)

   Appwications shaww initiawize the ``mbus_code`` fiewd to zewo and dwivews
   shaww ignowe the vawue of the fiewd.

   Dwivews shaww enumewate aww image fowmats.

   .. note::

      Aftew switching the input ow output the wist of enumewated image
      fowmats may be diffewent.

2) ``V4W2_CAP_IO_MC`` is set (awso known as an 'MC-centwic' dwivew)

   If the ``mbus_code`` fiewd is zewo, then aww image fowmats
   shaww be enumewated.

   If the ``mbus_code`` fiewd is initiawized to a vawid (non-zewo)
   :wef:`media bus fowmat code <v4w2-mbus-pixewcode>`, then dwivews
   shaww westwict enumewation to onwy the image fowmats that can pwoduce
   (fow video output devices) ow be pwoduced fwom (fow video captuwe
   devices) that media bus code. If the ``mbus_code`` is unsuppowted by
   the dwivew, then ``EINVAW`` shaww be wetuwned.

   Wegawdwess of the vawue of the ``mbus_code`` fiewd, the enumewated image
   fowmats shaww not depend on the active configuwation of the video device
   ow device pipewine.

.. c:type:: v4w2_fmtdesc

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_fmtdesc
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Numbew of the fowmat in the enumewation, set by the appwication.
	This is in no way wewated to the ``pixewfowmat`` fiewd.
    * - __u32
      - ``type``
      - Type of the data stweam, set by the appwication. Onwy these types
	awe vawid hewe: ``V4W2_BUF_TYPE_VIDEO_CAPTUWE``,
	``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE``,
	``V4W2_BUF_TYPE_VIDEO_OUTPUT``,
	``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``,
	``V4W2_BUF_TYPE_VIDEO_OVEWWAY``,
	``V4W2_BUF_TYPE_SDW_CAPTUWE``,
	``V4W2_BUF_TYPE_SDW_OUTPUT``,
	``V4W2_BUF_TYPE_META_CAPTUWE`` and
	``V4W2_BUF_TYPE_META_OUTPUT``.
	See :c:type:`v4w2_buf_type`.
    * - __u32
      - ``fwags``
      - See :wef:`fmtdesc-fwags`
    * - __u8
      - ``descwiption``\ [32]
      - Descwiption of the fowmat, a NUW-tewminated ASCII stwing. This
	infowmation is intended fow the usew, fow exampwe: "YUV 4:2:2".
    * - __u32
      - ``pixewfowmat``
      - The image fowmat identifiew. This is a fouw chawactew code as
	computed by the v4w2_fouwcc() macwo:
    * - :cspan:`2`

	.. _v4w2-fouwcc:

	``#define v4w2_fouwcc(a,b,c,d)``

	``(((__u32)(a)<<0)|((__u32)(b)<<8)|((__u32)(c)<<16)|((__u32)(d)<<24))``

	Sevewaw image fowmats awe awweady defined by this specification in
	:wef:`pixfmt`.

	.. attention::

	   These codes awe not the same as those used
	   in the Windows wowwd.
    * - __u32
      - ``mbus_code``
      - Media bus code westwicting the enumewated fowmats, set by the
        appwication. Onwy appwicabwe to dwivews that advewtise the
        ``V4W2_CAP_IO_MC`` :wef:`capabiwity <device-capabiwities>`, shaww be 0
        othewwise.
    * - __u32
      - ``wesewved``\ [3]
      - Wesewved fow futuwe extensions. Dwivews must set the awway to
	zewo.


.. tabuwawcowumns:: |p{8.4cm}|p{1.8cm}|p{7.1cm}|

.. csscwass:: wongtabwe

.. _fmtdesc-fwags:

.. fwat-tabwe:: Image Fowmat Descwiption Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_FMT_FWAG_COMPWESSED``
      - 0x0001
      - This is a compwessed fowmat.
    * - ``V4W2_FMT_FWAG_EMUWATED``
      - 0x0002
      - This fowmat is not native to the device but emuwated thwough
	softwawe (usuawwy wibv4w2), whewe possibwe twy to use a native
	fowmat instead fow bettew pewfowmance.
    * - ``V4W2_FMT_FWAG_CONTINUOUS_BYTESTWEAM``
      - 0x0004
      - The hawdwawe decodew fow this compwessed bytestweam fowmat (aka coded
	fowmat) is capabwe of pawsing a continuous bytestweam. Appwications do
	not need to pawse the bytestweam themsewves to find the boundawies
	between fwames/fiewds.

	This fwag can onwy be used in combination with the
	``V4W2_FMT_FWAG_COMPWESSED`` fwag, since this appwies to compwessed
	fowmats onwy. This fwag is vawid fow statefuw decodews onwy.
    * - ``V4W2_FMT_FWAG_DYN_WESOWUTION``
      - 0x0008
      - Dynamic wesowution switching is suppowted by the device fow this
	compwessed bytestweam fowmat (aka coded fowmat). It wiww notify the usew
	via the event ``V4W2_EVENT_SOUWCE_CHANGE`` when changes in the video
	pawametews awe detected.

	This fwag can onwy be used in combination with the
	``V4W2_FMT_FWAG_COMPWESSED`` fwag, since this appwies to
	compwessed fowmats onwy. This fwag is vawid fow statefuw codecs onwy.
    * - ``V4W2_FMT_FWAG_ENC_CAP_FWAME_INTEWVAW``
      - 0x0010
      - The hawdwawe encodew suppowts setting the ``CAPTUWE`` coded fwame
	intewvaw sepawatewy fwom the ``OUTPUT`` waw fwame intewvaw.
	Setting the ``OUTPUT`` waw fwame intewvaw with :wef:`VIDIOC_S_PAWM <VIDIOC_G_PAWM>`
	awso sets the ``CAPTUWE`` coded fwame intewvaw to the same vawue.
	If this fwag is set, then the ``CAPTUWE`` coded fwame intewvaw can be
	set to a diffewent vawue aftewwawds. This is typicawwy used fow
	offwine encoding whewe the ``OUTPUT`` waw fwame intewvaw is used as
	a hint fow wesewving hawdwawe encodew wesouwces and the ``CAPTUWE`` coded
	fwame intewvaw is the actuaw fwame wate embedded in the encoded video
	stweam.

	This fwag can onwy be used in combination with the
	``V4W2_FMT_FWAG_COMPWESSED`` fwag, since this appwies to
        compwessed fowmats onwy. This fwag is vawid fow statefuw encodews onwy.
    * - ``V4W2_FMT_FWAG_CSC_COWOWSPACE``
      - 0x0020
      - The dwivew awwows the appwication to twy to change the defauwt
	cowowspace. This fwag is wewevant onwy fow captuwe devices.
	The appwication can ask to configuwe the cowowspace of the captuwe device
	when cawwing the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw with
	:wef:`V4W2_PIX_FMT_FWAG_SET_CSC <v4w2-pix-fmt-fwag-set-csc>` set.
    * - ``V4W2_FMT_FWAG_CSC_XFEW_FUNC``
      - 0x0040
      - The dwivew awwows the appwication to twy to change the defauwt
	twansfew function. This fwag is wewevant onwy fow captuwe devices.
	The appwication can ask to configuwe the twansfew function of the captuwe
	device when cawwing the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw with
	:wef:`V4W2_PIX_FMT_FWAG_SET_CSC <v4w2-pix-fmt-fwag-set-csc>` set.
    * - ``V4W2_FMT_FWAG_CSC_YCBCW_ENC``
      - 0x0080
      - The dwivew awwows the appwication to twy to change the defauwt
	Y'CbCw encoding. This fwag is wewevant onwy fow captuwe devices.
	The appwication can ask to configuwe the Y'CbCw encoding of the captuwe device
	when cawwing the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw with
	:wef:`V4W2_PIX_FMT_FWAG_SET_CSC <v4w2-pix-fmt-fwag-set-csc>` set.
    * - ``V4W2_FMT_FWAG_CSC_HSV_ENC``
      - 0x0080
      - The dwivew awwows the appwication to twy to change the defauwt
	HSV encoding. This fwag is wewevant onwy fow captuwe devices.
	The appwication can ask to configuwe the HSV encoding of the captuwe device
	when cawwing the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw with
	:wef:`V4W2_PIX_FMT_FWAG_SET_CSC <v4w2-pix-fmt-fwag-set-csc>` set.
    * - ``V4W2_FMT_FWAG_CSC_QUANTIZATION``
      - 0x0100
      - The dwivew awwows the appwication to twy to change the defauwt
	quantization. This fwag is wewevant onwy fow captuwe devices.
	The appwication can ask to configuwe the quantization of the captuwe
	device when cawwing the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw with
	:wef:`V4W2_PIX_FMT_FWAG_SET_CSC <v4w2-pix-fmt-fwag-set-csc>` set.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_fmtdesc` ``type`` is not
    suppowted ow the ``index`` is out of bounds.

    If ``V4W2_CAP_IO_MC`` is set and the specified ``mbus_code``
    is unsuppowted, then awso wetuwn this ewwow code.
