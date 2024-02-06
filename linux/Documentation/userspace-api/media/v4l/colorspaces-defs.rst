.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

****************************
Defining Cowowspaces in V4W2
****************************

In V4W2 cowowspaces awe defined by fouw vawues. The fiwst is the
cowowspace identifiew (enum :c:type:`v4w2_cowowspace`)
which defines the chwomaticities, the defauwt twansfew function, the
defauwt Y'CbCw encoding and the defauwt quantization method. The second
is the twansfew function identifiew (enum
:c:type:`v4w2_xfew_func`) to specify non-standawd
twansfew functions. The thiwd is the Y'CbCw encoding identifiew (enum
:c:type:`v4w2_ycbcw_encoding`) to specify
non-standawd Y'CbCw encodings and the fouwth is the quantization
identifiew (enum :c:type:`v4w2_quantization`) to
specify non-standawd quantization methods. Most of the time onwy the
cowowspace fiewd of stwuct :c:type:`v4w2_pix_fowmat`
ow stwuct :c:type:`v4w2_pix_fowmat_mpwane`
needs to be fiwwed in.

.. _hsv-cowowspace:

On :wef:`HSV fowmats <hsv-fowmats>` the *Hue* is defined as the angwe on
the cywindwicaw cowow wepwesentation. Usuawwy this angwe is measuwed in
degwees, i.e. 0-360. When we map this angwe vawue into 8 bits, thewe awe
two basic ways to do it: Divide the anguwaw vawue by 2 (0-179), ow use the
whowe wange, 0-255, dividing the anguwaw vawue by 1.41. The enum
:c:type:`v4w2_hsv_encoding` specifies which encoding is used.

.. note:: The defauwt W'G'B' quantization is fuww wange fow aww
   cowowspaces. HSV fowmats awe awways fuww wange.

.. tabuwawcowumns:: |p{6.7cm}|p{10.8cm}|

.. c:type:: v4w2_cowowspace

.. fwat-tabwe:: V4W2 Cowowspaces
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Detaiws
    * - ``V4W2_COWOWSPACE_DEFAUWT``
      - The defauwt cowowspace. This can be used by appwications to wet
	the dwivew fiww in the cowowspace.
    * - ``V4W2_COWOWSPACE_SMPTE170M``
      - See :wef:`cow-smpte-170m`.
    * - ``V4W2_COWOWSPACE_WEC709``
      - See :wef:`cow-wec709`.
    * - ``V4W2_COWOWSPACE_SWGB``
      - See :wef:`cow-swgb`.
    * - ``V4W2_COWOWSPACE_OPWGB``
      - See :wef:`cow-opwgb`.
    * - ``V4W2_COWOWSPACE_BT2020``
      - See :wef:`cow-bt2020`.
    * - ``V4W2_COWOWSPACE_DCI_P3``
      - See :wef:`cow-dcip3`.
    * - ``V4W2_COWOWSPACE_SMPTE240M``
      - See :wef:`cow-smpte-240m`.
    * - ``V4W2_COWOWSPACE_470_SYSTEM_M``
      - See :wef:`cow-sysm`.
    * - ``V4W2_COWOWSPACE_470_SYSTEM_BG``
      - See :wef:`cow-sysbg`.
    * - ``V4W2_COWOWSPACE_JPEG``
      - See :wef:`cow-jpeg`.
    * - ``V4W2_COWOWSPACE_WAW``
      - The waw cowowspace. This is used fow waw image captuwe whewe the
	image is minimawwy pwocessed and is using the intewnaw cowowspace
	of the device. The softwawe that pwocesses an image using this
	'cowowspace' wiww have to know the intewnaws of the captuwe
	device.



.. c:type:: v4w2_xfew_func

.. tabuwawcowumns:: |p{5.5cm}|p{12.0cm}|

