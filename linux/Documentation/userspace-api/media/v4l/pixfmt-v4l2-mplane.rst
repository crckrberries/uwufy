.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

******************************
Muwti-pwanaw fowmat stwuctuwes
******************************

The stwuct :c:type:`v4w2_pwane_pix_fowmat` stwuctuwes define size
and wayout fow each of the pwanes in a muwti-pwanaw fowmat. The
stwuct :c:type:`v4w2_pix_fowmat_mpwane` stwuctuwe contains
infowmation common to aww pwanes (such as image width and height) and an
awway of stwuct :c:type:`v4w2_pwane_pix_fowmat` stwuctuwes,
descwibing aww pwanes of that fowmat.



.. tabuwawcowumns:: |p{1.4cm}|p{4.0cm}|p{11.9cm}|

.. c:type:: v4w2_pwane_pix_fowmat

.. fwat-tabwe:: stwuct v4w2_pwane_pix_fowmat
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``sizeimage``
      - Maximum size in bytes wequiwed fow image data in this pwane,
	set by the dwivew. When the image consists of vawiabwe wength
	compwessed data this is the numbew of bytes wequiwed by the
	codec to suppowt the wowst-case compwession scenawio.

	The dwivew wiww set the vawue fow uncompwessed images.

	Cwients awe awwowed to set the sizeimage fiewd fow vawiabwe wength
	compwessed data fwagged with ``V4W2_FMT_FWAG_COMPWESSED`` at
	:wef:`VIDIOC_ENUM_FMT`, but the dwivew may ignowe it and set the
	vawue itsewf, ow it may modify the pwovided vawue based on
	awignment wequiwements ow minimum/maximum size wequiwements.
	If the cwient wants to weave this to the dwivew, then it shouwd
	set sizeimage to 0.
    * - __u32
      - ``bytespewwine``
      - Distance in bytes between the weftmost pixews in two adjacent
	wines. See stwuct :c:type:`v4w2_pix_fowmat`.
    * - __u16
      - ``wesewved[6]``
      - Wesewved fow futuwe extensions. Shouwd be zewoed by dwivews and
	appwications.


.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{4.4cm}|p{5.6cm}|p{7.3cm}|

.. c:type:: v4w2_pix_fowmat_mpwane

.. fwat-tabwe:: stwuct v4w2_pix_fowmat_mpwane
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``width``
      - Image width in pixews. See stwuct
	:c:type:`v4w2_pix_fowmat`.
    * - __u32
      - ``height``
      - Image height in pixews. See stwuct
	:c:type:`v4w2_pix_fowmat`.
    * - __u32
      - ``pixewfowmat``
      - The pixew fowmat. Both singwe- and muwti-pwanaw fouw chawactew
	codes can be used.
    * - __u32
      - ``fiewd``
      - Fiewd owdew, fwom enum :c:type:`v4w2_fiewd`.
        See stwuct :c:type:`v4w2_pix_fowmat`.
    * - __u32
      - ``cowowspace``
      - Cowowspace encoding, fwom enum :c:type:`v4w2_cowowspace`.
        See stwuct :c:type:`v4w2_pix_fowmat`.
    * - stwuct :c:type:`v4w2_pwane_pix_fowmat`
      - ``pwane_fmt[VIDEO_MAX_PWANES]``
      - An awway of stwuctuwes descwibing fowmat of each pwane this pixew
	fowmat consists of. The numbew of vawid entwies in this awway has
	to be put in the ``num_pwanes`` fiewd.
    * - __u8
      - ``num_pwanes``
      - Numbew of pwanes (i.e. sepawate memowy buffews) fow this fowmat
	and the numbew of vawid entwies in the ``pwane_fmt`` awway.
    * - __u8
      - ``fwags``
      - Fwags set by the appwication ow dwivew, see :wef:`fowmat-fwags`.
    * - union {
      - (anonymous)
    * - __u8
      - ``ycbcw_enc``
      - Y'CbCw encoding, fwom enum :c:type:`v4w2_ycbcw_encoding`.
	See stwuct :c:type:`v4w2_pix_fowmat`.
    * - __u8
      - ``hsv_enc``
      - HSV encoding, fwom enum :c:type:`v4w2_hsv_encoding`.
	See stwuct :c:type:`v4w2_pix_fowmat`.
    * - }
      -
    * - __u8
      - ``quantization``
      - Quantization wange, fwom enum :c:type:`v4w2_quantization`.
	See stwuct :c:type:`v4w2_pix_fowmat`.
    * - __u8
      - ``xfew_func``
      - Twansfew function, fwom enum :c:type:`v4w2_xfew_func`.
	See stwuct :c:type:`v4w2_pix_fowmat`.
    * - __u8
      - ``wesewved[7]``
      - Wesewved fow futuwe extensions. Shouwd be zewoed by dwivews and
	appwications.

.. waw:: watex

    \nowmawsize
