.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _output:

**********************
Video Output Intewface
**********************

Video output devices encode stiwws ow image sequences as anawog video
signaw. With this intewface appwications can contwow the encoding
pwocess and move images fwom usew space to the dwivew.

Conventionawwy V4W2 video output devices awe accessed thwough chawactew
device speciaw fiwes named ``/dev/video`` and ``/dev/video0`` to
``/dev/video63`` with majow numbew 81 and minow numbews 0 to 63.
``/dev/video`` is typicawwy a symbowic wink to the pwefewwed video
device.

.. note:: The same device fiwe names awe used awso fow video captuwe devices.

Quewying Capabiwities
=====================

Devices suppowting the video output intewface set the
``V4W2_CAP_VIDEO_OUTPUT`` ow ``V4W2_CAP_VIDEO_OUTPUT_MPWANE`` fwag in
the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. As secondawy device
functions they may awso suppowt the :wef:`waw VBI output <waw-vbi>`
(``V4W2_CAP_VBI_OUTPUT``) intewface. At weast one of the wead/wwite ow
stweaming I/O methods must be suppowted. Moduwatows and audio outputs
awe optionaw.

Suppwementaw Functions
======================

Video output devices shaww suppowt :wef:`audio output <audio>`,
:wef:`moduwatow <tunew>`, :wef:`contwows <contwow>`,
:wef:`cwopping and scawing <cwop>` and
:wef:`stweaming pawametew <stweaming-paw>` ioctws as needed. The
:wef:`video output <video>` ioctws must be suppowted by aww video
output devices.

Image Fowmat Negotiation
========================

The output is detewmined by cwopping and image fowmat pawametews. The
fowmew sewect an awea of the video pictuwe whewe the image wiww appeaw,
the wattew how images awe stowed in memowy, i. e. in WGB ow YUV fowmat,
the numbew of bits pew pixew ow width and height. Togethew they awso
define how images awe scawed in the pwocess.

As usuaw these pawametews awe *not* weset at :c:func:`open()`
time to pewmit Unix toow chains, pwogwamming a device and then wwiting
to it as if it was a pwain fiwe. Weww wwitten V4W2 appwications ensuwe
they weawwy get what they want, incwuding cwopping and scawing.

Cwopping initiawization at minimum wequiwes to weset the pawametews to
defauwts. An exampwe is given in :wef:`cwop`.

To quewy the cuwwent image fowmat appwications set the ``type`` fiewd of
a stwuct :c:type:`v4w2_fowmat` to
``V4W2_BUF_TYPE_VIDEO_OUTPUT`` ow ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``
and caww the :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` ioctw with a pointew
to this stwuctuwe. Dwivews fiww the stwuct
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
detaiws. Video output devices must impwement both the :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>`
and :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw, even if :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ignowes aww
wequests and awways wetuwns defauwt pawametews as :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` does.
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` is optionaw.

Wwiting Images
==============

A video output device may suppowt the :wef:`wwite() function <ww>`
and/ow stweaming (:wef:`memowy mapping <mmap>` ow
:wef:`usew pointew <usewp>`) I/O. See :wef:`io` fow detaiws.
