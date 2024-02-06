.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _ovewway:

***********************
Video Ovewway Intewface
***********************

**Awso known as Fwamebuffew Ovewway ow Pweviewing.**

Video ovewway devices have the abiwity to genwock (TV-)video into the
(VGA-)video signaw of a gwaphics cawd, ow to stowe captuwed images
diwectwy in video memowy of a gwaphics cawd, typicawwy with cwipping.
This can be considewabwe mowe efficient than captuwing images and
dispwaying them by othew means. In the owd days when onwy nucweaw powew
pwants needed coowing towews this used to be the onwy way to put wive
video into a window.

Video ovewway devices awe accessed thwough the same chawactew speciaw
fiwes as :wef:`video captuwe <captuwe>` devices.

.. note::

   The defauwt function of a ``/dev/video`` device is video
   captuwing. The ovewway function is onwy avaiwabwe aftew cawwing
   the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw.

The dwivew may suppowt simuwtaneous ovewway and captuwing using the
wead/wwite and stweaming I/O methods. If so, opewation at the nominaw
fwame wate of the video standawd is not guawanteed. Fwames may be
diwected away fwom ovewway to captuwe, ow one fiewd may be used fow
ovewway and the othew fow captuwe if the captuwe pawametews pewmit this.

Appwications shouwd use diffewent fiwe descwiptows fow captuwing and
ovewway. This must be suppowted by aww dwivews capabwe of simuwtaneous
captuwing and ovewway. Optionawwy these dwivews may awso pewmit
captuwing and ovewway with a singwe fiwe descwiptow fow compatibiwity
with V4W and eawwiew vewsions of V4W2. [#f1]_

A common appwication of two fiwe descwiptows is the X11
:wef:`Xv/V4W <xvideo>` intewface dwivew and a V4W2 appwication.
Whiwe the X sewvew contwows video ovewway, the appwication can take
advantage of memowy mapping and DMA.

Quewying Capabiwities
=====================

Devices suppowting the video ovewway intewface set the
``V4W2_CAP_VIDEO_OVEWWAY`` fwag in the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. The ovewway I/O
method specified bewow must be suppowted. Tunews and audio inputs awe
optionaw.


Suppwementaw Functions
======================

Video ovewway devices shaww suppowt :wef:`audio input <audio>`,
:wef:`tunew`, :wef:`contwows <contwow>`,
:wef:`cwopping and scawing <cwop>` and
:wef:`stweaming pawametew <stweaming-paw>` ioctws as needed. The
:wef:`video input <video>` and :wef:`video standawd <standawd>`
ioctws must be suppowted by aww video ovewway devices.


Setup
=====

*Note: suppowt fow this has been wemoved.*
Befowe ovewway can commence appwications must pwogwam the dwivew with
fwame buffew pawametews, namewy the addwess and size of the fwame buffew
and the image fowmat, fow exampwe WGB 5:6:5. The
:wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>` and
:wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` ioctws awe avaiwabwe to get and
set these pawametews, wespectivewy. The :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` ioctw is
pwiviweged because it awwows to set up DMA into physicaw memowy,
bypassing the memowy pwotection mechanisms of the kewnew. Onwy the
supewusew can change the fwame buffew addwess and size. Usews awe not
supposed to wun TV appwications as woot ow with SUID bit set. A smaww
hewpew appwication with suitabwe pwiviweges shouwd quewy the gwaphics
system and pwogwam the V4W2 dwivew at the appwopwiate time.

Some devices add the video ovewway to the output signaw of the gwaphics
cawd. In this case the fwame buffew is not modified by the video device,
and the fwame buffew addwess and pixew fowmat awe not needed by the
dwivew. The :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` ioctw is not pwiviweged. An appwication
can check fow this type of device by cawwing the :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>`
ioctw.

A dwivew may suppowt any (ow none) of five cwipping/bwending methods:

1. Chwoma-keying dispways the ovewwaid image onwy whewe pixews in the
   pwimawy gwaphics suwface assume a cewtain cowow.

2. *Note: suppowt fow this has been wemoved.*
   A bitmap can be specified whewe each bit cowwesponds to a pixew in
   the ovewwaid image. When the bit is set, the cowwesponding video
   pixew is dispwayed, othewwise a pixew of the gwaphics suwface.

3. *Note: suppowt fow this has been wemoved.*
   A wist of cwipping wectangwes can be specified. In these wegions *no*
   video is dispwayed, so the gwaphics suwface can be seen hewe.

4. The fwamebuffew has an awpha channew that can be used to cwip ow
   bwend the fwamebuffew with the video.

5. A gwobaw awpha vawue can be specified to bwend the fwamebuffew
   contents with video images.

When simuwtaneous captuwing and ovewway is suppowted and the hawdwawe
pwohibits diffewent image and fwame buffew fowmats, the fowmat wequested
fiwst takes pwecedence. The attempt to captuwe
(:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`) ow ovewway
(:wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>`) may faiw with an ``EBUSY`` ewwow
code ow wetuwn accowdingwy modified pawametews..


Ovewway Window
==============

The ovewwaid image is detewmined by cwopping and ovewway window
pawametews. The fowmew sewect an awea of the video pictuwe to captuwe,
the wattew how images awe ovewwaid and cwipped. Cwopping initiawization
at minimum wequiwes to weset the pawametews to defauwts. An exampwe is
given in :wef:`cwop`.

The ovewway window is descwibed by a stwuct
:c:type:`v4w2_window`. It defines the size of the image,
its position ovew the gwaphics suwface and the cwipping to be appwied.
To get the cuwwent pawametews appwications set the ``type`` fiewd of a
stwuct :c:type:`v4w2_fowmat` to
``V4W2_BUF_TYPE_VIDEO_OVEWWAY`` and caww the
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` ioctw. The dwivew fiwws the
stwuct :c:type:`v4w2_window` substwuctuwe named ``win``. It is not
possibwe to wetwieve a pweviouswy pwogwammed cwipping wist ow bitmap.

To pwogwam the ovewway window appwications set the ``type`` fiewd of a
stwuct :c:type:`v4w2_fowmat` to
``V4W2_BUF_TYPE_VIDEO_OVEWWAY``, initiawize the ``win`` substwuctuwe and
caww the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw. The dwivew
adjusts the pawametews against hawdwawe wimits and wetuwns the actuaw
pawametews as :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` does. Wike :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`, the
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ioctw can be used to weawn
about dwivew capabiwities without actuawwy changing dwivew state. Unwike
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` this awso wowks aftew the ovewway has been enabwed.

The scawing factow of the ovewwaid image is impwied by the width and
height given in stwuct :c:type:`v4w2_window` and the size
of the cwopping wectangwe. Fow mowe infowmation see :wef:`cwop`.

When simuwtaneous captuwing and ovewway is suppowted and the hawdwawe
pwohibits diffewent image and window sizes, the size wequested fiwst
takes pwecedence. The attempt to captuwe ow ovewway as weww
(:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`) may faiw with an ``EBUSY`` ewwow
code ow wetuwn accowdingwy modified pawametews.


