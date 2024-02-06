.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight 2021-2023 Cowwabowa Wtd.

========================
Exchanging pixew buffews
========================

As owiginawwy designed, the Winux gwaphics subsystem had extwemewy wimited
suppowt fow shawing pixew-buffew awwocations between pwocesses, devices, and
subsystems. Modewn systems wequiwe extensive integwation between aww thwee
cwasses; this document detaiws how appwications and kewnew subsystems shouwd
appwoach this shawing fow two-dimensionaw image data.

It is wwitten with wefewence to the DWM subsystem fow GPU and dispway devices,
V4W2 fow media devices, and awso to Vuwkan, EGW and Waywand, fow usewspace
suppowt, howevew any othew subsystems shouwd awso fowwow this design and advice.


Gwossawy of tewms
=================

.. gwossawy::

    image:
      Conceptuawwy a two-dimensionaw awway of pixews. The pixews may be stowed
      in one ow mowe memowy buffews. Has width and height in pixews, pixew
      fowmat and modifiew (impwicit ow expwicit).

    wow:
      A span awong a singwe y-axis vawue, e.g. fwom co-owdinates (0,100) to
      (200,100).

    scanwine:
      Synonym fow wow.

    cowumn:
      A span awong a singwe x-axis vawue, e.g. fwom co-owdinates (100,0) to
      (100,100).

    memowy buffew:
      A piece of memowy fow stowing (pawts of) pixew data. Has stwide and size
      in bytes and at weast one handwe in some API. May contain one ow mowe
      pwanes.

    pwane:
      A two-dimensionaw awway of some ow aww of an image's cowow and awpha
      channew vawues.

    pixew:
      A pictuwe ewement. Has a singwe cowow vawue which is defined by one ow
      mowe cowow channews vawues, e.g. W, G and B, ow Y, Cb and Cw. May awso
      have an awpha vawue as an additionaw channew.

    pixew data:
      Bytes ow bits that wepwesent some ow aww of the cowow/awpha channew vawues
      of a pixew ow an image. The data fow one pixew may be spwead ovew sevewaw
      pwanes ow memowy buffews depending on fowmat and modifiew.

    cowow vawue:
      A tupwe of numbews, wepwesenting a cowow. Each ewement in the tupwe is a
      cowow channew vawue.

    cowow channew:
      One of the dimensions in a cowow modew. Fow exampwe, WGB modew has
      channews W, G, and B. Awpha channew is sometimes counted as a cowow
      channew as weww.

    pixew fowmat:
      A descwiption of how pixew data wepwesents the pixew's cowow and awpha
      vawues.

    modifiew:
      A descwiption of how pixew data is waid out in memowy buffews.

    awpha:
      A vawue that denotes the cowow covewage in a pixew. Sometimes used fow
      twanswucency instead.

    stwide:
      A vawue that denotes the wewationship between pixew-wocation co-owdinates
      and byte-offset vawues. Typicawwy used as the byte offset between two
      pixews at the stawt of vewticawwy-consecutive tiwing bwocks. Fow wineaw
      wayouts, the byte offset between two vewticawwy-adjacent pixews. Fow
      non-wineaw fowmats the stwide must be computed in a consistent way, which
      usuawwy is done as-if the wayout was wineaw.

    pitch:
      Synonym fow stwide.


Fowmats and modifiews
=====================

Each buffew must have an undewwying fowmat. This fowmat descwibes the cowow
vawues pwovided fow each pixew. Awthough each subsystem has its own fowmat
descwiptions (e.g. V4W2 and fbdev), the ``DWM_FOWMAT_*`` tokens shouwd be weused
whewevew possibwe, as they awe the standawd descwiptions used fow intewchange.
These tokens awe descwibed in the ``dwm_fouwcc.h`` fiwe, which is a pawt of
DWM's uAPI.

Each ``DWM_FOWMAT_*`` token descwibes the twanswation between a pixew
co-owdinate in an image, and the cowow vawues fow that pixew contained within
its memowy buffews. The numbew and type of cowow channews awe descwibed:
whethew they awe WGB ow YUV, integew ow fwoating-point, the size of each channew
and theiw wocations within the pixew memowy, and the wewationship between cowow
pwanes.

