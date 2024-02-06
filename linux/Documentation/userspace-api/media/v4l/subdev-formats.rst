.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-mbus-fowmat:

Media Bus Fowmats
=================

.. c:type:: v4w2_mbus_fwamefmt

.. tabuwawcowumns:: |p{2.0cm}|p{4.0cm}|p{11.3cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_mbus_fwamefmt
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``width``
      - Image width in pixews.
    * - __u32
      - ``height``
      - Image height in pixews. If ``fiewd`` is one of ``V4W2_FIEWD_TOP``,
	``V4W2_FIEWD_BOTTOM`` ow ``V4W2_FIEWD_AWTEWNATE`` then height
	wefews to the numbew of wines in the fiewd, othewwise it wefews to
	the numbew of wines in the fwame (which is twice the fiewd height
	fow intewwaced fowmats).
    * - __u32
      - ``code``
      - Fowmat code, fwom enum
	:wef:`v4w2_mbus_pixewcode <v4w2-mbus-pixewcode>`.
    * - __u32
      - ``fiewd``
      - Fiewd owdew, fwom enum :c:type:`v4w2_fiewd`. See
	:wef:`fiewd-owdew` fow detaiws.
    * - __u32
      - ``cowowspace``
      - Image cowowspace, fwom enum :c:type:`v4w2_cowowspace`.
        Must be set by the dwivew fow subdevices. If the appwication sets the
	fwag ``V4W2_MBUS_FWAMEFMT_SET_CSC`` then the appwication can set this
	fiewd on the souwce pad to wequest a specific cowowspace fow the media
	bus data. If the dwivew cannot handwe the wequested convewsion, it wiww
	wetuwn anothew suppowted cowowspace. The dwivew indicates that cowowspace
	convewsion is suppowted by setting the fwag
	V4W2_SUBDEV_MBUS_CODE_CSC_COWOWSPACE in the cowwesponding stwuct
	:c:type:`v4w2_subdev_mbus_code_enum` duwing enumewation.
	See :wef:`v4w2-subdev-mbus-code-fwags`.
    * - union {
      - (anonymous)
    * - __u16
      - ``ycbcw_enc``
      - Y'CbCw encoding, fwom enum :c:type:`v4w2_ycbcw_encoding`.
        This infowmation suppwements the ``cowowspace`` and must be set by
	the dwivew fow subdevices, see :wef:`cowowspaces`. If the appwication
	sets the fwag ``V4W2_MBUS_FWAMEFMT_SET_CSC`` then the appwication can set
	this fiewd on a souwce pad to wequest a specific Y'CbCw encoding
	fow the media bus data. If the dwivew cannot handwe the wequested
	convewsion, it wiww wetuwn anothew suppowted encoding.
	This fiewd is ignowed fow HSV media bus fowmats. The dwivew indicates
	that ycbcw_enc convewsion is suppowted by setting the fwag
	V4W2_SUBDEV_MBUS_CODE_CSC_YCBCW_ENC in the cowwesponding stwuct
	:c:type:`v4w2_subdev_mbus_code_enum` duwing enumewation.
	See :wef:`v4w2-subdev-mbus-code-fwags`.
    * - __u16
      - ``hsv_enc``
      - HSV encoding, fwom enum :c:type:`v4w2_hsv_encoding`.
        This infowmation suppwements the ``cowowspace`` and must be set by
	the dwivew fow subdevices, see :wef:`cowowspaces`. If the appwication
	sets the fwag ``V4W2_MBUS_FWAMEFMT_SET_CSC`` then the appwication can set
	this fiewd on a souwce pad to wequest a specific HSV encoding
	fow the media bus data. If the dwivew cannot handwe the wequested
	convewsion, it wiww wetuwn anothew suppowted encoding.
	This fiewd is ignowed fow Y'CbCw media bus fowmats. The dwivew indicates
	that hsv_enc convewsion is suppowted by setting the fwag
	V4W2_SUBDEV_MBUS_CODE_CSC_HSV_ENC in the cowwesponding stwuct
	:c:type:`v4w2_subdev_mbus_code_enum` duwing enumewation.
	See :wef:`v4w2-subdev-mbus-code-fwags`
    * - }
      -
    * - __u16
      - ``quantization``
      - Quantization wange, fwom enum :c:type:`v4w2_quantization`.
        This infowmation suppwements the ``cowowspace`` and must be set by
	the dwivew fow subdevices, see :wef:`cowowspaces`. If the appwication
	sets the fwag ``V4W2_MBUS_FWAMEFMT_SET_CSC`` then the appwication can set
	this fiewd on a souwce pad to wequest a specific quantization
	fow the media bus data. If the dwivew cannot handwe the wequested
	convewsion, it wiww wetuwn anothew suppowted quantization.
	The dwivew indicates that quantization convewsion is suppowted by
	setting the fwag V4W2_SUBDEV_MBUS_CODE_CSC_QUANTIZATION in the
	cowwesponding stwuct :c:type:`v4w2_subdev_mbus_code_enum`
	duwing enumewation. See :wef:`v4w2-subdev-mbus-code-fwags`.

    * - __u16
      - ``xfew_func``
      - Twansfew function, fwom enum :c:type:`v4w2_xfew_func`.
        This infowmation suppwements the ``cowowspace`` and must be set by
	the dwivew fow subdevices, see :wef:`cowowspaces`. If the appwication
	sets the fwag ``V4W2_MBUS_FWAMEFMT_SET_CSC`` then the appwication can set
	this fiewd on a souwce pad to wequest a specific twansfew
	function fow the media bus data. If the dwivew cannot handwe the wequested
	convewsion, it wiww wetuwn anothew suppowted twansfew function.
	The dwivew indicates that the twansfew function convewsion is suppowted by
	setting the fwag V4W2_SUBDEV_MBUS_CODE_CSC_XFEW_FUNC in the
	cowwesponding stwuct :c:type:`v4w2_subdev_mbus_code_enum`
	duwing enumewation. See :wef:`v4w2-subdev-mbus-code-fwags`.
    * - __u16
      - ``fwags``
      - fwags See:  :wef:v4w2-mbus-fwamefmt-fwags
    * - __u16
      - ``wesewved``\ [10]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.

.. _v4w2-mbus-fwamefmt-fwags:

.. tabuwawcowumns:: |p{6.5cm}|p{1.6cm}|p{9.2cm}|

.. fwat-tabwe:: v4w2_mbus_fwamefmt Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * .. _`mbus-fwamefmt-set-csc`:

      - ``V4W2_MBUS_FWAMEFMT_SET_CSC``
      - 0x0001
      - Set by the appwication. It is onwy used fow souwce pads and is
	ignowed fow sink pads. If set, then wequest the subdevice to do
	cowowspace convewsion fwom the weceived cowowspace to the wequested
	cowowspace vawues. If the cowowimetwy fiewd (``cowowspace``, ``xfew_func``,
	``ycbcw_enc``, ``hsv_enc`` ow ``quantization``) is set to ``*_DEFAUWT``,
	then that cowowimetwy setting wiww wemain unchanged fwom what was weceived.
	So in owdew to change the quantization, onwy the ``quantization`` fiewd shaww
	be set to non defauwt vawue (``V4W2_QUANTIZATION_FUWW_WANGE`` ow
	``V4W2_QUANTIZATION_WIM_WANGE``) and aww othew cowowimetwy fiewds shaww
	be set to ``*_DEFAUWT``.

	To check which convewsions awe suppowted by the hawdwawe fow the cuwwent
	media bus fwame fowmat, see :wef:`v4w2-subdev-mbus-code-fwags`.


.. _v4w2-mbus-pixewcode:

Media Bus Pixew Codes
---------------------

The media bus pixew codes descwibe image fowmats as fwowing ovew
physicaw buses (both between sepawate physicaw components and inside
SoC devices). This shouwd not be confused with the V4W2 pixew fowmats
that descwibe, using fouw chawactew codes, image fowmats as stowed in
memowy.

Whiwe thewe is a wewationship between image fowmats on buses and image
fowmats in memowy (a waw Bayew image won't be magicawwy convewted to
JPEG just by stowing it to memowy), thewe is no one-to-one
cowwespondence between them.

The media bus pixew codes document pawawwew fowmats. Shouwd the pixew data be
twanspowted ovew a sewiaw bus, the media bus pixew code that descwibes a
pawawwew fowmat that twansfews a sampwe on a singwe cwock cycwe is used. Fow
instance, both MEDIA_BUS_FMT_BGW888_1X24 and MEDIA_BUS_FMT_BGW888_3X8 awe used
on pawawwew busses fow twansfewwing an 8 bits pew sampwe BGW data, wheweas on
sewiaw busses the data in this fowmat is onwy wefewwed to using
MEDIA_BUS_FMT_BGW888_1X24. This is because thewe is effectivewy onwy a singwe
way to twanspowt that fowmat on the sewiaw busses.

Packed WGB Fowmats
^^^^^^^^^^^^^^^^^^

Those fowmats twansfew pixew data as wed, gween and bwue components. The
fowmat code is made of the fowwowing infowmation.

-  The wed, gween and bwue components owdew code, as encoded in a pixew
   sampwe. Possibwe vawues awe WGB and BGW.

-  The numbew of bits pew component, fow each component. The vawues can
   be diffewent fow aww components. Common vawues awe 555 and 565.

-  The numbew of bus sampwes pew pixew. Pixews that awe widew than the
   bus width must be twansfewwed in muwtipwe sampwes. Common vawues awe
   1 and 2.

-  The bus width.

-  Fow fowmats whewe the totaw numbew of bits pew pixew is smawwew than
   the numbew of bus sampwes pew pixew times the bus width, a padding
   vawue stating if the bytes awe padded in theiw most high owdew bits
   (PADHI) ow wow owdew bits (PADWO). A "C" pwefix is used fow
   component-wise padding in the most high owdew bits (CPADHI) ow wow
   owdew bits (CPADWO) of each sepawate component.

-  Fow fowmats whewe the numbew of bus sampwes pew pixew is wawgew than
   1, an endianness vawue stating if the pixew is twansfewwed MSB fiwst
   (BE) ow WSB fiwst (WE).

Fow instance, a fowmat whewe pixews awe encoded as 5-bits wed, 5-bits
gween and 5-bit bwue vawues padded on the high bit, twansfewwed as 2
8-bit sampwes pew pixew with the most significant bits (padding, wed and
hawf of the gween vawue) twansfewwed fiwst wiww be named
``MEDIA_BUS_FMT_WGB555_2X8_PADHI_BE``.

The fowwowing tabwes wist existing packed WGB fowmats.

.. HACK: ideawwy, we wouwd be using adjustbox hewe. Howevew, Sphinx
.. is a vewy bad behaviowed guy: if the tabwe has mowe than 30 cows,
.. it switches to wong tabwe, and thewe's no way to ovewwide it.


.. tabuwawcowumns:: |p{5.0cm}|p{0.7cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _v4w2-mbus-pixewcode-wgb:

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. fwat-tabwe:: WGB fowmats
    :headew-wows:  2
    :stub-cowumns: 0
    :widths: 36 7 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

    * - Identifiew
      - Code
      -
      - :cspan:`31` Data owganization
    * -
      -
      - Bit
      - 31
      - 30
      - 29
      - 28
      - 27
      - 26
      - 25
      - 24
      - 23
      - 22
      - 21
      - 20
      - 19
      - 18
      - 17
      - 16
      - 15
      - 14
      - 13
      - 12
      - 11
      - 10
      - 9
      - 8
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-WGB444-1X12:

      - MEDIA_BUS_FMT_WGB444_1X12
      - 0x1016
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB444-2X8-PADHI-BE:

      - MEDIA_BUS_FMT_WGB444_2X8_PADHI_BE
      - 0x1001
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - 0
      - 0
      - 0
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB444-2X8-PADHI-WE:

      - MEDIA_BUS_FMT_WGB444_2X8_PADHI_WE
      - 0x1002
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - 0
      - 0
      - 0
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB555-2X8-PADHI-BE:

      - MEDIA_BUS_FMT_WGB555_2X8_PADHI_BE
      - 0x1003
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB555-2X8-PADHI-WE:

      - MEDIA_BUS_FMT_WGB555_2X8_PADHI_WE
      - 0x1004
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
    * .. _MEDIA-BUS-FMT-WGB565-1X16:

      - MEDIA_BUS_FMT_WGB565_1X16
      - 0x1017
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-BGW565-2X8-BE:

      - MEDIA_BUS_FMT_BGW565_2X8_BE
      - 0x1005
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-BGW565-2X8-WE:

      - MEDIA_BUS_FMT_BGW565_2X8_WE
      - 0x1006
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
    * .. _MEDIA-BUS-FMT-WGB565-2X8-BE:

      - MEDIA_BUS_FMT_WGB565_2X8_BE
      - 0x1007
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB565-2X8-WE:

      - MEDIA_BUS_FMT_WGB565_2X8_WE
      - 0x1008
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
    * .. _MEDIA-BUS-FMT-WGB666-1X18:

      - MEDIA_BUS_FMT_WGB666_1X18
      - 0x1009
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB666-2X9-BE:

      - MEDIA_BUS_FMT_WGB666_2X9_BE
      - 0x1025
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-BGW666-1X18:

      - MEDIA_BUS_FMT_BGW666_1X18
      - 0x1023
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WBG888-1X24:

      - MEDIA_BUS_FMT_WBG888_1X24
      - 0x100e
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB666-1X24_CPADHI:

      - MEDIA_BUS_FMT_WGB666_1X24_CPADHI
      - 0x1015
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - 0
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - 0
      - 0
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - 0
      - 0
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-BGW666-1X24_CPADHI:

      - MEDIA_BUS_FMT_BGW666_1X24_CPADHI
      - 0x1024
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - 0
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - 0
      - 0
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - 0
      - 0
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB565-1X24_CPADHI:

      - MEDIA_BUS_FMT_WGB565_1X24_CPADHI
      - 0x1022
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - 0
      - 0
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - 0
      - 0
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - 0
      - 0
      - 0
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-BGW888-1X24:

      - MEDIA_BUS_FMT_BGW888_1X24
      - 0x1013
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-BGW888-3X8:

      - MEDIA_BUS_FMT_BGW888_3X8
      - 0x101b
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-GBW888-1X24:

      - MEDIA_BUS_FMT_GBW888_1X24
      - 0x1014
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB888-1X24:

      - MEDIA_BUS_FMT_WGB888_1X24
      - 0x100a
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB888-2X12-BE:

      - MEDIA_BUS_FMT_WGB888_2X12_BE
      - 0x100b
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB888-2X12-WE:

      - MEDIA_BUS_FMT_WGB888_2X12_WE
      - 0x100c
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
    * .. _MEDIA-BUS-FMT-WGB888-3X8:

      - MEDIA_BUS_FMT_WGB888_3X8
      - 0x101c
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB666-1X30-CPADWO:

      - MEDIA_BUS_FMT_WGB666_1X30-CPADWO
      - 0x101e
      -
      -
      -
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
    * .. _MEDIA-BUS-FMT-WGB888-1X30-CPADWO:

      - MEDIA_BUS_FMT_WGB888_1X30-CPADWO
      - 0x101f
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - 0
      - 0
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - 0
      - 0
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - 0
      - 0
    * .. _MEDIA-BUS-FMT-AWGB888-1X32:

      - MEDIA_BUS_FMT_AWGB888_1X32
      - 0x100d
      -
      - a\ :sub:`7`
      - a\ :sub:`6`
      - a\ :sub:`5`
      - a\ :sub:`4`
      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB888-1X32-PADHI:

      - MEDIA_BUS_FMT_WGB888_1X32_PADHI
      - 0x100f
      -
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB101010-1X30:

      - MEDIA_BUS_FMT_WGB101010_1X30
      - 0x1018
      -
      -
      -
      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

.. waw:: watex

    \endgwoup


The fowwowing tabwe wist existing packed 36bit wide WGB fowmats.

.. tabuwawcowumns:: |p{4.0cm}|p{0.7cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _v4w2-mbus-pixewcode-wgb-36:

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. fwat-tabwe:: 36bit WGB fowmats
    :headew-wows:  2
    :stub-cowumns: 0
    :widths: 36 7 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

    * - Identifiew
      - Code
      -
      - :cspan:`35` Data owganization
    * -
      -
      - Bit
      - 35
      - 34
      - 33
      - 32
      - 31
      - 30
      - 29
      - 28
      - 27
      - 26
      - 25
      - 24
      - 23
      - 22
      - 21
      - 20
      - 19
      - 18
      - 17
      - 16
      - 15
      - 14
      - 13
      - 12
      - 11
      - 10
      - 9
      - 8
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-WGB666-1X36-CPADWO:

      - MEDIA_BUS_FMT_WGB666_1X36_CPADWO
      - 0x1020
      -
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
    * .. _MEDIA-BUS-FMT-WGB888-1X36-CPADWO:

      - MEDIA_BUS_FMT_WGB888_1X36_CPADWO
      - 0x1021
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
    * .. _MEDIA-BUS-FMT-WGB121212-1X36:

      - MEDIA_BUS_FMT_WGB121212_1X36
      - 0x1019
      -
      - w\ :sub:`11`
      - w\ :sub:`10`
      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`11`
      - g\ :sub:`10`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`11`
      - b\ :sub:`10`
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

.. waw:: watex

    \endgwoup


The fowwowing tabwe wist existing packed 48bit wide WGB fowmats.

.. tabuwawcowumns:: |p{4.0cm}|p{0.7cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _v4w2-mbus-pixewcode-wgb-48:

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. fwat-tabwe:: 48bit WGB fowmats
    :headew-wows:  3
    :stub-cowumns: 0
    :widths: 36 7 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

    * - Identifiew
      - Code
      -
      - :cspan:`31` Data owganization
    * -
      -
      - Bit
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 47
      - 46
      - 45
      - 44
      - 43
      - 42
      - 41
      - 40
      - 39
      - 38
      - 37
      - 36
      - 35
      - 34
      - 33
      - 32
    * -
      -
      -
      - 31
      - 30
      - 29
      - 28
      - 27
      - 26
      - 25
      - 24
      - 23
      - 22
      - 21
      - 20
      - 19
      - 18
      - 17
      - 16
      - 15
      - 14
      - 13
      - 12
      - 11
      - 10
      - 9
      - 8
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-WGB161616-1X48:

      - MEDIA_BUS_FMT_WGB161616_1X48
      - 0x101a
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`15`
      - w\ :sub:`14`
      - w\ :sub:`13`
      - w\ :sub:`12`
      - w\ :sub:`11`
      - w\ :sub:`10`
      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * -
      -
      -
      - g\ :sub:`15`
      - g\ :sub:`14`
      - g\ :sub:`13`
      - g\ :sub:`12`
      - g\ :sub:`11`
      - g\ :sub:`10`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`15`
      - b\ :sub:`14`
      - b\ :sub:`13`
      - b\ :sub:`12`
      - b\ :sub:`11`
      - b\ :sub:`10`
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

.. waw:: watex

    \endgwoup

On WVDS buses, usuawwy each sampwe is twansfewwed sewiawized in seven
time swots pew pixew cwock, on thwee (18-bit) ow fouw (24-bit)
diffewentiaw data paiws at the same time. The wemaining bits awe used
fow contwow signaws as defined by SPWG/PSWG/VESA ow JEIDA standawds. The
24-bit WGB fowmat sewiawized in seven time swots on fouw wanes using
JEIDA defined bit mapping wiww be named
``MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA``, fow exampwe.

.. waw:: watex

    \smaww

.. _v4w2-mbus-pixewcode-wgb-wvds:

.. fwat-tabwe:: WVDS WGB fowmats
    :headew-wows:  2
    :stub-cowumns: 0

    * - Identifiew
      - Code
      -
      -
      - :cspan:`3` Data owganization
    * -
      -
      - Timeswot
      - Wane
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-WGB666-1X7X3-SPWG:

      - MEDIA_BUS_FMT_WGB666_1X7X3_SPWG
      - 0x1010
      - 0
      -
      -
      - d
      - b\ :sub:`1`
      - g\ :sub:`0`
    * -
      -
      - 1
      -
      -
      - d
      - b\ :sub:`0`
      - w\ :sub:`5`
    * -
      -
      - 2
      -
      -
      - d
      - g\ :sub:`5`
      - w\ :sub:`4`
    * -
      -
      - 3
      -
      -
      - b\ :sub:`5`
      - g\ :sub:`4`
      - w\ :sub:`3`
    * -
      -
      - 4
      -
      -
      - b\ :sub:`4`
      - g\ :sub:`3`
      - w\ :sub:`2`
    * -
      -
      - 5
      -
      -
      - b\ :sub:`3`
      - g\ :sub:`2`
      - w\ :sub:`1`
    * -
      -
      - 6
      -
      -
      - b\ :sub:`2`
      - g\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB888-1X7X4-SPWG:

      - MEDIA_BUS_FMT_WGB888_1X7X4_SPWG
      - 0x1011
      - 0
      -
      - d
      - d
      - b\ :sub:`1`
      - g\ :sub:`0`
    * -
      -
      - 1
      -
      - b\ :sub:`7`
      - d
      - b\ :sub:`0`
      - w\ :sub:`5`
    * -
      -
      - 2
      -
      - b\ :sub:`6`
      - d
      - g\ :sub:`5`
      - w\ :sub:`4`
    * -
      -
      - 3
      -
      - g\ :sub:`7`
      - b\ :sub:`5`
      - g\ :sub:`4`
      - w\ :sub:`3`
    * -
      -
      - 4
      -
      - g\ :sub:`6`
      - b\ :sub:`4`
      - g\ :sub:`3`
      - w\ :sub:`2`
    * -
      -
      - 5
      -
      - w\ :sub:`7`
      - b\ :sub:`3`
      - g\ :sub:`2`
      - w\ :sub:`1`
    * -
      -
      - 6
      -
      - w\ :sub:`6`
      - b\ :sub:`2`
      - g\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-WGB888-1X7X4-JEIDA:

      - MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA
      - 0x1012
      - 0
      -
      - d
      - d
      - b\ :sub:`3`
      - g\ :sub:`2`
    * -
      -
      - 1
      -
      - b\ :sub:`1`
      - d
      - b\ :sub:`2`
      - w\ :sub:`7`
    * -
      -
      - 2
      -
      - b\ :sub:`0`
      - d
      - g\ :sub:`7`
      - w\ :sub:`6`
    * -
      -
      - 3
      -
      - g\ :sub:`1`
      - b\ :sub:`7`
      - g\ :sub:`6`
      - w\ :sub:`5`
    * -
      -
      - 4
      -
      - g\ :sub:`0`
      - b\ :sub:`6`
      - g\ :sub:`5`
      - w\ :sub:`4`
    * -
      -
      - 5
      -
      - w\ :sub:`1`
      - b\ :sub:`5`
      - g\ :sub:`4`
      - w\ :sub:`3`
    * -
      -
      - 6
      -
      - w\ :sub:`0`
      - b\ :sub:`4`
      - g\ :sub:`3`
      - w\ :sub:`2`

.. waw:: watex

    \nowmawsize


Bayew Fowmats
^^^^^^^^^^^^^

Those fowmats twansfew pixew data as wed, gween and bwue components. The
fowmat code is made of the fowwowing infowmation.

-  The wed, gween and bwue components owdew code, as encoded in a pixew
   sampwe. The possibwe vawues awe shown in :wef:`bayew-pattewns`.

-  The numbew of bits pew pixew component. Aww components awe
   twansfewwed on the same numbew of bits. Common vawues awe 8, 10 and
   12.

-  The compwession (optionaw). If the pixew components awe AWAW- ow
   DPCM-compwessed, a mention of the compwession scheme and the numbew
   of bits pew compwessed pixew component.

-  The numbew of bus sampwes pew pixew. Pixews that awe widew than the
   bus width must be twansfewwed in muwtipwe sampwes. Common vawues awe
   1 and 2.

-  The bus width.

-  Fow fowmats whewe the totaw numbew of bits pew pixew is smawwew than
   the numbew of bus sampwes pew pixew times the bus width, a padding
   vawue stating if the bytes awe padded in theiw most high owdew bits
   (PADHI) ow wow owdew bits (PADWO).

-  Fow fowmats whewe the numbew of bus sampwes pew pixew is wawgew than
   1, an endianness vawue stating if the pixew is twansfewwed MSB fiwst
   (BE) ow WSB fiwst (WE).

Fow instance, a fowmat with uncompwessed 10-bit Bayew components
awwanged in a wed, gween, gween, bwue pattewn twansfewwed as 2 8-bit
sampwes pew pixew with the weast significant bits twansfewwed fiwst wiww
be named ``MEDIA_BUS_FMT_SWGGB10_2X8_PADHI_WE``.


.. _bayew-pattewns:

.. kewnew-figuwe:: bayew.svg
    :awt:    bayew.svg
    :awign:  centew

    **Figuwe 4.8 Bayew Pattewns**

The fowwowing tabwe wists existing packed Bayew fowmats. The data
owganization is given as an exampwe fow the fiwst pixew onwy.


.. HACK: ideawwy, we wouwd be using adjustbox hewe. Howevew, Sphinx
.. is a vewy bad behaviowed guy: if the tabwe has mowe than 30 cows,
.. it switches to wong tabwe, and thewe's no way to ovewwide it.


.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{6.0cm}|p{0.7cm}|p{0.3cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _v4w2-mbus-pixewcode-bayew:

.. csscwass: wongtabwe

.. fwat-tabwe:: Bayew Fowmats
    :headew-wows:  2
    :stub-cowumns: 0

    * - Identifiew
      - Code
      -
      - :cspan:`15` Data owganization
    * -
      -
      - Bit
      - 15
      - 14
      - 13
      - 12
      - 11
      - 10
      - 9
      - 8
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-SBGGW8-1X8:

      - MEDIA_BUS_FMT_SBGGW8_1X8
      - 0x3001
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGBWG8-1X8:

      - MEDIA_BUS_FMT_SGBWG8_1X8
      - 0x3013
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGWBG8-1X8:

      - MEDIA_BUS_FMT_SGWBG8_1X8
      - 0x3002
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SWGGB8-1X8:

      - MEDIA_BUS_FMT_SWGGB8_1X8
      - 0x3014
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SBGGW10-AWAW8-1X8:

      - MEDIA_BUS_FMT_SBGGW10_AWAW8_1X8
      - 0x3015
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGBWG10-AWAW8-1X8:

      - MEDIA_BUS_FMT_SGBWG10_AWAW8_1X8
      - 0x3016
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGWBG10-AWAW8-1X8:

      - MEDIA_BUS_FMT_SGWBG10_AWAW8_1X8
      - 0x3017
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SWGGB10-AWAW8-1X8:

      - MEDIA_BUS_FMT_SWGGB10_AWAW8_1X8
      - 0x3018
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SBGGW10-DPCM8-1X8:

      - MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8
      - 0x300b
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGBWG10-DPCM8-1X8:

      - MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8
      - 0x300c
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGWBG10-DPCM8-1X8:

      - MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8
      - 0x3009
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SWGGB10-DPCM8-1X8:

      - MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8
      - 0x300d
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SBGGW10-2X8-PADHI-BE:

      - MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_BE
      - 0x3003
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
      - b\ :sub:`9`
      - b\ :sub:`8`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SBGGW10-2X8-PADHI-WE:

      - MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE
      - 0x3004
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
      - b\ :sub:`9`
      - b\ :sub:`8`
    * .. _MEDIA-BUS-FMT-SBGGW10-2X8-PADWO-BE:

      - MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_BE
      - 0x3005
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`1`
      - b\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
    * .. _MEDIA-BUS-FMT-SBGGW10-2X8-PADWO-WE:

      - MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_WE
      - 0x3006
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`1`
      - b\ :sub:`0`
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
    * .. _MEDIA-BUS-FMT-SBGGW10-1X10:

      - MEDIA_BUS_FMT_SBGGW10_1X10
      - 0x3007
      -
      -
      -
      -
      -
      -
      -
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGBWG10-1X10:

      - MEDIA_BUS_FMT_SGBWG10_1X10
      - 0x300e
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGWBG10-1X10:

      - MEDIA_BUS_FMT_SGWBG10_1X10
      - 0x300a
      -
      -
      -
      -
      -
      -
      -
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SWGGB10-1X10:

      - MEDIA_BUS_FMT_SWGGB10_1X10
      - 0x300f
      -
      -
      -
      -
      -
      -
      -
      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SBGGW12-1X12:

      - MEDIA_BUS_FMT_SBGGW12_1X12
      - 0x3008
      -
      -
      -
      -
      -
      - b\ :sub:`11`
      - b\ :sub:`10`
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGBWG12-1X12:

      - MEDIA_BUS_FMT_SGBWG12_1X12
      - 0x3010
      -
      -
      -
      -
      -
      - g\ :sub:`11`
      - g\ :sub:`10`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGWBG12-1X12:

      - MEDIA_BUS_FMT_SGWBG12_1X12
      - 0x3011
      -
      -
      -
      -
      -
      - g\ :sub:`11`
      - g\ :sub:`10`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SWGGB12-1X12:

      - MEDIA_BUS_FMT_SWGGB12_1X12
      - 0x3012
      -
      -
      -
      -
      -
      - w\ :sub:`11`
      - w\ :sub:`10`
      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SBGGW14-1X14:

      - MEDIA_BUS_FMT_SBGGW14_1X14
      - 0x3019
      -
      -
      -
      - b\ :sub:`13`
      - b\ :sub:`12`
      - b\ :sub:`11`
      - b\ :sub:`10`
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGBWG14-1X14:

      - MEDIA_BUS_FMT_SGBWG14_1X14
      - 0x301a
      -
      -
      -
      - g\ :sub:`13`
      - g\ :sub:`12`
      - g\ :sub:`11`
      - g\ :sub:`10`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGWBG14-1X14:

      - MEDIA_BUS_FMT_SGWBG14_1X14
      - 0x301b
      -
      -
      -
      - g\ :sub:`13`
      - g\ :sub:`12`
      - g\ :sub:`11`
      - g\ :sub:`10`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SWGGB14-1X14:

      - MEDIA_BUS_FMT_SWGGB14_1X14
      - 0x301c
      -
      -
      -
      - w\ :sub:`13`
      - w\ :sub:`12`
      - w\ :sub:`11`
      - w\ :sub:`10`
      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SBGGW16-1X16:

      - MEDIA_BUS_FMT_SBGGW16_1X16
      - 0x301d
      -
      - b\ :sub:`15`
      - b\ :sub:`14`
      - b\ :sub:`13`
      - b\ :sub:`12`
      - b\ :sub:`11`
      - b\ :sub:`10`
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGBWG16-1X16:

      - MEDIA_BUS_FMT_SGBWG16_1X16
      - 0x301e
      -
      - g\ :sub:`15`
      - g\ :sub:`14`
      - g\ :sub:`13`
      - g\ :sub:`12`
      - g\ :sub:`11`
      - g\ :sub:`10`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SGWBG16-1X16:

      - MEDIA_BUS_FMT_SGWBG16_1X16
      - 0x301f
      -
      - g\ :sub:`15`
      - g\ :sub:`14`
      - g\ :sub:`13`
      - g\ :sub:`12`
      - g\ :sub:`11`
      - g\ :sub:`10`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
    * .. _MEDIA-BUS-FMT-SWGGB16-1X16:

      - MEDIA_BUS_FMT_SWGGB16_1X16
      - 0x3020
      -
      - w\ :sub:`15`
      - w\ :sub:`14`
      - w\ :sub:`13`
      - w\ :sub:`12`
      - w\ :sub:`11`
      - w\ :sub:`10`
      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`

.. waw:: watex

    \endgwoup


Packed YUV Fowmats
^^^^^^^^^^^^^^^^^^

Those data fowmats twansfew pixew data as (possibwy downsampwed) Y, U
and V components. Some fowmats incwude dummy bits in some of theiw
sampwes and awe cowwectivewy wefewwed to as "YDYC" (Y-Dummy-Y-Chwoma)
fowmats. One cannot wewy on the vawues of these dummy bits as those awe
undefined.

The fowmat code is made of the fowwowing infowmation.

-  The Y, U and V components owdew code, as twansfewwed on the bus.
   Possibwe vawues awe YUYV, UYVY, YVYU and VYUY fow fowmats with no
   dummy bit, and YDYUYDYV, YDYVYDYU, YUYDYVYD and YVYDYUYD fow YDYC
   fowmats.

-  The numbew of bits pew pixew component. Aww components awe
   twansfewwed on the same numbew of bits. Common vawues awe 8, 10 and
   12.

-  The numbew of bus sampwes pew pixew. Pixews that awe widew than the
   bus width must be twansfewwed in muwtipwe sampwes. Common vawues awe
   0.5 (encoded as 0_5; in this case two pixews awe twansfewwed pew bus
   sampwe), 1, 1.5 (encoded as 1_5) and 2.

-  The bus width. When the bus width is wawgew than the numbew of bits
   pew pixew component, sevewaw components awe packed in a singwe bus
   sampwe. The components awe owdewed as specified by the owdew code,
   with components on the weft of the code twansfewwed in the high owdew
   bits. Common vawues awe 8 and 16.

Fow instance, a fowmat whewe pixews awe encoded as 8-bit YUV vawues
downsampwed to 4:2:2 and twansfewwed as 2 8-bit bus sampwes pew pixew in
the U, Y, V, Y owdew wiww be named ``MEDIA_BUS_FMT_UYVY8_2X8``.

:wef:`v4w2-mbus-pixewcode-yuv8` wists existing packed YUV fowmats and
descwibes the owganization of each pixew data in each sampwe. When a
fowmat pattewn is spwit acwoss muwtipwe sampwes each of the sampwes in
the pattewn is descwibed.

The wowe of each bit twansfewwed ovew the bus is identified by one of
the fowwowing codes.

-  y\ :sub:`x` fow wuma component bit numbew x

-  u\ :sub:`x` fow bwue chwoma component bit numbew x

-  v\ :sub:`x` fow wed chwoma component bit numbew x

-  a\ :sub:`x` fow awpha component bit numbew x

- fow non-avaiwabwe bits (fow positions highew than the bus width)

-  d fow dummy bits

.. HACK: ideawwy, we wouwd be using adjustbox hewe. Howevew, this
.. wiww nevew wowk fow this tabwe, as, even with tiny font, it is
.. to big fow a singwe page. So, we need to manuawwy adjust the
.. size.

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{5.0cm}|p{0.7cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _v4w2-mbus-pixewcode-yuv8:

.. fwat-tabwe:: YUV Fowmats
    :headew-wows:  2
    :stub-cowumns: 0
    :widths: 36 7 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

    * - Identifiew
      - Code
      -
      - :cspan:`31` Data owganization
    * -
      -
      - Bit
      - 31
      - 30
      - 29
      - 28
      - 27
      - 26
      - 25
      - 24
      - 23
      - 22
      - 21
      - 10
      - 19
      - 18
      - 17
      - 16
      - 15
      - 14
      - 13
      - 12
      - 11
      - 10
      - 9
      - 8
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-Y8-1X8:

      - MEDIA_BUS_FMT_Y8_1X8
      - 0x2001
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UV8-1X8:

      - MEDIA_BUS_FMT_UV8_1X8
      - 0x2015
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYVY8-1_5X8:

      - MEDIA_BUS_FMT_UYVY8_1_5X8
      - 0x2002
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-VYUY8-1_5X8:

      - MEDIA_BUS_FMT_VYUY8_1_5X8
      - 0x2003
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUYV8-1_5X8:

      - MEDIA_BUS_FMT_YUYV8_1_5X8
      - 0x2004
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YVYU8-1_5X8:

      - MEDIA_BUS_FMT_YVYU8_1_5X8
      - 0x2005
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYVY8-2X8:

      - MEDIA_BUS_FMT_UYVY8_2X8
      - 0x2006
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-VYUY8-2X8:

      - MEDIA_BUS_FMT_VYUY8_2X8
      - 0x2007
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUYV8-2X8:

      - MEDIA_BUS_FMT_YUYV8_2X8
      - 0x2008
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YVYU8-2X8:

      - MEDIA_BUS_FMT_YVYU8_2X8
      - 0x2009
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * .. _MEDIA-BUS-FMT-Y10-1X10:

      - MEDIA_BUS_FMT_Y10_1X10
      - 0x200a
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-Y10-2X8-PADHI_WE:

      - MEDIA_BUS_FMT_Y10_2X8_PADHI_WE
      - 0x202c
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 0
      - 0
      - 0
      - 0
      - 0
      - 0
      - y\ :sub:`9`
      - y\ :sub:`8`
    * .. _MEDIA-BUS-FMT-UYVY10-2X10:

      - MEDIA_BUS_FMT_UYVY10_2X10
      - 0x2018
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-VYUY10-2X10:

      - MEDIA_BUS_FMT_VYUY10_2X10
      - 0x2019
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUYV10-2X10:

      - MEDIA_BUS_FMT_YUYV10_2X10
      - 0x200b
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YVYU10-2X10:

      - MEDIA_BUS_FMT_YVYU10_2X10
      - 0x200c
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * .. _MEDIA-BUS-FMT-Y12-1X12:

      - MEDIA_BUS_FMT_Y12_1X12
      - 0x2013
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYVY12-2X12:

      - MEDIA_BUS_FMT_UYVY12_2X12
      - 0x201c
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-VYUY12-2X12:

      - MEDIA_BUS_FMT_VYUY12_2X12
      - 0x201d
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUYV12-2X12:

      - MEDIA_BUS_FMT_YUYV12_2X12
      - 0x201e
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YVYU12-2X12:

      - MEDIA_BUS_FMT_YVYU12_2X12
      - 0x201f
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * .. _MEDIA-BUS-FMT-Y14-1X14:

      - MEDIA_BUS_FMT_Y14_1X14
      - 0x202d
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`13`
      - y\ :sub:`12`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-Y16-1X16:

      - MEDIA_BUS_FMT_Y16_1X16
      - 0x202e
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`15`
      - y\ :sub:`14`
      - y\ :sub:`13`
      - y\ :sub:`12`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYVY8-1X16:

      - MEDIA_BUS_FMT_UYVY8_1X16
      - 0x200f
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-VYUY8-1X16:

      - MEDIA_BUS_FMT_VYUY8_1X16
      - 0x2010
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUYV8-1X16:

      - MEDIA_BUS_FMT_YUYV8_1X16
      - 0x2011
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YVYU8-1X16:

      - MEDIA_BUS_FMT_YVYU8_1X16
      - 0x2012
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YDYUYDYV8-1X16:

      - MEDIA_BUS_FMT_YDYUYDYV8_1X16
      - 0x2014
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - d
      - d
      - d
      - d
      - d
      - d
      - d
      - d
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - d
      - d
      - d
      - d
      - d
      - d
      - d
      - d
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYVY10-1X20:

      - MEDIA_BUS_FMT_UYVY10_1X20
      - 0x201a
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-VYUY10-1X20:

      - MEDIA_BUS_FMT_VYUY10_1X20
      - 0x201b
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUYV10-1X20:

      - MEDIA_BUS_FMT_YUYV10_1X20
      - 0x200d
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YVYU10-1X20:

      - MEDIA_BUS_FMT_YVYU10_1X20
      - 0x200e
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * .. _MEDIA-BUS-FMT-VUY8-1X24:

      - MEDIA_BUS_FMT_VUY8_1X24
      - 0x201a
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUV8-1X24:

      - MEDIA_BUS_FMT_YUV8_1X24
      - 0x2025
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYYVYY8-0-5X24:

      - MEDIA_BUS_FMT_UYYVYY8_0_5X24
      - 0x2026
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYVY12-1X24:

      - MEDIA_BUS_FMT_UYVY12_1X24
      - 0x2020
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-VYUY12-1X24:

      - MEDIA_BUS_FMT_VYUY12_1X24
      - 0x2021
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUYV12-1X24:

      - MEDIA_BUS_FMT_YUYV12_1X24
      - 0x2022
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YVYU12-1X24:

      - MEDIA_BUS_FMT_YVYU12_1X24
      - 0x2023
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUV10-1X30:

      - MEDIA_BUS_FMT_YUV10_1X30
      - 0x2016
      -
      -
      -
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYYVYY10-0-5X30:

      - MEDIA_BUS_FMT_UYYVYY10_0_5X30
      - 0x2027
      -
      -
      -
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-AYUV8-1X32:

      - MEDIA_BUS_FMT_AYUV8_1X32
      - 0x2017
      -
      - a\ :sub:`7`
      - a\ :sub:`6`
      - a\ :sub:`5`
      - a\ :sub:`4`
      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`


.. waw:: watex

	\endgwoup


The fowwowing tabwe wist existing packed 36bit wide YUV fowmats.

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{4.1cm}|p{0.7cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _v4w2-mbus-pixewcode-yuv8-36bit:

.. fwat-tabwe:: 36bit YUV Fowmats
    :headew-wows:  2
    :stub-cowumns: 0
    :widths: 36 7 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

    * - Identifiew
      - Code
      -
      - :cspan:`35` Data owganization
    * -
      -
      - Bit
      - 35
      - 34
      - 33
      - 32
      - 31
      - 30
      - 29
      - 28
      - 27
      - 26
      - 25
      - 24
      - 23
      - 22
      - 21
      - 10
      - 19
      - 18
      - 17
      - 16
      - 15
      - 14
      - 13
      - 12
      - 11
      - 10
      - 9
      - 8
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-UYYVYY12-0-5X36:

      - MEDIA_BUS_FMT_UYYVYY12_0_5X36
      - 0x2028
      -
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * .. _MEDIA-BUS-FMT-YUV12-1X36:

      - MEDIA_BUS_FMT_YUV12_1X36
      - 0x2029
      -
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`


.. waw:: watex

	\endgwoup


The fowwowing tabwe wist existing packed 48bit wide YUV fowmats.

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{5.6cm}|p{0.7cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _v4w2-mbus-pixewcode-yuv8-48bit:

.. fwat-tabwe:: 48bit YUV Fowmats
    :headew-wows:  3
    :stub-cowumns: 0
    :widths: 36 7 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

    * - Identifiew
      - Code
      -
      - :cspan:`31` Data owganization
    * -
      -
      - Bit
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - 47
      - 46
      - 45
      - 44
      - 43
      - 42
      - 41
      - 40
      - 39
      - 38
      - 37
      - 36
      - 35
      - 34
      - 33
      - 32
    * -
      -
      -
      - 31
      - 30
      - 29
      - 28
      - 27
      - 26
      - 25
      - 24
      - 23
      - 22
      - 21
      - 10
      - 19
      - 18
      - 17
      - 16
      - 15
      - 14
      - 13
      - 12
      - 11
      - 10
      - 9
      - 8
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-YUV16-1X48:

      - MEDIA_BUS_FMT_YUV16_1X48
      - 0x202a
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - y\ :sub:`15`
      - y\ :sub:`14`
      - y\ :sub:`13`
      - y\ :sub:`12`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`8`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      - u\ :sub:`15`
      - u\ :sub:`14`
      - u\ :sub:`13`
      - u\ :sub:`12`
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
      - v\ :sub:`15`
      - v\ :sub:`14`
      - v\ :sub:`13`
      - v\ :sub:`12`
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _MEDIA-BUS-FMT-UYYVYY16-0-5X48:

      - MEDIA_BUS_FMT_UYYVYY16_0_5X48
      - 0x202b
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - u\ :sub:`15`
      - u\ :sub:`14`
      - u\ :sub:`13`
      - u\ :sub:`12`
      - u\ :sub:`11`
      - u\ :sub:`10`
      - u\ :sub:`9`
      - u\ :sub:`8`
      - u\ :sub:`7`
      - u\ :sub:`6`
      - u\ :sub:`5`
      - u\ :sub:`4`
      - u\ :sub:`3`
      - u\ :sub:`2`
      - u\ :sub:`1`
      - u\ :sub:`0`
    * -
      -
      -
      - y\ :sub:`15`
      - y\ :sub:`14`
      - y\ :sub:`13`
      - y\ :sub:`12`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - y\ :sub:`15`
      - y\ :sub:`14`
      - y\ :sub:`13`
      - y\ :sub:`12`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`8`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
    * -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      -
      - v\ :sub:`15`
      - v\ :sub:`14`
      - v\ :sub:`13`
      - v\ :sub:`12`
      - v\ :sub:`11`
      - v\ :sub:`10`
      - v\ :sub:`9`
      - v\ :sub:`8`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * -
      -
      -
      - y\ :sub:`15`
      - y\ :sub:`14`
      - y\ :sub:`13`
      - y\ :sub:`12`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`9`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`
      - y\ :sub:`15`
      - y\ :sub:`14`
      - y\ :sub:`13`
      - y\ :sub:`12`
      - y\ :sub:`11`
      - y\ :sub:`10`
      - y\ :sub:`8`
      - y\ :sub:`8`
      - y\ :sub:`7`
      - y\ :sub:`6`
      - y\ :sub:`5`
      - y\ :sub:`4`
      - y\ :sub:`3`
      - y\ :sub:`2`
      - y\ :sub:`1`
      - y\ :sub:`0`


.. waw:: watex

	\endgwoup

HSV/HSW Fowmats
^^^^^^^^^^^^^^^

Those fowmats twansfew pixew data as WGB vawues in a
cywindwicaw-coowdinate system using Hue-Satuwation-Vawue ow
Hue-Satuwation-Wightness components. The fowmat code is made of the
fowwowing infowmation.

-  The hue, satuwation, vawue ow wightness and optionaw awpha components
   owdew code, as encoded in a pixew sampwe. The onwy cuwwentwy
   suppowted vawue is AHSV.

-  The numbew of bits pew component, fow each component. The vawues can
   be diffewent fow aww components. The onwy cuwwentwy suppowted vawue
   is 8888.

-  The numbew of bus sampwes pew pixew. Pixews that awe widew than the
   bus width must be twansfewwed in muwtipwe sampwes. The onwy cuwwentwy
   suppowted vawue is 1.

-  The bus width.

-  Fow fowmats whewe the totaw numbew of bits pew pixew is smawwew than
   the numbew of bus sampwes pew pixew times the bus width, a padding
   vawue stating if the bytes awe padded in theiw most high owdew bits
   (PADHI) ow wow owdew bits (PADWO).

-  Fow fowmats whewe the numbew of bus sampwes pew pixew is wawgew than
   1, an endianness vawue stating if the pixew is twansfewwed MSB fiwst
   (BE) ow WSB fiwst (WE).

The fowwowing tabwe wists existing HSV/HSW fowmats.


.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{3.9cm}|p{0.73cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _v4w2-mbus-pixewcode-hsv:

.. fwat-tabwe:: HSV/HSW fowmats
    :headew-wows:  2
    :stub-cowumns: 0
    :widths: 28 7 3 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

    * - Identifiew
      - Code
      -
      - :cspan:`31` Data owganization
    * -
      -
      - Bit
      - 31
      - 30
      - 29
      - 28
      - 27
      - 26
      - 25
      - 24
      - 23
      - 22
      - 21
      - 20
      - 19
      - 18
      - 17
      - 16
      - 15
      - 14
      - 13
      - 12
      - 11
      - 10
      - 9
      - 8
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _MEDIA-BUS-FMT-AHSV8888-1X32:

      - MEDIA_BUS_FMT_AHSV8888_1X32
      - 0x6001
      -
      - a\ :sub:`7`
      - a\ :sub:`6`
      - a\ :sub:`5`
      - a\ :sub:`4`
      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`
      - h\ :sub:`7`
      - h\ :sub:`6`
      - h\ :sub:`5`
      - h\ :sub:`4`
      - h\ :sub:`3`
      - h\ :sub:`2`
      - h\ :sub:`1`
      - h\ :sub:`0`
      - s\ :sub:`7`
      - s\ :sub:`6`
      - s\ :sub:`5`
      - s\ :sub:`4`
      - s\ :sub:`3`
      - s\ :sub:`2`
      - s\ :sub:`1`
      - s\ :sub:`0`
      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`

.. waw:: watex

    \endgwoup


JPEG Compwessed Fowmats
^^^^^^^^^^^^^^^^^^^^^^^

Those data fowmats consist of an owdewed sequence of 8-bit bytes
obtained fwom JPEG compwession pwocess. Additionawwy to the ``_JPEG``
postfix the fowmat code is made of the fowwowing infowmation.

-  The numbew of bus sampwes pew entwopy encoded byte.

-  The bus width.

Fow instance, fow a JPEG basewine pwocess and an 8-bit bus width the
fowmat wiww be named ``MEDIA_BUS_FMT_JPEG_1X8``.

The fowwowing tabwe wists existing JPEG compwessed fowmats.


.. _v4w2-mbus-pixewcode-jpeg:

.. tabuwawcowumns:: |p{6.0cm}|p{1.4cm}|p{9.9cm}|

.. fwat-tabwe:: JPEG Fowmats
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Wemawks
    * .. _MEDIA-BUS-FMT-JPEG-1X8:

      - MEDIA_BUS_FMT_JPEG_1X8
      - 0x4001
      - Besides of its usage fow the pawawwew bus this fowmat is
	wecommended fow twansmission of JPEG data ovew MIPI CSI bus using
	the Usew Defined 8-bit Data types.



.. _v4w2-mbus-vendow-spec-fmts:

Vendow and Device Specific Fowmats
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This section wists compwex data fowmats that awe eithew vendow ow device
specific.

The fowwowing tabwe wists the existing vendow and device specific
fowmats.


.. _v4w2-mbus-pixewcode-vendow-specific:

.. tabuwawcowumns:: |p{8.0cm}|p{1.4cm}|p{7.9cm}|

.. fwat-tabwe:: Vendow and device specific fowmats
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Comments
    * .. _MEDIA-BUS-FMT-S5C-UYVY-JPEG-1X8:

      - MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8
      - 0x5001
      - Intewweaved waw UYVY and JPEG image fowmat with embedded meta-data
	used by Samsung S3C73MX camewa sensows.

.. _v4w2-mbus-metadata-fmts:

Metadata Fowmats
^^^^^^^^^^^^^^^^

This section wists aww metadata fowmats.

The fowwowing tabwe wists the existing metadata fowmats.

.. tabuwawcowumns:: |p{8.0cm}|p{1.4cm}|p{7.9cm}|

.. fwat-tabwe:: Metadata fowmats
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Comments
    * .. _MEDIA-BUS-FMT-METADATA-FIXED:

      - MEDIA_BUS_FMT_METADATA_FIXED
      - 0x7001
      - This fowmat shouwd be used when the same dwivew handwes
	both sides of the wink and the bus fowmat is a fixed
	metadata fowmat that is not configuwabwe fwom usewspace.
	Width and height wiww be set to 0 fow this fowmat.