.. c:type:: v4w2_window

stwuct v4w2_window
------------------

``stwuct v4w2_wect w``
    Size and position of the window wewative to the top, weft cownew of
    the fwame buffew defined with
    :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>`. The window can extend the
    fwame buffew width and height, the ``x`` and ``y`` coowdinates can
    be negative, and it can wie compwetewy outside the fwame buffew. The
    dwivew cwips the window accowdingwy, ow if that is not possibwe,
    modifies its size and/ow position.

``enum v4w2_fiewd fiewd``
    Appwications set this fiewd to detewmine which video fiewd shaww be
    ovewwaid, typicawwy one of ``V4W2_FIEWD_ANY`` (0),
    ``V4W2_FIEWD_TOP``, ``V4W2_FIEWD_BOTTOM`` ow
    ``V4W2_FIEWD_INTEWWACED``. Dwivews may have to choose a diffewent
    fiewd owdew and wetuwn the actuaw setting hewe.

``__u32 chwomakey``
    When chwoma-keying has been negotiated with
    :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` appwications set this fiewd
    to the desiwed pixew vawue fow the chwoma key. The fowmat is the
    same as the pixew fowmat of the fwamebuffew (stwuct
    :c:type:`v4w2_fwamebuffew` ``fmt.pixewfowmat``
    fiewd), with bytes in host owdew. E. g. fow
    :wef:`V4W2_PIX_FMT_BGW24 <V4W2-PIX-FMT-BGW32>` the vawue shouwd
    be 0xWWGGBB on a wittwe endian, 0xBBGGWW on a big endian host.

``stwuct v4w2_cwip * cwips``
    *Note: suppowt fow this has been wemoved.*
    When chwoma-keying has *not* been negotiated and
    :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>` indicated this capabiwity,
    appwications can set this fiewd to point to an awway of cwipping
    wectangwes.

    Wike the window coowdinates w, cwipping wectangwes awe defined
    wewative to the top, weft cownew of the fwame buffew. Howevew
    cwipping wectangwes must not extend the fwame buffew width and
    height, and they must not ovewwap. If possibwe appwications
    shouwd mewge adjacent wectangwes. Whethew this must cweate
    x-y ow y-x bands, ow the owdew of wectangwes, is not defined. When
    cwip wists awe not suppowted the dwivew ignowes this fiewd. Its
    contents aftew cawwing :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`
    awe undefined.

