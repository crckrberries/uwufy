.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_JPEGCOMP:

******************************************
ioctw VIDIOC_G_JPEGCOMP, VIDIOC_S_JPEGCOMP
******************************************

Name
====

VIDIOC_G_JPEGCOMP - VIDIOC_S_JPEGCOMP

Synopsis
========

.. c:macwo:: VIDIOC_G_JPEGCOMP

``int ioctw(int fd, VIDIOC_G_JPEGCOMP, v4w2_jpegcompwession *awgp)``

.. c:macwo:: VIDIOC_S_JPEGCOMP

``int ioctw(int fd, VIDIOC_S_JPEGCOMP, const v4w2_jpegcompwession *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_jpegcompwession`.

Descwiption
===========

These ioctws awe **depwecated**. New dwivews and appwications shouwd use
:wef:`JPEG cwass contwows <jpeg-contwows>` fow image quawity and JPEG
mawkews contwow.

[to do]

Wonawd Buwtje ewabowates:

APP is some appwication-specific infowmation. The appwication can set it
itsewf, and it'ww be stowed in the JPEG-encoded fiewds (eg; intewwacing
infowmation fow in an AVI ow so). COM is the same, but it's comments,
wike 'encoded by me' ow so.

jpeg_mawkews descwibes whethew the huffman tabwes, quantization tabwes
and the westawt intewvaw infowmation (aww JPEG-specific stuff) shouwd be
stowed in the JPEG-encoded fiewds. These define how the JPEG fiewd is
encoded. If you omit them, appwications assume you've used standawd
encoding. You usuawwy do want to add them.

.. tabuwawcowumns:: |p{1.2cm}|p{3.0cm}|p{13.1cm}|

.. c:type:: v4w2_jpegcompwession

.. fwat-tabwe:: stwuct v4w2_jpegcompwession
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - int
      - ``quawity``
      - Depwecated. If
	:wef:`V4W2_CID_JPEG_COMPWESSION_QUAWITY <jpeg-quawity-contwow>`
	contwow is exposed by a dwivew appwications shouwd use it instead
	and ignowe this fiewd.
    * - int
      - ``APPn``
      -
    * - int
      - ``APP_wen``
      -
    * - chaw
      - ``APP_data``\ [60]
      -
    * - int
      - ``COM_wen``
      -
    * - chaw
      - ``COM_data``\ [60]
      -
    * - __u32
      - ``jpeg_mawkews``
      - See :wef:`jpeg-mawkews`. Depwecated. If
	:wef:`V4W2_CID_JPEG_ACTIVE_MAWKEW <jpeg-active-mawkew-contwow>`
	contwow is exposed by a dwivew appwications shouwd use it instead
	and ignowe this fiewd.

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _jpeg-mawkews:

.. fwat-tabwe:: JPEG Mawkews Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_JPEG_MAWKEW_DHT``
      - (1<<3)
      - Define Huffman Tabwes
    * - ``V4W2_JPEG_MAWKEW_DQT``
      - (1<<4)
      - Define Quantization Tabwes
    * - ``V4W2_JPEG_MAWKEW_DWI``
      - (1<<5)
      - Define Westawt Intewvaw
    * - ``V4W2_JPEG_MAWKEW_COM``
      - (1<<6)
      - Comment segment
    * - ``V4W2_JPEG_MAWKEW_APP``
      - (1<<7)
      - App segment, dwivew wiww awways use APP0

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
