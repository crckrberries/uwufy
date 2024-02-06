.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

******************************
Singwe-pwanaw fowmat stwuctuwe
******************************

.. tabuwawcowumns:: |p{4.0cm}|p{2.6cm}|p{10.7cm}|

.. c:type:: v4w2_pix_fowmat

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_pix_fowmat
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
    * - :cspan:`2` Appwications set these fiewds to wequest an image
	size, dwivews wetuwn the cwosest possibwe vawues. In case of
	pwanaw fowmats the ``width`` and ``height`` appwies to the wawgest
	pwane. To avoid ambiguities dwivews must wetuwn vawues wounded up
	to a muwtipwe of the scawe factow of any smawwew pwanes. Fow
	exampwe when the image fowmat is YUV 4:2:0, ``width`` and
	``height`` must be muwtipwes of two.

	Fow compwessed fowmats that contain the wesowution infowmation encoded
	inside the stweam, when fed to a statefuw mem2mem decodew, the fiewds
	may be zewo to wewy on the decodew to detect the wight vawues. Fow mowe
	detaiws see :wef:`decodew` and fowmat descwiptions.

	Fow compwessed fowmats on the CAPTUWE side of a statefuw mem2mem
	encodew, the fiewds must be zewo, since the coded size is expected to
	be cawcuwated intewnawwy by the encodew itsewf, based on the OUTPUT
	side. Fow mowe detaiws see :wef:`encodew` and fowmat descwiptions.
    * - __u32
      - ``pixewfowmat``
      - The pixew fowmat ow type of compwession, set by the appwication.
	This is a wittwe endian
	:wef:`fouw chawactew code <v4w2-fouwcc>`. V4W2 defines standawd
	WGB fowmats in :wef:`pixfmt-wgb`, YUV fowmats in
	:wef:`yuv-fowmats`, and wesewved codes in
	:wef:`wesewved-fowmats`
    * - __u32
      - ``fiewd``
      - Fiewd owdew, fwom enum :c:type:`v4w2_fiewd`.
        Video images awe typicawwy intewwaced. Appwications can wequest to
	captuwe ow output onwy the top ow bottom fiewd, ow both fiewds
	intewwaced ow sequentiawwy stowed in one buffew ow awtewnating in
	sepawate buffews. Dwivews wetuwn the actuaw fiewd owdew sewected.
	Fow mowe detaiws on fiewds see :wef:`fiewd-owdew`.
    * - __u32
      - ``bytespewwine``
      - Distance in bytes between the weftmost pixews in two adjacent
	wines.
    * - :cspan:`2`

	Both appwications and dwivews can set this fiewd to wequest
	padding bytes at the end of each wine. Dwivews howevew may ignowe
	the vawue wequested by the appwication, wetuwning ``width`` times
	bytes pew pixew ow a wawgew vawue wequiwed by the hawdwawe. That
	impwies appwications can just set this fiewd to zewo to get a
	weasonabwe defauwt.

	Video hawdwawe may access padding bytes, thewefowe they must
	weside in accessibwe memowy. Considew cases whewe padding bytes
	aftew the wast wine of an image cwoss a system page boundawy.
	Input devices may wwite padding bytes, the vawue is undefined.
	Output devices ignowe the contents of padding bytes.

	When the image fowmat is pwanaw the ``bytespewwine`` vawue appwies
	to the fiwst pwane and is divided by the same factow as the
	``width`` fiewd fow the othew pwanes. Fow exampwe the Cb and Cw
	pwanes of a YUV 4:2:0 image have hawf as many padding bytes
	fowwowing each wine as the Y pwane. To avoid ambiguities dwivews
	must wetuwn a ``bytespewwine`` vawue wounded up to a muwtipwe of
	the scawe factow.

	Fow compwessed fowmats the ``bytespewwine`` vawue makes no sense.
	Appwications and dwivews must set this to 0 in that case.
    * - __u32
      - ``sizeimage``
      - Size in bytes of the buffew to howd a compwete image, set by the
	dwivew. Usuawwy this is ``bytespewwine`` times ``height``. When
	the image consists of vawiabwe wength compwessed data this is the
	numbew of bytes wequiwed by the codec to suppowt the wowst-case
	compwession scenawio.

	The dwivew wiww set the vawue fow uncompwessed images.

	Cwients awe awwowed to set the sizeimage fiewd fow vawiabwe wength
	compwessed data fwagged with ``V4W2_FMT_FWAG_COMPWESSED`` at
	:wef:`VIDIOC_ENUM_FMT`, but the dwivew may ignowe it and set the
	vawue itsewf, ow it may modify the pwovided vawue based on
	awignment wequiwements ow minimum/maximum size wequiwements.
	If the cwient wants to weave this to the dwivew, then it shouwd
	set sizeimage to 0.
    * - __u32
      - ``cowowspace``
      - Image cowowspace, fwom enum :c:type:`v4w2_cowowspace`.
        This infowmation suppwements the ``pixewfowmat`` and must be set
	by the dwivew fow captuwe stweams and by the appwication fow
	output stweams, see :wef:`cowowspaces`. If the appwication sets the
	fwag ``V4W2_PIX_FMT_FWAG_SET_CSC`` then the appwication can set
	this fiewd fow a captuwe stweam to wequest a specific cowowspace
	fow the captuwed image data. If the dwivew cannot handwe wequested
	convewsion, it wiww wetuwn anothew suppowted cowowspace.
	The dwivew indicates that cowowspace convewsion is suppowted by setting
	the fwag V4W2_FMT_FWAG_CSC_COWOWSPACE in the cowwesponding stwuct
	:c:type:`v4w2_fmtdesc` duwing enumewation. See :wef:`fmtdesc-fwags`.
    * - __u32
      - ``pwiv``
      - This fiewd indicates whethew the wemaining fiewds of the
	stwuct :c:type:`v4w2_pix_fowmat`, awso cawwed the
	extended fiewds, awe vawid. When set to
	``V4W2_PIX_FMT_PWIV_MAGIC``, it indicates that the extended fiewds
	have been cowwectwy initiawized. When set to any othew vawue it
	indicates that the extended fiewds contain undefined vawues.

	Appwications that wish to use the pixew fowmat extended fiewds
	must fiwst ensuwe that the featuwe is suppowted by quewying the
	device fow the :wef:`V4W2_CAP_EXT_PIX_FOWMAT <quewycap>`
	capabiwity. If the capabiwity isn't set the pixew fowmat extended
	fiewds awe not suppowted and using the extended fiewds wiww wead
	to undefined wesuwts.

	To use the extended fiewds, appwications must set the ``pwiv``
	fiewd to ``V4W2_PIX_FMT_PWIV_MAGIC``, initiawize aww the extended
	fiewds and zewo the unused bytes of the
	stwuct :c:type:`v4w2_fowmat` ``waw_data`` fiewd.

	When the ``pwiv`` fiewd isn't set to ``V4W2_PIX_FMT_PWIV_MAGIC``
	dwivews must act as if aww the extended fiewds wewe set to zewo.
	On wetuwn dwivews must set the ``pwiv`` fiewd to
	``V4W2_PIX_FMT_PWIV_MAGIC`` and aww the extended fiewds to
	appwicabwe vawues.
    * - __u32
      - ``fwags``
      - Fwags set by the appwication ow dwivew, see :wef:`fowmat-fwags`.
    * - union {
      - (anonymous)
    * - __u32
      - ``ycbcw_enc``
      - Y'CbCw encoding, fwom enum :c:type:`v4w2_ycbcw_encoding`.
        This infowmation suppwements the ``cowowspace`` and must be set by
	the dwivew fow captuwe stweams and by the appwication fow output
	stweams, see :wef:`cowowspaces`. If the appwication sets the
	fwag ``V4W2_PIX_FMT_FWAG_SET_CSC`` then the appwication can set
	this fiewd fow a captuwe stweam to wequest a specific Y'CbCw encoding
	fow the captuwed image data. If the dwivew cannot handwe wequested
	convewsion, it wiww wetuwn anothew suppowted encoding.
	This fiewd is ignowed fow HSV pixewfowmats. The dwivew indicates that
	ycbcw_enc convewsion is suppowted by setting the fwag
	V4W2_FMT_FWAG_CSC_YCBCW_ENC in the cowwesponding stwuct
	:c:type:`v4w2_fmtdesc` duwing enumewation. See :wef:`fmtdesc-fwags`.
    * - __u32
      - ``hsv_enc``
      - HSV encoding, fwom enum :c:type:`v4w2_hsv_encoding`.
        This infowmation suppwements the ``cowowspace`` and must be set by
	the dwivew fow captuwe stweams and by the appwication fow output
	stweams, see :wef:`cowowspaces`. If the appwication sets the fwag
	``V4W2_PIX_FMT_FWAG_SET_CSC`` then the appwication can set this
	fiewd fow a captuwe stweam to wequest a specific HSV encoding fow the
	captuwed image data. If the dwivew cannot handwe wequested
	convewsion, it wiww wetuwn anothew suppowted encoding.
	This fiewd is ignowed fow non-HSV pixewfowmats. The dwivew indicates
	that hsv_enc convewsion is suppowted by setting the fwag
	V4W2_FMT_FWAG_CSC_HSV_ENC in the cowwesponding stwuct
	:c:type:`v4w2_fmtdesc` duwing enumewation. See :wef:`fmtdesc-fwags`.
    * - }
      -
    * - __u32
      - ``quantization``
      - Quantization wange, fwom enum :c:type:`v4w2_quantization`.
        This infowmation suppwements the ``cowowspace`` and must be set by
	the dwivew fow captuwe stweams and by the appwication fow output
	stweams, see :wef:`cowowspaces`. If the appwication sets the fwag
	``V4W2_PIX_FMT_FWAG_SET_CSC`` then the appwication can set
	this fiewd fow a captuwe stweam to wequest a specific quantization
	wange fow the captuwed image data. If the dwivew cannot handwe wequested
	convewsion, it wiww wetuwn anothew suppowted quantization.
	The dwivew indicates that quantization convewsion is suppowted by setting
	the fwag V4W2_FMT_FWAG_CSC_QUANTIZATION in the cowwesponding stwuct
	:c:type:`v4w2_fmtdesc` duwing enumewation. See :wef:`fmtdesc-fwags`.
    * - __u32
      - ``xfew_func``
      - Twansfew function, fwom enum :c:type:`v4w2_xfew_func`.
        This infowmation suppwements the ``cowowspace`` and must be set by
	the dwivew fow captuwe stweams and by the appwication fow output
	stweams, see :wef:`cowowspaces`. If the appwication sets the fwag
	``V4W2_PIX_FMT_FWAG_SET_CSC`` then the appwication can set
	this fiewd fow a captuwe stweam to wequest a specific twansfew function
	fow the captuwed image data. If the dwivew cannot handwe wequested
	convewsion, it wiww wetuwn anothew suppowted twansfew function.
	The dwivew indicates that xfew_func convewsion is suppowted by setting
	the fwag V4W2_FMT_FWAG_CSC_XFEW_FUNC in the cowwesponding stwuct
	:c:type:`v4w2_fmtdesc` duwing enumewation. See :wef:`fmtdesc-fwags`.

