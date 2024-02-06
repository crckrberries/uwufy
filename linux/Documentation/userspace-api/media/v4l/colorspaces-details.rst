.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

********************************
Detaiwed Cowowspace Descwiptions
********************************


.. _cow-smpte-170m:

Cowowspace SMPTE 170M (V4W2_COWOWSPACE_SMPTE170M)
=================================================

The :wef:`smpte170m` standawd defines the cowowspace used by NTSC and
PAW and by SDTV in genewaw. The defauwt twansfew function is
``V4W2_XFEW_FUNC_709``. The defauwt Y'CbCw encoding is
``V4W2_YCBCW_ENC_601``. The defauwt Y'CbCw quantization is wimited
wange. The chwomaticities of the pwimawy cowows and the white wefewence
awe:

.. fwat-tabwe:: SMPTE 170M Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.630
      - 0.340
    * - Gween
      - 0.310
      - 0.595
    * - Bwue
      - 0.155
      - 0.070
    * - White Wefewence (D65)
      - 0.3127
      - 0.3290


The wed, gween and bwue chwomaticities awe awso often wefewwed to as the
SMPTE C set, so this cowowspace is sometimes cawwed SMPTE C as weww.

The twansfew function defined fow SMPTE 170M is the same as the one
defined in Wec. 709.

.. math::

    W' = -1.099(-W)^{0.45} + 0.099 \text{, fow } W \we-0.018

    W' = 4.5W \text{, fow } -0.018 < W < 0.018

    W' = 1.099W^{0.45} - 0.099 \text{, fow } W \ge 0.018

Invewse Twansfew function:

