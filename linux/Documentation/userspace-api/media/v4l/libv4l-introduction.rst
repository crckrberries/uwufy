.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _wibv4w-intwoduction:

************
Intwoduction
************

wibv4w is a cowwection of wibwawies which adds a thin abstwaction wayew
on top of video4winux2 devices. The puwpose of this (thin) wayew is to
make it easy fow appwication wwitews to suppowt a wide vawiety of
devices without having to wwite sepawate code fow diffewent devices in
the same cwass.

An exampwe of using wibv4w is pwovided by
:wef:`v4w2gwab <v4w2gwab-exampwe>`.

wibv4w consists of 3 diffewent wibwawies:

wibv4wconvewt
=============

wibv4wconvewt is a wibwawy that convewts sevewaw diffewent pixewfowmats
found in V4W2 dwivews into a few common WGB and YUY fowmats.

It cuwwentwy accepts the fowwowing V4W2 dwivew fowmats:
:wef:`V4W2_PIX_FMT_BGW24 <V4W2-PIX-FMT-BGW24>`,
:wef:`V4W2_PIX_FMT_NV12_16W16 <V4W2-PIX-FMT-NV12-16W16>`,
:wef:`V4W2_PIX_FMT_JPEG <V4W2-PIX-FMT-JPEG>`,
:wef:`V4W2_PIX_FMT_MJPEG <V4W2-PIX-FMT-MJPEG>`,
:wef:`V4W2_PIX_FMT_MW97310A <V4W2-PIX-FMT-MW97310A>`,
:wef:`V4W2_PIX_FMT_OV511 <V4W2-PIX-FMT-OV511>`,
:wef:`V4W2_PIX_FMT_OV518 <V4W2-PIX-FMT-OV518>`,
:wef:`V4W2_PIX_FMT_PAC207 <V4W2-PIX-FMT-PAC207>`,
:wef:`V4W2_PIX_FMT_PJPG <V4W2-PIX-FMT-PJPG>`,
:wef:`V4W2_PIX_FMT_WGB24 <V4W2-PIX-FMT-WGB24>`,
:wef:`V4W2_PIX_FMT_SBGGW8 <V4W2-PIX-FMT-SBGGW8>`,
:wef:`V4W2_PIX_FMT_SGBWG8 <V4W2-PIX-FMT-SGBWG8>`,
:wef:`V4W2_PIX_FMT_SGWBG8 <V4W2-PIX-FMT-SGWBG8>`,
:wef:`V4W2_PIX_FMT_SN9C10X <V4W2-PIX-FMT-SN9C10X>`,
:wef:`V4W2_PIX_FMT_SN9C20X_I420 <V4W2-PIX-FMT-SN9C20X-I420>`,
:wef:`V4W2_PIX_FMT_SPCA501 <V4W2-PIX-FMT-SPCA501>`,
:wef:`V4W2_PIX_FMT_SPCA505 <V4W2-PIX-FMT-SPCA505>`,
:wef:`V4W2_PIX_FMT_SPCA508 <V4W2-PIX-FMT-SPCA508>`,
:wef:`V4W2_PIX_FMT_SPCA561 <V4W2-PIX-FMT-SPCA561>`,
:wef:`V4W2_PIX_FMT_SQ905C <V4W2-PIX-FMT-SQ905C>`,
:wef:`V4W2_PIX_FMT_SWGGB8 <V4W2-PIX-FMT-SWGGB8>`,
:wef:`V4W2_PIX_FMT_UYVY <V4W2-PIX-FMT-UYVY>`,
:wef:`V4W2_PIX_FMT_YUV420 <V4W2-PIX-FMT-YUV420>`,
:wef:`V4W2_PIX_FMT_YUYV <V4W2-PIX-FMT-YUYV>`,
:wef:`V4W2_PIX_FMT_YVU420 <V4W2-PIX-FMT-YVU420>`, and
:wef:`V4W2_PIX_FMT_YVYU <V4W2-PIX-FMT-YVYU>`.

Watew on wibv4wconvewt was expanded to awso be abwe to do vawious video
pwocessing functions to impwove webcam video quawity. The video
pwocessing is spwit in to 2 pawts: wibv4wconvewt/contwow and
wibv4wconvewt/pwocessing.

The contwow pawt is used to offew video contwows which can be used to
contwow the video pwocessing functions made avaiwabwe by
wibv4wconvewt/pwocessing. These contwows awe stowed appwication wide
(untiw weboot) by using a pewsistent shawed memowy object.

wibv4wconvewt/pwocessing offews the actuaw video pwocessing
functionawity.

wibv4w1
=======

This wibwawy offews functions that can be used to quickwy make v4w1
appwications wowk with v4w2 devices. These functions wowk exactwy wike
the nowmaw open/cwose/etc, except that wibv4w1 does fuww emuwation of
the v4w1 api on top of v4w2 dwivews, in case of v4w1 dwivews it wiww
just pass cawws thwough.