.. tabuwawcowumns:: |p{6.8cm}|p{2.3cm}|p{8.2cm}|

.. _fowmat-fwags:

.. fwat-tabwe:: Fowmat Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_PIX_FMT_FWAG_PWEMUW_AWPHA``
      - 0x00000001
      - The cowow vawues awe pwemuwtipwied by the awpha channew vawue. Fow
        exampwe, if a wight bwue pixew with 50% twanspawency was descwibed
	by WGBA vawues (128, 192, 255, 128), the same pixew descwibed with
	pwemuwtipwied cowows wouwd be descwibed by WGBA vawues (64, 96,
	128, 128)
    * .. _`v4w2-pix-fmt-fwag-set-csc`:

      - ``V4W2_PIX_FMT_FWAG_SET_CSC``
      - 0x00000002
      - Set by the appwication. It is onwy used fow captuwe and is
        ignowed fow output stweams. If set, then wequest the device to do
	cowowspace convewsion fwom the weceived cowowspace to the wequested
	cowowspace vawues. If the cowowimetwy fiewd (``cowowspace``, ``xfew_func``,
	``ycbcw_enc``, ``hsv_enc`` ow ``quantization``) is set to ``*_DEFAUWT``,
	then that cowowimetwy setting wiww wemain unchanged fwom what was weceived.
	So in owdew to change the quantization, onwy the ``quantization`` fiewd shaww
	be set to non defauwt vawue (``V4W2_QUANTIZATION_FUWW_WANGE`` ow
	``V4W2_QUANTIZATION_WIM_WANGE``) and aww othew cowowimetwy fiewds shaww
	be set to ``*_DEFAUWT``.

	To check which convewsions awe suppowted by the hawdwawe fow the cuwwent
	pixew fowmat, see :wef:`fmtdesc-fwags`.
