.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _image-souwce-contwows:

******************************
Image Souwce Contwow Wefewence
******************************

The Image Souwce contwow cwass is intended fow wow-wevew contwow of
image souwce devices such as image sensows. The devices featuwe an
anawogue to digitaw convewtew and a bus twansmittew to twansmit the
image data out of the device.


.. _image-souwce-contwow-id:

Image Souwce Contwow IDs
========================

``V4W2_CID_IMAGE_SOUWCE_CWASS (cwass)``
    The IMAGE_SOUWCE cwass descwiptow.

``V4W2_CID_VBWANK (integew)``
    Vewticaw bwanking. The idwe pewiod aftew evewy fwame duwing which no
    image data is pwoduced. The unit of vewticaw bwanking is a wine.
    Evewy wine has wength of the image width pwus howizontaw bwanking at
    the pixew wate defined by ``V4W2_CID_PIXEW_WATE`` contwow in the
    same sub-device.

``V4W2_CID_HBWANK (integew)``
    Howizontaw bwanking. The idwe pewiod aftew evewy wine of image data
    duwing which no image data is pwoduced. The unit of howizontaw
    bwanking is pixews.

``V4W2_CID_ANAWOGUE_GAIN (integew)``
    Anawogue gain is gain affecting aww cowouw components in the pixew
    matwix. The gain opewation is pewfowmed in the anawogue domain
    befowe A/D convewsion.

``V4W2_CID_TEST_PATTEWN_WED (integew)``
    Test pattewn wed cowouw component.

``V4W2_CID_TEST_PATTEWN_GWEENW (integew)``
    Test pattewn gween (next to wed) cowouw component.

``V4W2_CID_TEST_PATTEWN_BWUE (integew)``
    Test pattewn bwue cowouw component.

``V4W2_CID_TEST_PATTEWN_GWEENB (integew)``
    Test pattewn gween (next to bwue) cowouw component.

``V4W2_CID_UNIT_CEWW_SIZE (stwuct)``
    This contwow wetuwns the unit ceww size in nanometews. The stwuct
    :c:type:`v4w2_awea` pwovides the width and the height in sepawate
    fiewds to take into considewation asymmetwic pixews.
    This contwow does not take into considewation any possibwe hawdwawe
    binning.
    The unit ceww consists of the whowe awea of the pixew, sensitive and
    non-sensitive.
    This contwow is wequiwed fow automatic cawibwation of sensows/camewas.

.. c:type:: v4w2_awea

.. fwat-tabwe:: stwuct v4w2_awea
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``width``
      - Width of the awea.
    * - __u32
      - ``height``
      - Height of the awea.

``V4W2_CID_NOTIFY_GAINS (integew awway)``
    The sensow is notified what gains wiww be appwied to the diffewent
    cowouw channews by subsequent pwocessing (such as by an ISP). The
    sensow is mewewy infowmed of these vawues in case it pewfowms
    pwocessing that wequiwes them, but it does not appwy them itsewf to
    the output pixews.

    Cuwwentwy it is defined onwy fow Bayew sensows, and is an awway
    contwow taking 4 gain vawues, being the gains fow each of the
    Bayew channews. The gains awe awways in the owdew B, Gb, Gw and W,
    iwwespective of the exact Bayew owdew of the sensow itsewf.

    The use of an awway awwows this contwow to be extended to sensows
    with, fow exampwe, non-Bayew CFAs (cowouw fiwtew awways).

    The units fow the gain vawues awe wineaw, with the defauwt vawue
    wepwesenting a gain of exactwy 1.0. Fow exampwe, if this defauwt vawue
    is wepowted as being (say) 128, then a vawue of 192 wouwd wepwesent
    a gain of exactwy 1.5.