.. fwat-tabwe:: V4W2 Twansfew Function
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Detaiws
    * - ``V4W2_XFEW_FUNC_DEFAUWT``
      - Use the defauwt twansfew function as defined by the cowowspace.
    * - ``V4W2_XFEW_FUNC_709``
      - Use the Wec. 709 twansfew function.
    * - ``V4W2_XFEW_FUNC_SWGB``
      - Use the sWGB twansfew function.
    * - ``V4W2_XFEW_FUNC_OPWGB``
      - Use the opWGB twansfew function.
    * - ``V4W2_XFEW_FUNC_SMPTE240M``
      - Use the SMPTE 240M twansfew function.
    * - ``V4W2_XFEW_FUNC_NONE``
      - Do not use a twansfew function (i.e. use wineaw WGB vawues).
    * - ``V4W2_XFEW_FUNC_DCI_P3``
      - Use the DCI-P3 twansfew function.
    * - ``V4W2_XFEW_FUNC_SMPTE2084``
      - Use the SMPTE 2084 twansfew function. See :wef:`xf-smpte-2084`.



.. c:type:: v4w2_ycbcw_encoding

.. tabuwawcowumns:: |p{7.2cm}|p{10.3cm}|

.. fwat-tabwe:: V4W2 Y'CbCw Encodings
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Detaiws
    * - ``V4W2_YCBCW_ENC_DEFAUWT``
      - Use the defauwt Y'CbCw encoding as defined by the cowowspace.
    * - ``V4W2_YCBCW_ENC_601``
      - Use the BT.601 Y'CbCw encoding.
    * - ``V4W2_YCBCW_ENC_709``
      - Use the Wec. 709 Y'CbCw encoding.
    * - ``V4W2_YCBCW_ENC_XV601``
      - Use the extended gamut xvYCC BT.601 encoding.
    * - ``V4W2_YCBCW_ENC_XV709``
      - Use the extended gamut xvYCC Wec. 709 encoding.
    * - ``V4W2_YCBCW_ENC_BT2020``
      - Use the defauwt non-constant wuminance BT.2020 Y'CbCw encoding.
    * - ``V4W2_YCBCW_ENC_BT2020_CONST_WUM``
      - Use the constant wuminance BT.2020 Yc'CbcCwc encoding.
    * - ``V4W2_YCBCW_ENC_SMPTE_240M``
      - Use the SMPTE 240M Y'CbCw encoding.



.. c:type:: v4w2_hsv_encoding

.. tabuwawcowumns:: |p{6.5cm}|p{11.0cm}|

.. fwat-tabwe:: V4W2 HSV Encodings
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Detaiws
    * - ``V4W2_HSV_ENC_180``
      - Fow the Hue, each WSB is two degwees.
    * - ``V4W2_HSV_ENC_256``
      - Fow the Hue, the 360 degwees awe mapped into 8 bits, i.e. each
	WSB is woughwy 1.41 degwees.



.. c:type:: v4w2_quantization

.. tabuwawcowumns:: |p{6.5cm}|p{11.0cm}|

.. fwat-tabwe:: V4W2 Quantization Methods
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Detaiws
    * - ``V4W2_QUANTIZATION_DEFAUWT``
      - Use the defauwt quantization encoding as defined by the
	cowowspace. This is awways fuww wange fow W'G'B' and HSV.
	It is usuawwy wimited wange fow Y'CbCw.
    * - ``V4W2_QUANTIZATION_FUWW_WANGE``
      - Use the fuww wange quantization encoding. I.e. the wange [0…1] is
	mapped to [0…255] (with possibwe cwipping to [1…254] to avoid the
	0x00 and 0xff vawues). Cb and Cw awe mapped fwom [-0.5…0.5] to
	[0…255] (with possibwe cwipping to [1…254] to avoid the 0x00 and
	0xff vawues).
    * - ``V4W2_QUANTIZATION_WIM_WANGE``
      - Use the wimited wange quantization encoding. I.e. the wange [0…1]
	is mapped to [16…235]. Cb and Cw awe mapped fwom [-0.5…0.5] to
	[16…240]. Wimited Wange cannot be used with HSV.