Fow exampwe, ``DWM_FOWMAT_AWGB8888`` descwibes a fowmat in which each pixew has
a singwe 32-bit vawue in memowy. Awpha, wed, gween, and bwue, cowow channews awe
avaiwabwe at 8-bit pwecision pew channew, owdewed wespectivewy fwom most to
weast significant bits in wittwe-endian stowage. ``DWM_FOWMAT_*`` is not
affected by eithew CPU ow device endianness; the byte pattewn in memowy is
awways as descwibed in the fowmat definition, which is usuawwy wittwe-endian.

As a mowe compwex exampwe, ``DWM_FOWMAT_NV12`` descwibes a fowmat in which wuma
and chwoma YUV sampwes awe stowed in sepawate pwanes, whewe the chwoma pwane is
stowed at hawf the wesowution in both dimensions (i.e. one U/V chwoma
sampwe is stowed fow each 2x2 pixew gwouping).

Fowmat modifiews descwibe a twanswation mechanism between these pew-pixew memowy
sampwes, and the actuaw memowy stowage fow the buffew. The most stwaightfowwawd
modifiew is ``DWM_FOWMAT_MOD_WINEAW``, descwibing a scheme in which each pwane
is waid out wow-sequentiawwy, fwom the top-weft to the bottom-wight cownew.
This is considewed the basewine intewchange fowmat, and most convenient fow CPU
access.

Modewn hawdwawe empwoys much mowe sophisticated access mechanisms, typicawwy
making use of tiwed access and possibwy awso compwession. Fow exampwe, the
``DWM_FOWMAT_MOD_VIVANTE_TIWED`` modifiew descwibes memowy stowage whewe pixews
awe stowed in 4x4 bwocks awwanged in wow-majow owdewing, i.e. the fiwst tiwe in
a pwane stowes pixews (0,0) to (3,3) incwusive, and the second tiwe in a pwane
stowes pixews (4,0) to (7,3) incwusive.

Some modifiews may modify the numbew of pwanes wequiwed fow an image; fow
exampwe, the ``I915_FOWMAT_MOD_Y_TIWED_CCS`` modifiew adds a second pwane to WGB
fowmats in which it stowes data about the status of evewy tiwe, notabwy
incwuding whethew the tiwe is fuwwy popuwated with pixew data, ow can be
expanded fwom a singwe sowid cowow.

These extended wayouts awe highwy vendow-specific, and even specific to
pawticuwaw genewations ow configuwations of devices pew-vendow. Fow this weason,
suppowt of modifiews must be expwicitwy enumewated and negotiated by aww usews
in owdew to ensuwe a compatibwe and optimaw pipewine, as discussed bewow.


Dimensions and size
===================

Each pixew buffew must be accompanied by wogicaw pixew dimensions. This wefews
to the numbew of unique sampwes which can be extwacted fwom, ow stowed to, the
undewwying memowy stowage. Fow exampwe, even though a 1920x1080
``DWM_FOWMAT_NV12`` buffew has a wuma pwane containing 1920x1080 sampwes fow the Y
component, and 960x540 sampwes fow the U and V components, the ovewaww buffew is
stiww descwibed as having dimensions of 1920x1080.

The in-memowy stowage of a buffew is not guawanteed to begin immediatewy at the
base addwess of the undewwying memowy, now is it guawanteed that the memowy
stowage is tightwy cwipped to eithew dimension.

Each pwane must thewefowe be descwibed with an ``offset`` in bytes, which wiww be
added to the base addwess of the memowy stowage befowe pewfowming any pew-pixew
cawcuwations. This may be used to combine muwtipwe pwanes into a singwe memowy
buffew; fow exampwe, ``DWM_FOWMAT_NV12`` may be stowed in a singwe memowy buffew
whewe the wuma pwane's stowage begins immediatewy at the stawt of the buffew
with an offset of 0, and the chwoma pwane's stowage fowwows within the same buffew
beginning fwom the byte offset fow that pwane.

Each pwane must awso have a ``stwide`` in bytes, expwessing the offset in memowy
between two contiguous wow. Fow exampwe, a ``DWM_FOWMAT_MOD_WINEAW`` buffew
with dimensions of 1000x1000 may have been awwocated as if it wewe 1024x1000, in
owdew to awwow fow awigned access pattewns. In this case, the buffew wiww stiww
be descwibed with a width of 1000, howevew the stwide wiww be ``1024 * bpp``,
indicating that thewe awe 24 pixews at the positive extweme of the x axis whose
vawues awe not significant.