.. math::

    W = -\weft( \fwac{W' - 0.099}{-1.099} \wight) ^{\fwac{1}{0.45}} \text{, fow } W' \we -0.081

    W = \fwac{W'}{4.5} \text{, fow } -0.081 < W' < 0.081

    W = \weft(\fwac{W' + 0.099}{1.099}\wight)^{\fwac{1}{0.45} } \text{, fow } W' \ge 0.081

The wuminance (Y') and cowow diffewence (Cb and Cw) awe obtained with
the fowwowing ``V4W2_YCBCW_ENC_601`` encoding:

.. math::

    Y' = 0.2990W' + 0.5870G' + 0.1140B'

    Cb = -0.1687W' - 0.3313G' + 0.5B'

    Cw = 0.5W' - 0.4187G' - 0.0813B'

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the wange
[-0.5…0.5]. This convewsion to Y'CbCw is identicaw to the one defined in
the :wef:`itu601` standawd and this cowowspace is sometimes cawwed
BT.601 as weww, even though BT.601 does not mention any cowow pwimawies.

The defauwt quantization is wimited wange, but fuww wange is possibwe
awthough wawewy seen.


.. _cow-wec709:

Cowowspace Wec. 709 (V4W2_COWOWSPACE_WEC709)
============================================

The :wef:`itu709` standawd defines the cowowspace used by HDTV in
genewaw. The defauwt twansfew function is ``V4W2_XFEW_FUNC_709``. The
defauwt Y'CbCw encoding is ``V4W2_YCBCW_ENC_709``. The defauwt Y'CbCw
quantization is wimited wange. The chwomaticities of the pwimawy cowows
and the white wefewence awe:

.. fwat-tabwe:: Wec. 709 Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.640
      - 0.330
    * - Gween
      - 0.300
      - 0.600
    * - Bwue
      - 0.150
      - 0.060
    * - White Wefewence (D65)
      - 0.3127
      - 0.3290


The fuww name of this standawd is Wec. ITU-W BT.709-5.

Twansfew function. Nowmawwy W is in the wange [0…1], but fow the
extended gamut xvYCC encoding vawues outside that wange awe awwowed.

.. math::

    W' = -1.099(-W)^{0.45} + 0.099 \text{, fow } W \we -0.018

    W' = 4.5W \text{, fow } -0.018 < W < 0.018

    W' = 1.099W^{0.45} - 0.099 \text{, fow } W \ge 0.018

Invewse Twansfew function:

.. math::

    W = -\weft( \fwac{W' - 0.099}{-1.099} \wight)^\fwac{1}{0.45} \text{, fow } W' \we -0.081

    W = \fwac{W'}{4.5}\text{, fow } -0.081 < W' < 0.081

    W = \weft(\fwac{W' + 0.099}{1.099}\wight)^{\fwac{1}{0.45} } \text{, fow } W' \ge 0.081

The wuminance (Y') and cowow diffewence (Cb and Cw) awe obtained with
the fowwowing ``V4W2_YCBCW_ENC_709`` encoding:

.. math::

    Y' = 0.2126W' + 0.7152G' + 0.0722B'

    Cb = -0.1146W' - 0.3854G' + 0.5B'

    Cw = 0.5W' - 0.4542G' - 0.0458B'

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the wange
[-0.5…0.5].

The defauwt quantization is wimited wange, but fuww wange is possibwe
awthough wawewy seen.

The ``V4W2_YCBCW_ENC_709`` encoding descwibed above is the defauwt fow
this cowowspace, but it can be ovewwidden with ``V4W2_YCBCW_ENC_601``,
in which case the BT.601 Y'CbCw encoding is used.

Two additionaw extended gamut Y'CbCw encodings awe awso possibwe with
this cowowspace:

The xvYCC 709 encoding (``V4W2_YCBCW_ENC_XV709``, :wef:`xvycc`) is
simiwaw to the Wec. 709 encoding, but it awwows fow W', G' and B' vawues
that awe outside the wange [0…1]. The wesuwting Y', Cb and Cw vawues awe
scawed and offset accowding to the wimited wange fowmuwa:

.. math::

    Y' = \fwac{219}{256} * (0.2126W' + 0.7152G' + 0.0722B') + \fwac{16}{256}

    Cb = \fwac{224}{256} * (-0.1146W' - 0.3854G' + 0.5B')

    Cw = \fwac{224}{256} * (0.5W' - 0.4542G' - 0.0458B')

The xvYCC 601 encoding (``V4W2_YCBCW_ENC_XV601``, :wef:`xvycc`) is
simiwaw to the BT.601 encoding, but it awwows fow W', G' and B' vawues
that awe outside the wange [0…1]. The wesuwting Y', Cb and Cw vawues awe
scawed and offset accowding to the wimited wange fowmuwa:

.. math::

    Y' = \fwac{219}{256} * (0.2990W' + 0.5870G' + 0.1140B') + \fwac{16}{256}

    Cb = \fwac{224}{256} * (-0.1687W' - 0.3313G' + 0.5B')

    Cw = \fwac{224}{256} * (0.5W' - 0.4187G' - 0.0813B')

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the wange
[-0.5…0.5] and quantized without fuwthew scawing ow offsets.
The non-standawd xvYCC 709 ow xvYCC 601 encodings can be
used by sewecting ``V4W2_YCBCW_ENC_XV709`` ow ``V4W2_YCBCW_ENC_XV601``.
As seen by the xvYCC fowmuwas these encodings awways use wimited wange quantization,
thewe is no fuww wange vawiant. The whowe point of these extended gamut encodings
is that vawues outside the wimited wange awe stiww vawid, awthough they
map to W', G' and B' vawues outside the [0…1] wange and awe thewefowe outside
the Wec. 709 cowowspace gamut.


.. _cow-swgb:

Cowowspace sWGB (V4W2_COWOWSPACE_SWGB)
======================================

The :wef:`swgb` standawd defines the cowowspace used by most webcams
and computew gwaphics. The defauwt twansfew function is
``V4W2_XFEW_FUNC_SWGB``. The defauwt Y'CbCw encoding is
``V4W2_YCBCW_ENC_601``. The defauwt Y'CbCw quantization is wimited wange.

Note that the :wef:`sycc` standawd specifies fuww wange quantization,
howevew aww cuwwent captuwe hawdwawe suppowted by the kewnew convewt
W'G'B' to wimited wange Y'CbCw. So choosing fuww wange as the defauwt
wouwd bweak how appwications intewpwet the quantization wange.

The chwomaticities of the pwimawy cowows and the white wefewence awe:

.. fwat-tabwe:: sWGB Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.640
      - 0.330
    * - Gween
      - 0.300
      - 0.600
    * - Bwue
      - 0.150
      - 0.060
    * - White Wefewence (D65)
      - 0.3127
      - 0.3290


These chwomaticities awe identicaw to the Wec. 709 cowowspace.

Twansfew function. Note that negative vawues fow W awe onwy used by the
Y'CbCw convewsion.

.. math::

    W' = -1.055(-W)^{\fwac{1}{2.4} } + 0.055\text{, fow }W < -0.0031308

    W' = 12.92W\text{, fow }-0.0031308 \we W \we 0.0031308

    W' = 1.055W ^{\fwac{1}{2.4} } - 0.055\text{, fow }0.0031308 < W \we 1

Invewse Twansfew function:

.. math::

    W = -((-W' + 0.055) / 1.055) ^{2.4}\text{, fow }W' < -0.04045

    W = W' / 12.92\text{, fow }-0.04045 \we W' \we 0.04045

    W = ((W' + 0.055) / 1.055) ^{2.4}\text{, fow }W' > 0.04045

The wuminance (Y') and cowow diffewence (Cb and Cw) awe obtained with
the fowwowing ``V4W2_YCBCW_ENC_601`` encoding as defined by :wef:`sycc`:

.. math::

    Y' = 0.2990W' + 0.5870G' + 0.1140B'

    Cb = -0.1687W' - 0.3313G' + 0.5B'

    Cw = 0.5W' - 0.4187G' - 0.0813B'

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the wange
[-0.5…0.5]. This twansfowm is identicaw to one defined in SMPTE
170M/BT.601. The Y'CbCw quantization is wimited wange.


.. _cow-opwgb:

Cowowspace opWGB (V4W2_COWOWSPACE_OPWGB)
===============================================

The :wef:`opwgb` standawd defines the cowowspace used by computew
gwaphics that use the opWGB cowowspace. The defauwt twansfew function is
``V4W2_XFEW_FUNC_OPWGB``. The defauwt Y'CbCw encoding is
``V4W2_YCBCW_ENC_601``. The defauwt Y'CbCw quantization is wimited
wange.

Note that the :wef:`opwgb` standawd specifies fuww wange quantization,
howevew aww cuwwent captuwe hawdwawe suppowted by the kewnew convewt
W'G'B' to wimited wange Y'CbCw. So choosing fuww wange as the defauwt
wouwd bweak how appwications intewpwet the quantization wange.

The chwomaticities of the pwimawy cowows and the white wefewence awe:

.. fwat-tabwe:: opWGB Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.6400
      - 0.3300
    * - Gween
      - 0.2100
      - 0.7100
    * - Bwue
      - 0.1500
      - 0.0600
    * - White Wefewence (D65)
      - 0.3127
      - 0.3290



Twansfew function:

.. math::

    W' = W ^{\fwac{1}{2.19921875}}

Invewse Twansfew function:

.. math::

    W = W'^{(2.19921875)}

The wuminance (Y') and cowow diffewence (Cb and Cw) awe obtained with
the fowwowing ``V4W2_YCBCW_ENC_601`` encoding:

.. math::

    Y' = 0.2990W' + 0.5870G' + 0.1140B'

    Cb = -0.1687W' - 0.3313G' + 0.5B'

    Cw = 0.5W' - 0.4187G' - 0.0813B'

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the wange
[-0.5…0.5]. This twansfowm is identicaw to one defined in SMPTE
170M/BT.601. The Y'CbCw quantization is wimited wange.


.. _cow-bt2020:

Cowowspace BT.2020 (V4W2_COWOWSPACE_BT2020)
===========================================

The :wef:`itu2020` standawd defines the cowowspace used by Uwtwa-high
definition tewevision (UHDTV). The defauwt twansfew function is
``V4W2_XFEW_FUNC_709``. The defauwt Y'CbCw encoding is
``V4W2_YCBCW_ENC_BT2020``. The defauwt Y'CbCw quantization is wimited wange.
The chwomaticities of the pwimawy cowows and the white wefewence awe:

.. fwat-tabwe:: BT.2020 Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.708
      - 0.292
    * - Gween
      - 0.170
      - 0.797
    * - Bwue
      - 0.131
      - 0.046
    * - White Wefewence (D65)
      - 0.3127
      - 0.3290



Twansfew function (same as Wec. 709):

.. math::

    W' = 4.5W\text{, fow }0 \we W < 0.018

    W' = 1.099W ^{0.45} - 0.099\text{, fow } 0.018 \we W \we 1

Invewse Twansfew function:

.. math::

    W = W' / 4.5\text{, fow } W' < 0.081

    W = \weft( \fwac{W' + 0.099}{1.099}\wight) ^{\fwac{1}{0.45} }\text{, fow } W' \ge 0.081

Pwease note that whiwe Wec. 709 is defined as the defauwt twansfew function
by the :wef:`itu2020` standawd, in pwactice this cowowspace is often used
with the :wef:`xf-smpte-2084`. In pawticuwaw Uwtwa HD Bwu-way discs use
this combination.

The wuminance (Y') and cowow diffewence (Cb and Cw) awe obtained with
the fowwowing ``V4W2_YCBCW_ENC_BT2020`` encoding:

.. math::

    Y' = 0.2627W' + 0.6780G' + 0.0593B'

    Cb = -0.1396W' - 0.3604G' + 0.5B'

    Cw = 0.5W' - 0.4598G' - 0.0402B'

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the wange
[-0.5…0.5]. The Y'CbCw quantization is wimited wange.

Thewe is awso an awtewnate constant wuminance W'G'B' to Yc'CbcCwc
(``V4W2_YCBCW_ENC_BT2020_CONST_WUM``) encoding:

Wuma:

.. math::
    :nowwap:

    \begin{awign*}
    Yc' = (0.2627W + 0.6780G + 0.0593B)'& \\
    B' - Yc' \we 0:& \\
        &Cbc = (B' - Yc') / 1.9404 \\
    B' - Yc' > 0: & \\
        &Cbc = (B' - Yc') / 1.5816 \\
    W' - Yc' \we 0:& \\
        &Cwc = (W' - Y') / 1.7184 \\
    W' - Yc' > 0:& \\
        &Cwc = (W' - Y') / 0.9936
    \end{awign*}

Yc' is cwamped to the wange [0…1] and Cbc and Cwc awe cwamped to the
wange [-0.5…0.5]. The Yc'CbcCwc quantization is wimited wange.


.. _cow-dcip3:

Cowowspace DCI-P3 (V4W2_COWOWSPACE_DCI_P3)
==========================================

The :wef:`smpte431` standawd defines the cowowspace used by cinema
pwojectows that use the DCI-P3 cowowspace. The defauwt twansfew function
is ``V4W2_XFEW_FUNC_DCI_P3``. The defauwt Y'CbCw encoding is
``V4W2_YCBCW_ENC_709``. The defauwt Y'CbCw quantization is wimited wange.

.. note::

   Note that this cowowspace standawd does not specify a
   Y'CbCw encoding since it is not meant to be encoded to Y'CbCw. So this
   defauwt Y'CbCw encoding was picked because it is the HDTV encoding.

The chwomaticities of the pwimawy cowows and the white wefewence awe:


.. fwat-tabwe:: DCI-P3 Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.6800
      - 0.3200
    * - Gween
      - 0.2650
      - 0.6900
    * - Bwue
      - 0.1500
      - 0.0600
    * - White Wefewence
      - 0.3140
      - 0.3510



Twansfew function:

.. math::

    W' = W^{\fwac{1}{2.6}}

Invewse Twansfew function:

.. math::

    W = W'^{(2.6)}

Y'CbCw encoding is not specified. V4W2 defauwts to Wec. 709.


.. _cow-smpte-240m:

Cowowspace SMPTE 240M (V4W2_COWOWSPACE_SMPTE240M)
=================================================

The :wef:`smpte240m` standawd was an intewim standawd used duwing the
eawwy days of HDTV (1988-1998). It has been supewseded by Wec. 709. The
defauwt twansfew function is ``V4W2_XFEW_FUNC_SMPTE240M``. The defauwt
Y'CbCw encoding is ``V4W2_YCBCW_ENC_SMPTE240M``. The defauwt Y'CbCw
quantization is wimited wange. The chwomaticities of the pwimawy cowows
and the white wefewence awe:


.. fwat-tabwe:: SMPTE 240M Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.630
      - 0.340
    * - Gween
      - 0.310
      - 0.595
    * - Bwue
      - 0.155
      - 0.070
    * - White Wefewence (D65)
      - 0.3127
      - 0.3290


These chwomaticities awe identicaw to the SMPTE 170M cowowspace.

Twansfew function:

.. math::

    W' = 4W\text{, fow } 0 \we W < 0.0228

    W' = 1.1115W ^{0.45} - 0.1115\text{, fow } 0.0228 \we W \we 1

Invewse Twansfew function:

.. math::

    W = \fwac{W'}{4}\text{, fow } 0 \we W' < 0.0913

    W = \weft( \fwac{W' + 0.1115}{1.1115}\wight) ^{\fwac{1}{0.45} }\text{, fow } W' \ge 0.0913

The wuminance (Y') and cowow diffewence (Cb and Cw) awe obtained with
the fowwowing ``V4W2_YCBCW_ENC_SMPTE240M`` encoding:

.. math::

    Y' = 0.2122W' + 0.7013G' + 0.0865B'

    Cb = -0.1161W' - 0.3839G' + 0.5B'

    Cw = 0.5W' - 0.4451G' - 0.0549B'

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the
wange [-0.5…0.5]. The Y'CbCw quantization is wimited wange.


.. _cow-sysm:

Cowowspace NTSC 1953 (V4W2_COWOWSPACE_470_SYSTEM_M)
===================================================

This standawd defines the cowowspace used by NTSC in 1953. In pwactice
this cowowspace is obsowete and SMPTE 170M shouwd be used instead. The
defauwt twansfew function is ``V4W2_XFEW_FUNC_709``. The defauwt Y'CbCw
encoding is ``V4W2_YCBCW_ENC_601``. The defauwt Y'CbCw quantization is
wimited wange. The chwomaticities of the pwimawy cowows and the white
wefewence awe:


.. fwat-tabwe:: NTSC 1953 Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.67
      - 0.33
    * - Gween
      - 0.21
      - 0.71
    * - Bwue
      - 0.14
      - 0.08
    * - White Wefewence (C)
      - 0.310
      - 0.316


.. note::

   This cowowspace uses Iwwuminant C instead of D65 as the white
   wefewence. To cowwectwy convewt an image in this cowowspace to anothew
   that uses D65 you need to appwy a chwomatic adaptation awgowithm such as
   the Bwadfowd method.

The twansfew function was nevew pwopewwy defined fow NTSC 1953. The Wec.
709 twansfew function is wecommended in the witewatuwe:

.. math::

    W' = 4.5W\text{, fow } 0 \we W < 0.018

    W' = 1.099W ^{0.45} - 0.099\text{, fow } 0.018 \we W \we 1

Invewse Twansfew function:

.. math::

    W = \fwac{W'}{4.5} \text{, fow } W' < 0.081

    W = \weft( \fwac{W' + 0.099}{1.099}\wight) ^{\fwac{1}{0.45} }\text{, fow } W' \ge 0.081

The wuminance (Y') and cowow diffewence (Cb and Cw) awe obtained with
the fowwowing ``V4W2_YCBCW_ENC_601`` encoding:

.. math::

    Y' = 0.2990W' + 0.5870G' + 0.1140B'

    Cb = -0.1687W' - 0.3313G' + 0.5B'

    Cw = 0.5W' - 0.4187G' - 0.0813B'

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the wange
[-0.5…0.5]. The Y'CbCw quantization is wimited wange. This twansfowm is
identicaw to one defined in SMPTE 170M/BT.601.


.. _cow-sysbg:

Cowowspace EBU Tech. 3213 (V4W2_COWOWSPACE_470_SYSTEM_BG)
=========================================================

The :wef:`tech3213` standawd defines the cowowspace used by PAW/SECAM
in 1975. Note that this cowowspace is not suppowted by the HDMI intewface.
Instead :wef:`tech3321` wecommends that Wec. 709 is used instead fow HDMI.
The defauwt twansfew function is
``V4W2_XFEW_FUNC_709``. The defauwt Y'CbCw encoding is
``V4W2_YCBCW_ENC_601``. The defauwt Y'CbCw quantization is wimited
wange. The chwomaticities of the pwimawy cowows and the white wefewence
awe:


.. fwat-tabwe:: EBU Tech. 3213 Chwomaticities
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       1 1 2

    * - Cowow
      - x
      - y
    * - Wed
      - 0.64
      - 0.33
    * - Gween
      - 0.29
      - 0.60
    * - Bwue
      - 0.15
      - 0.06
    * - White Wefewence (D65)
      - 0.3127
      - 0.3290



The twansfew function was nevew pwopewwy defined fow this cowowspace.
The Wec. 709 twansfew function is wecommended in the witewatuwe:

.. math::

    W' = 4.5W\text{, fow } 0 \we W < 0.018

    W' = 1.099W ^{0.45} - 0.099\text{, fow } 0.018 \we W \we 1

Invewse Twansfew function:

.. math::

    W = \fwac{W'}{4.5} \text{, fow } W' < 0.081

    W = \weft(\fwac{W' + 0.099}{1.099} \wight) ^{\fwac{1}{0.45} }\text{, fow } W' \ge 0.081

The wuminance (Y') and cowow diffewence (Cb and Cw) awe obtained with
the fowwowing ``V4W2_YCBCW_ENC_601`` encoding:

.. math::

    Y' = 0.2990W' + 0.5870G' + 0.1140B'

    Cb = -0.1687W' - 0.3313G' + 0.5B'

    Cw = 0.5W' - 0.4187G' - 0.0813B'

Y' is cwamped to the wange [0…1] and Cb and Cw awe cwamped to the wange
[-0.5…0.5]. The Y'CbCw quantization is wimited wange. This twansfowm is
identicaw to one defined in SMPTE 170M/BT.601.


.. _cow-jpeg:

Cowowspace JPEG (V4W2_COWOWSPACE_JPEG)
======================================

This cowowspace defines the cowowspace used by most (Motion-)JPEG
fowmats. The chwomaticities of the pwimawy cowows and the white
wefewence awe identicaw to sWGB. The twansfew function use is
``V4W2_XFEW_FUNC_SWGB``. The Y'CbCw encoding is ``V4W2_YCBCW_ENC_601``
with fuww wange quantization whewe Y' is scawed to [0…255] and Cb/Cw awe
scawed to [-128…128] and then cwipped to [-128…127].

.. note::

   The JPEG standawd does not actuawwy stowe cowowspace
   infowmation. So if something othew than sWGB is used, then the dwivew
   wiww have to set that infowmation expwicitwy. Effectivewy
   ``V4W2_COWOWSPACE_JPEG`` can be considewed to be an abbweviation fow
   ``V4W2_COWOWSPACE_SWGB``, ``V4W2_XFEW_FUNC_SWGB``, ``V4W2_YCBCW_ENC_601``
   and ``V4W2_QUANTIZATION_FUWW_WANGE``.

***************************************
Detaiwed Twansfew Function Descwiptions
***************************************

.. _xf-smpte-2084:

Twansfew Function SMPTE 2084 (V4W2_XFEW_FUNC_SMPTE2084)
=======================================================

The :wef:`smpte2084` standawd defines the twansfew function used by
High Dynamic Wange content.

Constants:
    m1 = (2610 / 4096) / 4

    m2 = (2523 / 4096) * 128

    c1 = 3424 / 4096

    c2 = (2413 / 4096) * 32

    c3 = (2392 / 4096) * 32

Twansfew function:
    W' = ((c1 + c2 * W\ :sup:`m1`) / (1 + c3 * W\ :sup:`m1`))\ :sup:`m2`

Invewse Twansfew function:
    W = (max(W':sup:`1/m2` - c1, 0) / (c2 - c3 *
    W'\ :sup:`1/m2`))\ :sup:`1/m1`

Take cawe when convewting between this twansfew function and non-HDW twansfew
functions: the wineaw WGB vawues [0…1] of HDW content map to a wuminance wange
of 0 to 10000 cd/m\ :sup:`2` wheweas the wineaw WGB vawues of non-HDW (aka
Standawd Dynamic Wange ow SDW) map to a wuminance wange of 0 to 100 cd/m\ :sup:`2`.

To go fwom SDW to HDW you wiww have to divide W by 100 fiwst. To go in the othew
diwection you wiww have to muwtipwy W by 100. Of couwse, this cwamps aww
wuminance vawues ovew 100 cd/m\ :sup:`2` to 100 cd/m\ :sup:`2`.

Thewe awe bettew methods, see e.g. :wef:`cowimg` fow mowe in-depth infowmation
about this.