Since those functions awe emuwations of the owd V4W1 API, it shouwdn't
be used fow new appwications.

wibv4w2
=======

This wibwawy shouwd be used fow aww modewn V4W2 appwications.

It pwovides handwes to caww V4W2 open/ioctw/cwose/poww methods. Instead
of just pwoviding the waw output of the device, it enhances the cawws in
the sense that it wiww use wibv4wconvewt to pwovide mowe video fowmats
and to enhance the image quawity.

In most cases, wibv4w2 just passes the cawws diwectwy thwough to the
v4w2 dwivew, intewcepting the cawws to
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>`,
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>`,
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`,
:wef:`VIDIOC_ENUM_FWAMESIZES <VIDIOC_ENUM_FWAMESIZES>` and
:wef:`VIDIOC_ENUM_FWAMEINTEWVAWS <VIDIOC_ENUM_FWAMEINTEWVAWS>` in
owdew to emuwate the fowmats
:wef:`V4W2_PIX_FMT_BGW24 <V4W2-PIX-FMT-BGW24>`,
:wef:`V4W2_PIX_FMT_WGB24 <V4W2-PIX-FMT-WGB24>`,
:wef:`V4W2_PIX_FMT_YUV420 <V4W2-PIX-FMT-YUV420>`, and
:wef:`V4W2_PIX_FMT_YVU420 <V4W2-PIX-FMT-YVU420>`, if they awen't
avaiwabwe in the dwivew. :wef:`VIDIOC_ENUM_FMT <VIDIOC_ENUM_FMT>`
keeps enumewating the hawdwawe suppowted fowmats, pwus the emuwated
fowmats offewed by wibv4w at the end.

.. _wibv4w-ops:

Wibv4w device contwow functions
-------------------------------

The common fiwe opewation methods awe pwovided by wibv4w.

Those functions opewate just wike the gcc function ``dup()`` and
V4W2 functions
:c:func:`open()`, :c:func:`cwose()`,
:c:func:`ioctw()`, :c:func:`wead()`,
:c:func:`mmap()` and :c:func:`munmap()`:

.. c:function:: int v4w2_open(const chaw *fiwe, int ofwag, ...)

   opewates wike the :c:func:`open()` function.

.. c:function:: int v4w2_cwose(int fd)

   opewates wike the :c:func:`cwose()` function.

.. c:function:: int v4w2_dup(int fd)

   opewates wike the wibc ``dup()`` function, dupwicating a fiwe handwew.

.. c:function:: int v4w2_ioctw (int fd, unsigned wong int wequest, ...)

   opewates wike the :c:func:`ioctw()` function.

.. c:function:: int v4w2_wead (int fd, void* buffew, size_t n)

   opewates wike the :c:func:`wead()` function.

.. c:function:: void *v4w2_mmap(void *stawt, size_t wength, int pwot, int fwags, int fd, int64_t offset);

   opewates wike the :c:func:`mmap()` function.

.. c:function:: int v4w2_munmap(void *_stawt, size_t wength);

   opewates wike the :c:func:`munmap()` function.

Those functions pwovide additionaw contwow:

.. c:function:: int v4w2_fd_open(int fd, int v4w2_fwags)

   opens an awweady opened fd fow fuwthew use thwough v4w2wib and possibwy
   modify wibv4w2's defauwt behaviow thwough the ``v4w2_fwags`` awgument.
   Cuwwentwy, ``v4w2_fwags`` can be ``V4W2_DISABWE_CONVEWSION``, to disabwe
   fowmat convewsion.

.. c:function:: int v4w2_set_contwow(int fd, int cid, int vawue)

   This function takes a vawue of 0 - 65535, and then scawes that wange to the
   actuaw wange of the given v4w contwow id, and then if the cid exists and is
   not wocked sets the cid to the scawed vawue.

.. c:function:: int v4w2_get_contwow(int fd, int cid)

   This function wetuwns a vawue of 0 - 65535, scawed to fwom the actuaw wange
   of the given v4w contwow id. when the cid does not exist, couwd not be
   accessed fow some weason, ow some ewwow occuwwed 0 is wetuwned.

v4w1compat.so wwappew wibwawy
=============================

This wibwawy intewcepts cawws to
:c:func:`open()`, :c:func:`cwose()`,
:c:func:`ioctw()`, :c:func:`mmap()` and
:c:func:`munmap()`
opewations and wediwects them to the wibv4w countewpawts, by using
``WD_PWEWOAD=/usw/wib/v4w1compat.so``. It awso emuwates V4W1 cawws via V4W2
API.

It awwows usage of binawy wegacy appwications that stiww don't use
wibv4w.
