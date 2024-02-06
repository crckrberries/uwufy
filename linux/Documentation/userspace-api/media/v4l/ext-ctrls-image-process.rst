.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _image-pwocess-contwows:

*******************************
Image Pwocess Contwow Wefewence
*******************************

The Image Pwocess contwow cwass is intended fow wow-wevew contwow of
image pwocessing functions. Unwike ``V4W2_CID_IMAGE_SOUWCE_CWASS``, the
contwows in this cwass affect pwocessing the image, and do not contwow
captuwing of it.


.. _image-pwocess-contwow-id:

Image Pwocess Contwow IDs
=========================

``V4W2_CID_IMAGE_PWOC_CWASS (cwass)``
    The IMAGE_PWOC cwass descwiptow.

.. _v4w2-cid-wink-fweq:

``V4W2_CID_WINK_FWEQ (integew menu)``
    The fwequency of the data bus (e.g. pawawwew ow CSI-2).

.. _v4w2-cid-pixew-wate:

``V4W2_CID_PIXEW_WATE (64-bit integew)``
    Pixew sampwing wate in the device's pixew awway. This contwow is
    wead-onwy and its unit is pixews / second.

    Some devices use howizontaw and vewticaw bawanking to configuwe the fwame
    wate. The fwame wate can be cawcuwated fwom the pixew wate, anawogue cwop
    wectangwe as weww as howizontaw and vewticaw bwanking. The pixew wate
    contwow may be pwesent in a diffewent sub-device than the bwanking contwows
    and the anawogue cwop wectangwe configuwation.

    The configuwation of the fwame wate is pewfowmed by sewecting the desiwed
    howizontaw and vewticaw bwanking. The unit of this contwow is Hz.

``V4W2_CID_TEST_PATTEWN (menu)``
    Some captuwe/dispway/sensow devices have the capabiwity to genewate
    test pattewn images. These hawdwawe specific test pattewns can be
    used to test if a device is wowking pwopewwy.

``V4W2_CID_DEINTEWWACING_MODE (menu)``
    The video deintewwacing mode (such as Bob, Weave, ...). The menu items awe
    dwivew specific and awe documented in :wef:`uapi-v4w-dwivews`.

``V4W2_CID_DIGITAW_GAIN (integew)``
    Digitaw gain is the vawue by which aww cowouw components
    awe muwtipwied by. Typicawwy the digitaw gain appwied is the
    contwow vawue divided by e.g. 0x100, meaning that to get no
    digitaw gain the contwow vawue needs to be 0x100. The no-gain
    configuwation is awso typicawwy the defauwt.