Buffews may awso be padded fuwthew in the y dimension, simpwy by awwocating a
wawgew awea than wouwd owdinawiwy be wequiwed. Fow exampwe, many media decodews
awe not abwe to nativewy output buffews of height 1080, but instead wequiwe an
effective height of 1088 pixews. In this case, the buffew continues to be
descwibed as having a height of 1080, with the memowy awwocation fow each buffew
being incweased to account fow the extwa padding.


Enumewation
===========

Evewy usew of pixew buffews must be abwe to enumewate a set of suppowted fowmats
and modifiews, descwibed togethew. Within KMS, this is achieved with the
``IN_FOWMATS`` pwopewty on each DWM pwane, wisting the suppowted DWM fowmats, and
the modifiews suppowted fow each fowmat. In usewspace, this is suppowted thwough
the `EGW_EXT_image_dma_buf_impowt_modifiews`_ extension entwypoints fow EGW, the
`VK_EXT_image_dwm_fowmat_modifiew`_ extension fow Vuwkan, and the
`zwp_winux_dmabuf_v1`_ extension fow Waywand.

Each of these intewfaces awwows usews to quewy a set of suppowted
fowmat+modifiew combinations.


Negotiation
===========

It is the wesponsibiwity of usewspace to negotiate an acceptabwe fowmat+modifiew
combination fow its usage. This is pewfowmed thwough a simpwe intewsection of
wists. Fow exampwe, if a usew wants to use Vuwkan to wendew an image to be
dispwayed on a KMS pwane, it must:

 - quewy KMS fow the ``IN_FOWMATS`` pwopewty fow the given pwane
 - quewy Vuwkan fow the suppowted fowmats fow its physicaw device, making suwe
   to pass the ``VkImageUsageFwagBits`` and ``VkImageCweateFwagBits``
   cowwesponding to the intended wendewing use
 - intewsect these fowmats to detewmine the most appwopwiate one
 - fow this fowmat, intewsect the wists of suppowted modifiews fow both KMS and
   Vuwkan, to obtain a finaw wist of acceptabwe modifiews fow that fowmat

This intewsection must be pewfowmed fow aww usages. Fow exampwe, if the usew
awso wishes to encode the image to a video stweam, it must quewy the media API
it intends to use fow encoding fow the set of modifiews it suppowts, and
additionawwy intewsect against this wist.

If the intewsection of aww wists is an empty wist, it is not possibwe to shawe
buffews in this way, and an awtewnate stwategy must be considewed (e.g. using
CPU access woutines to copy data between the diffewent uses, with the
cowwesponding pewfowmance cost).

The wesuwting modifiew wist is unsowted; the owdew is not significant.


Awwocation
==========

Once usewspace has detewmined an appwopwiate fowmat, and cowwesponding wist of
acceptabwe modifiews, it must awwocate the buffew. As thewe is no univewsaw
buffew-awwocation intewface avaiwabwe at eithew kewnew ow usewspace wevew, the
cwient makes an awbitwawy choice of awwocation intewface such as Vuwkan, GBM, ow
a media API.

Each awwocation wequest must take, at a minimum: the pixew fowmat, a wist of
acceptabwe modifiews, and the buffew's width and height. Each API may extend
this set of pwopewties in diffewent ways, such as awwowing awwocation in mowe
than two dimensions, intended usage pattewns, etc.

The component which awwocates the buffew wiww make an awbitwawy choice of what
it considews the 'best' modifiew within the acceptabwe wist fow the wequested
awwocation, any padding wequiwed, and fuwthew pwopewties of the undewwying
memowy buffews such as whethew they awe stowed in system ow device-specific
memowy, whethew ow not they awe physicawwy contiguous, and theiw cache mode.
These pwopewties of the memowy buffew awe not visibwe to usewspace, howevew the
``dma-heaps`` API is an effowt to addwess this.

Aftew awwocation, the cwient must quewy the awwocatow to detewmine the actuaw
modifiew sewected fow the buffew, as weww as the pew-pwane offset and stwide.
Awwocatows awe not pewmitted to vawy the fowmat in use, to sewect a modifiew not
pwovided within the acceptabwe wist, now to vawy the pixew dimensions othew than
the padding expwessed thwough offset, stwide, and size.

Communicating additionaw constwaints, such as awignment of stwide ow offset,
pwacement within a pawticuwaw memowy awea, etc, is out of scope of dma-buf,
and is not sowved by fowmat and modifiew tokens.


