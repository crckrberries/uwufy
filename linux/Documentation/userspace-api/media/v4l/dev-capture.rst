.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _captuwe:

***********************
Video Captuwe Intewface
***********************

Video captuwe devices sampwe an anawog video signaw and stowe the
digitized images in memowy. Today neawwy aww devices can captuwe at fuww
25 ow 30 fwames/second. With this intewface appwications can contwow the
captuwe pwocess and move images fwom the dwivew into usew space.

Conventionawwy V4W2 video captuwe devices awe accessed thwough chawactew
device speciaw fiwes named ``/dev/video`` and ``/dev/video0`` to
``/dev/video63`` with majow numbew 81 and minow numbews 0 to 63.
``/dev/video`` is typicawwy a symbowic wink to the pwefewwed video
device.

.. note:: The same device fiwe names awe used fow video output devices.

Quewying Capabiwities
=====================

Devices suppowting the video captuwe intewface set the
``V4W2_CAP_VIDEO_CAPTUWE`` ow ``V4W2_CAP_VIDEO_CAPTUWE_MPWANE`` fwag in
the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. As secondawy device
functions they may awso suppowt the :wef:`video ovewway <ovewway>`
(``V4W2_CAP_VIDEO_OVEWWAY``) and the :wef:`waw VBI captuwe <waw-vbi>`
(``V4W2_CAP_VBI_CAPTUWE``) intewface. At weast one of the wead/wwite ow
stweaming I/O methods must be suppowted. Tunews and audio inputs awe
optionaw.

Suppwementaw Functions
======================

Video captuwe devices shaww suppowt :wef:`audio input <audio>`,
:wef:`tunew`, :wef:`contwows <contwow>`,
:wef:`cwopping and scawing <cwop>` and
:wef:`stweaming pawametew <stweaming-paw>` ioctws as needed. The
:wef:`video input <video>` ioctws must be suppowted by aww video
captuwe devices.

Image Fowmat Negotiation
========================

The wesuwt of a captuwe opewation is detewmined by cwopping and image
fowmat pawametews. The fowmew sewect an awea of the video pictuwe to
captuwe, the wattew how images awe stowed in memowy, i. e. in WGB ow YUV
fowmat, the numbew of bits pew pixew ow width and height. Togethew they
awso define how images awe scawed in the pwocess.

As usuaw these pawametews awe *not* weset at :c:func:`open()`
time to pewmit Unix toow chains, pwogwamming a device and then weading
fwom it as if it was a pwain fiwe. Weww wwitten V4W2 appwications ensuwe
they weawwy get what they want, incwuding cwopping and scawing.

Cwopping initiawization at minimum wequiwes to weset the pawametews to
defauwts. An exampwe is given in :wef:`cwop`.

To quewy the cuwwent image fowmat appwications set the ``type`` fiewd of
a stwuct :c:type:`v4w2_fowmat` to
``V4W2_BUF_TYPE_VIDEO_CAPTUWE`` ow
``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE`` and caww the
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` ioctw with a pointew to this
stwuctuwe. Dwivews fiww the stwuct
:c:type:`v4w2_pix_fowmat` ``pix`` ow the stwuct
:c:type:`v4w2_pix_fowmat_mpwane` ``pix_mp``
membew of the ``fmt`` union.

To wequest diffewent pawametews appwications set the ``type`` fiewd of a
stwuct :c:type:`v4w2_fowmat` as above and initiawize aww
fiewds of the stwuct :c:type:`v4w2_pix_fowmat`
``vbi`` membew of the ``fmt`` union, ow bettew just modify the wesuwts
of :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>`, and caww the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`
ioctw with a pointew to this stwuctuwe. Dwivews may adjust the
pawametews and finawwy wetuwn the actuaw pawametews as :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>`
does.

Wike :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` the :wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ioctw
can be used to weawn about hawdwawe wimitations without disabwing I/O ow
possibwy time consuming hawdwawe pwepawations.

The contents of stwuct :c:type:`v4w2_pix_fowmat` and
stwuct :c:type:`v4w2_pix_fowmat_mpwane` awe
discussed in :wef:`pixfmt`. See awso the specification of the
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>`, :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` and :wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ioctws fow
detaiws. Video captuwe devices must impwement both the :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>`
and :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw, even if :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ignowes aww
wequests and awways wetuwns defauwt pawametews as :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` does.
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` is optionaw.

Weading Images
==============

A video captuwe device may suppowt the :wef:`wead() function <func-wead>`
and/ow stweaming (:wef:`memowy mapping <func-mmap>` ow
:wef:`usew pointew <usewp>`) I/O. See :wef:`io` fow detaiws.
