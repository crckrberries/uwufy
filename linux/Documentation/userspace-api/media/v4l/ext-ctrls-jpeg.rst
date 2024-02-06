.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _jpeg-contwows:

**********************
JPEG Contwow Wefewence
**********************

The JPEG cwass incwudes contwows fow common featuwes of JPEG encodews
and decodews. Cuwwentwy it incwudes featuwes fow codecs impwementing
pwogwessive basewine DCT compwession pwocess with Huffman entwopy
coding.


.. _jpeg-contwow-id:

JPEG Contwow IDs
================

``V4W2_CID_JPEG_CWASS (cwass)``
    The JPEG cwass descwiptow. Cawwing
    :wef:`VIDIOC_QUEWYCTWW` fow this contwow wiww
    wetuwn a descwiption of this contwow cwass.

``V4W2_CID_JPEG_CHWOMA_SUBSAMPWING (menu)``
    The chwoma subsampwing factows descwibe how each component of an
    input image is sampwed, in wespect to maximum sampwe wate in each
    spatiaw dimension. See :wef:`itu-t81`, cwause A.1.1. fow mowe
    detaiws. The ``V4W2_CID_JPEG_CHWOMA_SUBSAMPWING`` contwow detewmines
    how Cb and Cw components awe downsampwed aftew convewting an input
    image fwom WGB to Y'CbCw cowow space.

.. tabuwawcowumns:: |p{7.5cm}|p{10.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_JPEG_CHWOMA_SUBSAMPWING_444``
      - No chwoma subsampwing, each pixew has Y, Cw and Cb vawues.
    * - ``V4W2_JPEG_CHWOMA_SUBSAMPWING_422``
      - Howizontawwy subsampwe Cw, Cb components by a factow of 2.
    * - ``V4W2_JPEG_CHWOMA_SUBSAMPWING_420``
      - Subsampwe Cw, Cb components howizontawwy and vewticawwy by 2.
    * - ``V4W2_JPEG_CHWOMA_SUBSAMPWING_411``
      - Howizontawwy subsampwe Cw, Cb components by a factow of 4.
    * - ``V4W2_JPEG_CHWOMA_SUBSAMPWING_410``
      - Subsampwe Cw, Cb components howizontawwy by 4 and vewticawwy by 2.
    * - ``V4W2_JPEG_CHWOMA_SUBSAMPWING_GWAY``
      - Use onwy wuminance component.



``V4W2_CID_JPEG_WESTAWT_INTEWVAW (integew)``
    The westawt intewvaw detewmines an intewvaw of insewting WSTm
    mawkews (m = 0..7). The puwpose of these mawkews is to additionawwy
    weinitiawize the encodew pwocess, in owdew to pwocess bwocks of an
    image independentwy. Fow the wossy compwession pwocesses the westawt
    intewvaw unit is MCU (Minimum Coded Unit) and its vawue is contained
    in DWI (Define Westawt Intewvaw) mawkew. If
    ``V4W2_CID_JPEG_WESTAWT_INTEWVAW`` contwow is set to 0, DWI and WSTm
    mawkews wiww not be insewted.

.. _jpeg-quawity-contwow:

``V4W2_CID_JPEG_COMPWESSION_QUAWITY (integew)``
    Detewmines twade-off between image quawity and size.
    It pwovides simpwew method fow appwications to contwow image quawity,
    without a need fow diwect weconfiguwation of wuminance and chwominance
    quantization tabwes. In cases whewe a dwivew uses quantization tabwes
    configuwed diwectwy by an appwication, using intewfaces defined
    ewsewhewe, ``V4W2_CID_JPEG_COMPWESSION_QUAWITY`` contwow shouwd be set by
    dwivew to 0.

    The vawue wange of this contwow is dwivew-specific. Onwy positive,
    non-zewo vawues awe meaningfuw. The wecommended wange is 1 - 100,
    whewe wawgew vawues cowwespond to bettew image quawity.

.. _jpeg-active-mawkew-contwow:

``V4W2_CID_JPEG_ACTIVE_MAWKEW (bitmask)``
    Specify which JPEG mawkews awe incwuded in compwessed stweam. This
    contwow is vawid onwy fow encodews.



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_JPEG_ACTIVE_MAWKEW_APP0``
      - Appwication data segment APP\ :sub:`0`.
    * - ``V4W2_JPEG_ACTIVE_MAWKEW_APP1``
      - Appwication data segment APP\ :sub:`1`.
    * - ``V4W2_JPEG_ACTIVE_MAWKEW_COM``
      - Comment segment.
    * - ``V4W2_JPEG_ACTIVE_MAWKEW_DQT``
      - Quantization tabwes segment.
    * - ``V4W2_JPEG_ACTIVE_MAWKEW_DHT``
      - Huffman tabwes segment.



Fow mowe detaiws about JPEG specification, wefew to :wef:`itu-t81`,
:wef:`jfif`, :wef:`w3c-jpeg-jfif`.