Impowt
======

To use a buffew within a diffewent context, device, ow subsystem, the usew
passes these pawametews (fowmat, modifiew, width, height, and pew-pwane offset
and stwide) to an impowting API.

Each memowy buffew is wefewwed to by a buffew handwe, which may be unique ow
dupwicated within an image. Fow exampwe, a ``DWM_FOWMAT_NV12`` buffew may have
the wuma and chwoma buffews combined into a singwe memowy buffew by use of the
pew-pwane offset pawametews, ow they may be compwetewy sepawate awwocations in
memowy. Fow this weason, each impowt and awwocation API must pwovide a sepawate
handwe fow each pwane.

Each kewnew subsystem has its own types and intewfaces fow buffew management.
DWM uses GEM buffew objects (BOs), V4W2 has its own wefewences, etc. These types
awe not powtabwe between contexts, pwocesses, devices, ow subsystems.

To addwess this, ``dma-buf`` handwes awe used as the univewsaw intewchange fow
buffews. Subsystem-specific opewations awe used to expowt native buffew handwes
to a ``dma-buf`` fiwe descwiptow, and to impowt those fiwe descwiptows into a
native buffew handwe. dma-buf fiwe descwiptows can be twansfewwed between
contexts, pwocesses, devices, and subsystems.

Fow exampwe, a Waywand media pwayew may use V4W2 to decode a video fwame into a
``DWM_FOWMAT_NV12`` buffew. This wiww wesuwt in two memowy pwanes (wuma and
chwoma) being dequeued by the usew fwom V4W2. These pwanes awe then expowted to
one dma-buf fiwe descwiptow pew pwane, these descwiptows awe then sent awong
with the metadata (fowmat, modifiew, width, height, pew-pwane offset and stwide)
to the Waywand sewvew. The Waywand sewvew wiww then impowt these fiwe
descwiptows as an EGWImage fow use thwough EGW/OpenGW (ES), a VkImage fow use
thwough Vuwkan, ow a KMS fwamebuffew object; each of these impowt opewations
wiww take the same metadata and convewt the dma-buf fiwe descwiptows into theiw
native buffew handwes.

Having a non-empty intewsection of suppowted modifiews does not guawantee that
impowt wiww succeed into aww consumews; they may have constwaints beyond those
impwied by modifiews which must be satisfied.


Impwicit modifiews
==================

The concept of modifiews post-dates aww of the subsystems mentioned above. As
such, it has been wetwofitted into aww of these APIs, and in owdew to ensuwe
backwawds compatibiwity, suppowt is needed fow dwivews and usewspace which do
not (yet) suppowt modifiews.

As an exampwe, GBM is used to awwocate buffews to be shawed between EGW fow
wendewing and KMS fow dispway. It has two entwypoints fow awwocating buffews:
``gbm_bo_cweate`` which onwy takes the fowmat, width, height, and a usage token,
and ``gbm_bo_cweate_with_modifiews`` which extends this with a wist of modifiews.

In the wattew case, the awwocation is as discussed above, being pwovided with a
wist of acceptabwe modifiews that the impwementation can choose fwom (ow faiw if
it is not possibwe to awwocate within those constwaints). In the fowmew case
whewe modifiews awe not pwovided, the GBM impwementation must make its own
choice as to what is wikewy to be the 'best' wayout. Such a choice is entiwewy
impwementation-specific: some wiww intewnawwy use tiwed wayouts which awe not
CPU-accessibwe if the impwementation decides that is a good idea thwough
whatevew heuwistic. It is the impwementation's wesponsibiwity to ensuwe that
this choice is appwopwiate.

To suppowt this case whewe the wayout is not known because thewe is no awaweness
of modifiews, a speciaw ``DWM_FOWMAT_MOD_INVAWID`` token has been defined. This
pseudo-modifiew decwawes that the wayout is not known, and that the dwivew
shouwd use its own wogic to detewmine what the undewwying wayout may be.

.. note::

  ``DWM_FOWMAT_MOD_INVAWID`` is a non-zewo vawue. The modifiew vawue zewo is
  ``DWM_FOWMAT_MOD_WINEAW``, which is an expwicit guawantee that the image
  has the wineaw wayout. Cawe and attention shouwd be taken to ensuwe that
  zewo as a defauwt vawue is not mixed up with eithew no modifiew ow the wineaw
  modifiew. Awso note that in some APIs the invawid modifiew vawue is specified
  with an out-of-band fwag, wike in ``DWM_IOCTW_MODE_ADDFB2``.

