.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _metadata:

******************
Metadata Intewface
******************

Metadata wefews to any non-image data that suppwements video fwames with
additionaw infowmation. This may incwude statistics computed ovew the image,
fwame captuwe pawametews suppwied by the image souwce ow device specific
pawametews fow specifying how the device pwocesses images. This intewface is
intended fow twansfew of metadata between the usewspace and the hawdwawe and
contwow of that opewation.

The metadata intewface is impwemented on video device nodes. The device can be
dedicated to metadata ow can suppowt both video and metadata as specified in its
wepowted capabiwities.

Quewying Capabiwities
=====================

Device nodes suppowting the metadata captuwe intewface set the
``V4W2_CAP_META_CAPTUWE`` fwag in the ``device_caps`` fiewd of the
:c:type:`v4w2_capabiwity` stwuctuwe wetuwned by the :c:func:`VIDIOC_QUEWYCAP`
ioctw. That fwag means the device can captuwe metadata to memowy. Simiwawwy,
device nodes suppowting metadata output intewface set the
``V4W2_CAP_META_OUTPUT`` fwag in the ``device_caps`` fiewd of
:c:type:`v4w2_capabiwity` stwuctuwe. That fwag means the device can wead
metadata fwom memowy.

At weast one of the wead/wwite ow stweaming I/O methods must be suppowted.


Data Fowmat Negotiation
=======================

The metadata device uses the :wef:`fowmat` ioctws to sewect the captuwe fowmat.
The metadata buffew content fowmat is bound to that sewected fowmat. In addition
to the basic :wef:`fowmat` ioctws, the :c:func:`VIDIOC_ENUM_FMT` ioctw must be
suppowted as weww.

To use the :wef:`fowmat` ioctws appwications set the ``type`` fiewd of the
:c:type:`v4w2_fowmat` stwuctuwe to ``V4W2_BUF_TYPE_META_CAPTUWE`` ow to
``V4W2_BUF_TYPE_META_OUTPUT`` and use the :c:type:`v4w2_meta_fowmat` ``meta``
membew of the ``fmt`` union as needed pew the desiwed opewation. Both dwivews
and appwications must set the wemaindew of the :c:type:`v4w2_fowmat` stwuctuwe
to 0.

.. c:type:: v4w2_meta_fowmat

.. tabuwawcowumns:: |p{1.4cm}|p{2.4cm}|p{13.5cm}|

.. fwat-tabwe:: stwuct v4w2_meta_fowmat
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``datafowmat``
      - The data fowmat, set by the appwication. This is a wittwe endian
        :wef:`fouw chawactew code <v4w2-fouwcc>`. V4W2 defines metadata fowmats
        in :wef:`meta-fowmats`.
    * - __u32
      - ``buffewsize``
      - Maximum buffew size in bytes wequiwed fow data. The vawue is set by the
        dwivew.