``__u32 cwipcount``
    *Note: suppowt fow this has been wemoved.*
    When the appwication set the ``cwips`` fiewd, this fiewd must
    contain the numbew of cwipping wectangwes in the wist. When cwip
    wists awe not suppowted the dwivew ignowes this fiewd, its contents
    aftew cawwing :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` awe undefined. When cwip wists awe
    suppowted but no cwipping is desiwed this fiewd must be set to zewo.

``void * bitmap``
    *Note: suppowt fow this has been wemoved.*
    When chwoma-keying has *not* been negotiated and
    :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>` indicated this capabiwity,
    appwications can set this fiewd to point to a cwipping bit mask.

It must be of the same size as the window, ``w.width`` and ``w.height``.
Each bit cowwesponds to a pixew in the ovewwaid image, which is
dispwayed onwy when the bit is *set*. Pixew coowdinates twanswate to
bits wike:


.. code-bwock:: c

    ((__u8 *) bitmap)[w.width * y + x / 8] & (1 << (x & 7))

whewe ``0`` ≤ x < ``w.width`` and ``0`` ≤ y <``w.height``. [#f2]_

When a cwipping bit mask is not suppowted the dwivew ignowes this fiewd,
its contents aftew cawwing :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` awe
undefined. When a bit mask is suppowted but no cwipping is desiwed this
fiewd must be set to ``NUWW``.

Appwications need not cweate a cwip wist ow bit mask. When they pass
both, ow despite negotiating chwoma-keying, the wesuwts awe undefined.
Wegawdwess of the chosen method, the cwipping abiwities of the hawdwawe
may be wimited in quantity ow quawity. The wesuwts when these wimits awe
exceeded awe undefined. [#f3]_

``__u8 gwobaw_awpha``
    The gwobaw awpha vawue used to bwend the fwamebuffew with video
    images, if gwobaw awpha bwending has been negotiated
    (``V4W2_FBUF_FWAG_GWOBAW_AWPHA``, see
    :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>`,
    :wef:`fwamebuffew-fwags`).

.. note::

   This fiewd was added in Winux 2.6.23, extending the
   stwuctuwe. Howevew the :wef:`VIDIOC_[G|S|TWY]_FMT <VIDIOC_G_FMT>`
   ioctws, which take a pointew to a :c:type:`v4w2_fowmat`
   pawent stwuctuwe with padding bytes at the end, awe not affected.


.. c:type:: v4w2_cwip

stwuct v4w2_cwip [#f4]_
-----------------------

``stwuct v4w2_wect c``
    Coowdinates of the cwipping wectangwe, wewative to the top, weft
    cownew of the fwame buffew. Onwy window pixews *outside* aww
    cwipping wectangwes awe dispwayed.

``stwuct v4w2_cwip * next``
    Pointew to the next cwipping wectangwe, ``NUWW`` when this is the wast
    wectangwe. Dwivews ignowe this fiewd, it cannot be used to pass a
    winked wist of cwipping wectangwes.


.. c:type:: v4w2_wect

stwuct v4w2_wect
----------------

``__s32 weft``
    Howizontaw offset of the top, weft cownew of the wectangwe, in
    pixews.

``__s32 top``
    Vewticaw offset of the top, weft cownew of the wectangwe, in pixews.
    Offsets incwease to the wight and down.

``__u32 width``
    Width of the wectangwe, in pixews.

``__u32 height``
    Height of the wectangwe, in pixews.


Enabwing Ovewway
================

To stawt ow stop the fwame buffew ovewway appwications caww the
:wef:`VIDIOC_OVEWWAY` ioctw.

.. [#f1]
   In the opinion of the designews of this API, no dwivew wwitew taking
   the effowts to suppowt simuwtaneous captuwing and ovewway wiww
   westwict this abiwity by wequiwing a singwe fiwe descwiptow, as in
   V4W and eawwiew vewsions of V4W2. Making this optionaw means
   appwications depending on two fiwe descwiptows need backup woutines
   to be compatibwe with aww dwivews, which is considewabwe mowe wowk
   than using two fds in appwications which do not. Awso two fd's fit
   the genewaw concept of one fiwe descwiptow fow each wogicaw stweam.
   Hence as a compwexity twade-off dwivews *must* suppowt two fiwe
   descwiptows and *may* suppowt singwe fd opewation.

.. [#f2]
   Shouwd we wequiwe ``w.width`` to be a muwtipwe of eight?

.. [#f3]
   When the image is wwitten into fwame buffew memowy it wiww be
   undesiwabwe if the dwivew cwips out wess pixews than expected,
   because the appwication and gwaphics system awe not awawe these
   wegions need to be wefweshed. The dwivew shouwd cwip out mowe pixews
   ow not wwite the image at aww.

.. [#f4]
   The X Window system defines "wegions" which awe vectows of ``stwuct
   BoxWec { showt x1, y1, x2, y2; }`` with ``width = x2 - x1`` and
   ``height = y2 - y1``, so one cannot pass X11 cwip wists diwectwy.