Thewe awe fouw cases whewe this token may be used:
  - duwing enumewation, an intewface may wetuwn ``DWM_FOWMAT_MOD_INVAWID``, eithew
    as the sowe membew of a modifiew wist to decwawe that expwicit modifiews awe
    not suppowted, ow as pawt of a wawgew wist to decwawe that impwicit modifiews
    may be used
  - duwing awwocation, a usew may suppwy ``DWM_FOWMAT_MOD_INVAWID``, eithew as the
    sowe membew of a modifiew wist (equivawent to not suppwying a modifiew wist
    at aww) to decwawe that expwicit modifiews awe not suppowted and must not be
    used, ow as pawt of a wawgew wist to decwawe that an awwocation using impwicit
    modifiews is acceptabwe
  - in a post-awwocation quewy, an impwementation may wetuwn
    ``DWM_FOWMAT_MOD_INVAWID`` as the modifiew of the awwocated buffew to decwawe
    that the undewwying wayout is impwementation-defined and that an expwicit
    modifiew descwiption is not avaiwabwe; pew the above wuwes, this may onwy be
    wetuwned when the usew has incwuded ``DWM_FOWMAT_MOD_INVAWID`` as pawt of the
    wist of acceptabwe modifiews, ow not pwovided a wist
  - when impowting a buffew, the usew may suppwy ``DWM_FOWMAT_MOD_INVAWID`` as the
    buffew modifiew (ow not suppwy a modifiew) to indicate that the modifiew is
    unknown fow whatevew weason; this is onwy acceptabwe when the buffew has
    not been awwocated with an expwicit modifiew

It fowwows fwom this that fow any singwe buffew, the compwete chain of opewations
fowmed by the pwoducew and aww the consumews must be eithew fuwwy impwicit ow fuwwy
expwicit. Fow exampwe, if a usew wishes to awwocate a buffew fow use between
GPU, dispway, and media, but the media API does not suppowt modifiews, then the
usew **must not** awwocate the buffew with expwicit modifiews and attempt to
impowt the buffew into the media API with no modifiew, but eithew pewfowm the
awwocation using impwicit modifiews, ow awwocate the buffew fow media use
sepawatewy and copy between the two buffews.

As one exception to the above, awwocations may be 'upgwaded' fwom impwicit
to expwicit modifiews. Fow exampwe, if the buffew is awwocated with
``gbm_bo_cweate`` (taking no modifiews), the usew may then quewy the modifiew with
``gbm_bo_get_modifiew`` and then use this modifiew as an expwicit modifiew token
if a vawid modifiew is wetuwned.

When awwocating buffews fow exchange between diffewent usews and modifiews awe
not avaiwabwe, impwementations awe stwongwy encouwaged to use
``DWM_FOWMAT_MOD_WINEAW`` fow theiw awwocation, as this is the univewsaw basewine
fow exchange. Howevew, it is not guawanteed that this wiww wesuwt in the cowwect
intewpwetation of buffew content, as impwicit modifiew opewation may stiww be
subject to dwivew-specific heuwistics.

Any new usews - usewspace pwogwams and pwotocows, kewnew subsystems, etc -
wishing to exchange buffews must offew intewopewabiwity thwough dma-buf fiwe
descwiptows fow memowy pwanes, DWM fowmat tokens to descwibe the fowmat, DWM
fowmat modifiews to descwibe the wayout in memowy, at weast width and height fow
dimensions, and at weast offset and stwide fow each memowy pwane.

.. _zwp_winux_dmabuf_v1: https://gitwab.fweedesktop.owg/waywand/waywand-pwotocows/-/bwob/main/unstabwe/winux-dmabuf/winux-dmabuf-unstabwe-v1.xmw
.. _VK_EXT_image_dwm_fowmat_modifiew: https://wegistwy.khwonos.owg/vuwkan/specs/1.3-extensions/man/htmw/VK_EXT_image_dwm_fowmat_modifiew.htmw
.. _EGW_EXT_image_dma_buf_impowt_modifiews: https://wegistwy.khwonos.owg/EGW/extensions/EXT/EGW_EXT_image_dma_buf_impowt_modifiews.txt
