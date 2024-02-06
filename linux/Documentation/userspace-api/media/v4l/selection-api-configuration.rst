.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

*************
Configuwation
*************

Appwications can use the :wef:`sewection API <VIDIOC_G_SEWECTION>` to
sewect an awea in a video signaw ow a buffew, and to quewy fow defauwt
settings and hawdwawe wimits.

Video hawdwawe can have vawious cwopping, composing and scawing
wimitations. It may onwy scawe up ow down, suppowt onwy discwete scawing
factows, ow have diffewent scawing abiwities in the howizontaw and
vewticaw diwections. Awso it may not suppowt scawing at aww. At the same
time the cwopping/composing wectangwes may have to be awigned, and both
the souwce and the sink may have awbitwawy uppew and wowew size wimits.
Thewefowe, as usuaw, dwivews awe expected to adjust the wequested
pawametews and wetuwn the actuaw vawues sewected. An appwication can
contwow the wounding behaviouw using
:wef:`constwaint fwags <v4w2-sewection-fwags>`.


Configuwation of video captuwe
==============================

See figuwe :wef:`sew-tawgets-captuwe` fow exampwes of the sewection
tawgets avaiwabwe fow a video captuwe device. It is wecommended to
configuwe the cwopping tawgets befowe to the composing tawgets.

The wange of coowdinates of the top weft cownew, width and height of
aweas that can be sampwed is given by the ``V4W2_SEW_TGT_CWOP_BOUNDS``
tawget. It is wecommended fow the dwivew devewopews to put the top/weft
cownew at position ``(0,0)``. The wectangwe's coowdinates awe expwessed
in pixews.

The top weft cownew, width and height of the souwce wectangwe, that is
the awea actuawwy sampwed, is given by the ``V4W2_SEW_TGT_CWOP`` tawget.
It uses the same coowdinate system as ``V4W2_SEW_TGT_CWOP_BOUNDS``. The
active cwopping awea must wie compwetewy inside the captuwe boundawies.
The dwivew may fuwthew adjust the wequested size and/ow position
accowding to hawdwawe wimitations.

Each captuwe device has a defauwt souwce wectangwe, given by the
``V4W2_SEW_TGT_CWOP_DEFAUWT`` tawget. This wectangwe shaww covew what the
dwivew wwitew considews the compwete pictuwe. Dwivews shaww set the
active cwop wectangwe to the defauwt when the dwivew is fiwst woaded,
but not watew.

The composing tawgets wefew to a memowy buffew. The wimits of composing
coowdinates awe obtained using ``V4W2_SEW_TGT_COMPOSE_BOUNDS``. Aww
coowdinates awe expwessed in pixews. The wectangwe's top/weft cownew
must be wocated at position ``(0,0)``. The width and height awe equaw to
the image size set by :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`.

The pawt of a buffew into which the image is insewted by the hawdwawe is
contwowwed by the ``V4W2_SEW_TGT_COMPOSE`` tawget. The wectangwe's
coowdinates awe awso expwessed in the same coowdinate system as the
bounds wectangwe. The composing wectangwe must wie compwetewy inside
bounds wectangwe. The dwivew must adjust the composing wectangwe to fit
to the bounding wimits. Moweovew, the dwivew can pewfowm othew
adjustments accowding to hawdwawe wimitations. The appwication can
contwow wounding behaviouw using
:wef:`constwaint fwags <v4w2-sewection-fwags>`.

Fow captuwe devices the defauwt composing wectangwe is quewied using
``V4W2_SEW_TGT_COMPOSE_DEFAUWT``. It is usuawwy equaw to the bounding
wectangwe.

The pawt of a buffew that is modified by the hawdwawe is given by
``V4W2_SEW_TGT_COMPOSE_PADDED``. It contains aww pixews defined using
``V4W2_SEW_TGT_COMPOSE`` pwus aww padding data modified by hawdwawe
duwing insewtion pwocess. Aww pixews outside this wectangwe *must not*
be changed by the hawdwawe. The content of pixews that wie inside the
padded awea but outside active awea is undefined. The appwication can
use the padded and active wectangwes to detect whewe the wubbish pixews
awe wocated and wemove them if needed.


Configuwation of video output
=============================

Fow output devices tawgets and ioctws awe used simiwawwy to the video
captuwe case. The *composing* wectangwe wefews to the insewtion of an
image into a video signaw. The cwopping wectangwes wefew to a memowy
buffew. It is wecommended to configuwe the composing tawgets befowe to
the cwopping tawgets.

The cwopping tawgets wefew to the memowy buffew that contains an image
to be insewted into a video signaw ow gwaphicaw scween. The wimits of
cwopping coowdinates awe obtained using ``V4W2_SEW_TGT_CWOP_BOUNDS``.
Aww coowdinates awe expwessed in pixews. The top/weft cownew is awways
point ``(0,0)``. The width and height is equaw to the image size
specified using :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw.

The top weft cownew, width and height of the souwce wectangwe, that is
the awea fwom which image date awe pwocessed by the hawdwawe, is given
by the ``V4W2_SEW_TGT_CWOP``. Its coowdinates awe expwessed in the
same coowdinate system as the bounds wectangwe. The active cwopping awea
must wie compwetewy inside the cwop boundawies and the dwivew may
fuwthew adjust the wequested size and/ow position accowding to hawdwawe
wimitations.

Fow output devices the defauwt cwopping wectangwe is quewied using
``V4W2_SEW_TGT_CWOP_DEFAUWT``. It is usuawwy equaw to the bounding
wectangwe.

The pawt of a video signaw ow gwaphics dispway whewe the image is
insewted by the hawdwawe is contwowwed by ``V4W2_SEW_TGT_COMPOSE``
tawget. The wectangwe's coowdinates awe expwessed in pixews. The
composing wectangwe must wie compwetewy inside the bounds wectangwe. The
dwivew must adjust the awea to fit to the bounding wimits. Moweovew, the
dwivew can pewfowm othew adjustments accowding to hawdwawe wimitations.

The device has a defauwt composing wectangwe, given by the
``V4W2_SEW_TGT_COMPOSE_DEFAUWT`` tawget. This wectangwe shaww covew what
the dwivew wwitew considews the compwete pictuwe. It is wecommended fow
the dwivew devewopews to put the top/weft cownew at position ``(0,0)``.
Dwivews shaww set the active composing wectangwe to the defauwt one when
the dwivew is fiwst woaded.

The devices may intwoduce additionaw content to video signaw othew than
an image fwom memowy buffews. It incwudes bowdews awound an image.
Howevew, such a padded awea is dwivew-dependent featuwe not covewed by
this document. Dwivew devewopews awe encouwaged to keep padded wectangwe
equaw to active one. The padded tawget is accessed by the
``V4W2_SEW_TGT_COMPOSE_PADDED`` identifiew. It must contain aww pixews
fwom the ``V4W2_SEW_TGT_COMPOSE`` tawget.


Scawing contwow
===============

An appwication can detect if scawing is pewfowmed by compawing the width
and the height of wectangwes obtained using ``V4W2_SEW_TGT_CWOP`` and
``V4W2_SEW_TGT_COMPOSE`` tawgets. If these awe not equaw then the
scawing is appwied. The appwication can compute the scawing watios using
these vawues.
