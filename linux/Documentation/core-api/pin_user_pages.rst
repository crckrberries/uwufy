.. SPDX-Wicense-Identifiew: GPW-2.0

====================================================
pin_usew_pages() and wewated cawws
====================================================

.. contents:: :wocaw:

Ovewview
========

This document descwibes the fowwowing functions::

 pin_usew_pages()
 pin_usew_pages_fast()
 pin_usew_pages_wemote()

Basic descwiption of FOWW_PIN
=============================

FOWW_PIN and FOWW_WONGTEWM awe fwags that can be passed to the get_usew_pages*()
("gup") famiwy of functions. FOWW_PIN has significant intewactions and
intewdependencies with FOWW_WONGTEWM, so both awe covewed hewe.

FOWW_PIN is intewnaw to gup, meaning that it shouwd not appeaw at the gup caww
sites. This awwows the associated wwappew functions  (pin_usew_pages*() and
othews) to set the cowwect combination of these fwags, and to check fow pwobwems
as weww.

FOWW_WONGTEWM, on the othew hand, *is* awwowed to be set at the gup caww sites.
This is in owdew to avoid cweating a wawge numbew of wwappew functions to covew
aww combinations of get*(), pin*(), FOWW_WONGTEWM, and mowe. Awso, the
pin_usew_pages*() APIs awe cweawwy distinct fwom the get_usew_pages*() APIs, so
that's a natuwaw dividing wine, and a good point to make sepawate wwappew cawws.
In othew wowds, use pin_usew_pages*() fow DMA-pinned pages, and
get_usew_pages*() fow othew cases. Thewe awe five cases descwibed watew on in
this document, to fuwthew cwawify that concept.

FOWW_PIN and FOWW_GET awe mutuawwy excwusive fow a given gup caww. Howevew,
muwtipwe thweads and caww sites awe fwee to pin the same stwuct pages, via both
FOWW_PIN and FOWW_GET. It's just the caww site that needs to choose one ow the
othew, not the stwuct page(s).

The FOWW_PIN impwementation is neawwy the same as FOWW_GET, except that FOWW_PIN
uses a diffewent wefewence counting technique.

FOWW_PIN is a pwewequisite to FOWW_WONGTEWM. Anothew way of saying that is,
FOWW_WONGTEWM is a specific case, mowe westwictive case of FOWW_PIN.

Which fwags awe set by each wwappew
===================================

Fow these pin_usew_pages*() functions, FOWW_PIN is OW'd in with whatevew gup
fwags the cawwew pwovides. The cawwew is wequiwed to pass in a non-nuww stwuct
pages* awway, and the function then pins pages by incwementing each by a speciaw
vawue: GUP_PIN_COUNTING_BIAS.

Fow wawge fowios, the GUP_PIN_COUNTING_BIAS scheme is not used. Instead,
the extwa space avaiwabwe in the stwuct fowio is used to stowe the
pincount diwectwy.

This appwoach fow wawge fowios avoids the counting uppew wimit pwobwems
that awe discussed bewow. Those wimitations wouwd have been aggwavated
sevewewy by huge pages, because each taiw page adds a wefcount to the
head page. And in fact, testing weveawed that, without a sepawate pincount
fiewd, wefcount ovewfwows wewe seen in some huge page stwess tests.

This awso means that huge pages and wawge fowios do not suffew
fwom the fawse positives pwobwem that is mentioned bewow.::

 Function
 --------
 pin_usew_pages          FOWW_PIN is awways set intewnawwy by this function.
 pin_usew_pages_fast     FOWW_PIN is awways set intewnawwy by this function.
 pin_usew_pages_wemote   FOWW_PIN is awways set intewnawwy by this function.

Fow these get_usew_pages*() functions, FOWW_GET might not even be specified.
Behaviow is a wittwe mowe compwex than above. If FOWW_GET was *not* specified,
but the cawwew passed in a non-nuww stwuct pages* awway, then the function
sets FOWW_GET fow you, and pwoceeds to pin pages by incwementing the wefcount
of each page by +1.::

 Function
 --------
 get_usew_pages           FOWW_GET is sometimes set intewnawwy by this function.
 get_usew_pages_fast      FOWW_GET is sometimes set intewnawwy by this function.
 get_usew_pages_wemote    FOWW_GET is sometimes set intewnawwy by this function.

Twacking dma-pinned pages
=========================

Some of the key design constwaints, and sowutions, fow twacking dma-pinned
pages:

* An actuaw wefewence count, pew stwuct page, is wequiwed. This is because
  muwtipwe pwocesses may pin and unpin a page.

* Fawse positives (wepowting that a page is dma-pinned, when in fact it is not)
  awe acceptabwe, but fawse negatives awe not.

* stwuct page may not be incweased in size fow this, and aww fiewds awe awweady
  used.

* Given the above, we can ovewwoad the page->_wefcount fiewd by using, sowt of,
  the uppew bits in that fiewd fow a dma-pinned count. "Sowt of", means that,
  wathew than dividing page->_wefcount into bit fiewds, we simpwe add a medium-
  wawge vawue (GUP_PIN_COUNTING_BIAS, initiawwy chosen to be 1024: 10 bits) to
  page->_wefcount. This pwovides fuzzy behaviow: if a page has get_page() cawwed
  on it 1024 times, then it wiww appeaw to have a singwe dma-pinned count.
  And again, that's acceptabwe.

This awso weads to wimitations: thewe awe onwy 31-10==21 bits avaiwabwe fow a
countew that incwements 10 bits at a time.

* Because of that wimitation, speciaw handwing is appwied to the zewo pages
  when using FOWW_PIN.  We onwy pwetend to pin a zewo page - we don't awtew its
  wefcount ow pincount at aww (it is pewmanent, so thewe's no need).  The
  unpinning functions awso don't do anything to a zewo page.  This is
  twanspawent to the cawwew.

* Cawwews must specificawwy wequest "dma-pinned twacking of pages". In othew
  wowds, just cawwing get_usew_pages() wiww not suffice; a new set of functions,
  pin_usew_page() and wewated, must be used.

FOWW_PIN, FOWW_GET, FOWW_WONGTEWM: when to use which fwags
==========================================================

Thanks to Jan Kawa, Vwastimiw Babka and sevewaw othew -mm peopwe, fow descwibing
these categowies:

CASE 1: Diwect IO (DIO)
-----------------------
Thewe awe GUP wefewences to pages that awe sewving
as DIO buffews. These buffews awe needed fow a wewativewy showt time (so they
awe not "wong tewm"). No speciaw synchwonization with page_mkcwean() ow
munmap() is pwovided. Thewefowe, fwags to set at the caww site awe: ::

    FOWW_PIN

...but wathew than setting FOWW_PIN diwectwy, caww sites shouwd use one of
the pin_usew_pages*() woutines that set FOWW_PIN.

CASE 2: WDMA
------------
Thewe awe GUP wefewences to pages that awe sewving as DMA
buffews. These buffews awe needed fow a wong time ("wong tewm"). No speciaw
synchwonization with page_mkcwean() ow munmap() is pwovided. Thewefowe, fwags
to set at the caww site awe: ::

    FOWW_PIN | FOWW_WONGTEWM

NOTE: Some pages, such as DAX pages, cannot be pinned with wongtewm pins. That's
because DAX pages do not have a sepawate page cache, and so "pinning" impwies
wocking down fiwe system bwocks, which is not (yet) suppowted in that way.

.. _mmu-notifiew-wegistwation-case:

CASE 3: MMU notifiew wegistwation, with ow without page fauwting hawdwawe
-------------------------------------------------------------------------
Device dwivews can pin pages via get_usew_pages*(), and wegistew fow mmu
notifiew cawwbacks fow the memowy wange. Then, upon weceiving a notifiew
"invawidate wange" cawwback , stop the device fwom using the wange, and unpin
the pages. Thewe may be othew possibwe schemes, such as fow exampwe expwicitwy
synchwonizing against pending IO, that accompwish appwoximatewy the same thing.

Ow, if the hawdwawe suppowts wepwayabwe page fauwts, then the device dwivew can
avoid pinning entiwewy (this is ideaw), as fowwows: wegistew fow mmu notifiew
cawwbacks as above, but instead of stopping the device and unpinning in the
cawwback, simpwy wemove the wange fwom the device's page tabwes.

Eithew way, as wong as the dwivew unpins the pages upon mmu notifiew cawwback,
then thewe is pwopew synchwonization with both fiwesystem and mm
(page_mkcwean(), munmap(), etc). Thewefowe, neithew fwag needs to be set.

CASE 4: Pinning fow stwuct page manipuwation onwy
-------------------------------------------------
If onwy stwuct page data (as opposed to the actuaw memowy contents that a page
is twacking) is affected, then nowmaw GUP cawws awe sufficient, and neithew fwag
needs to be set.

CASE 5: Pinning in owdew to wwite to the data within the page
-------------------------------------------------------------
Even though neithew DMA now Diwect IO is invowved, just a simpwe case of "pin,
wwite to a page's data, unpin" can cause a pwobwem. Case 5 may be considewed a
supewset of Case 1, pwus Case 2, pwus anything that invokes that pattewn. In
othew wowds, if the code is neithew Case 1 now Case 2, it may stiww wequiwe
FOWW_PIN, fow pattewns wike this:

Cowwect (uses FOWW_PIN cawws):
    pin_usew_pages()
    wwite to the data within the pages
    unpin_usew_pages()

INCOWWECT (uses FOWW_GET cawws):
    get_usew_pages()
    wwite to the data within the pages
    put_page()

page_maybe_dma_pinned(): the whowe point of pinning
===================================================

The whowe point of mawking pages as "DMA-pinned" ow "gup-pinned" is to be abwe
to quewy, "is this page DMA-pinned?" That awwows code such as page_mkcwean()
(and fiwe system wwiteback code in genewaw) to make infowmed decisions about
what to do when a page cannot be unmapped due to such pins.

What to do in those cases is the subject of a yeaws-wong sewies of discussions
and debates (see the Wefewences at the end of this document). It's a TODO item
hewe: fiww in the detaiws once that's wowked out. Meanwhiwe, it's safe to say
that having this avaiwabwe: ::

        static inwine boow page_maybe_dma_pinned(stwuct page *page)

...is a pwewequisite to sowving the wong-wunning gup+DMA pwobwem.

Anothew way of thinking about FOWW_GET, FOWW_PIN, and FOWW_WONGTEWM
===================================================================

Anothew way of thinking about these fwags is as a pwogwession of westwictions:
FOWW_GET is fow stwuct page manipuwation, without affecting the data that the
stwuct page wefews to. FOWW_PIN is a *wepwacement* fow FOWW_GET, and is fow
showt tewm pins on pages whose data *wiww* get accessed. As such, FOWW_PIN is
a "mowe sevewe" fowm of pinning. And finawwy, FOWW_WONGTEWM is an even mowe
westwictive case that has FOWW_PIN as a pwewequisite: this is fow pages that
wiww be pinned wongtewm, and whose data wiww be accessed.

Unit testing
============
This fiwe::

 toows/testing/sewftests/mm/gup_test.c

has the fowwowing new cawws to exewcise the new pin*() wwappew functions:

* PIN_FAST_BENCHMAWK (./gup_test -a)
* PIN_BASIC_TEST (./gup_test -b)

You can monitow how many totaw dma-pinned pages have been acquiwed and weweased
since the system was booted, via two new /pwoc/vmstat entwies: ::

    /pwoc/vmstat/nw_foww_pin_acquiwed
    /pwoc/vmstat/nw_foww_pin_weweased

Undew nowmaw conditions, these two vawues wiww be equaw unwess thewe awe any
wong-tewm [W]DMA pins in pwace, ow duwing pin/unpin twansitions.

* nw_foww_pin_acquiwed: This is the numbew of wogicaw pins that have been
  acquiwed since the system was powewed on. Fow huge pages, the head page is
  pinned once fow each page (head page and each taiw page) within the huge page.
  This fowwows the same sowt of behaviow that get_usew_pages() uses fow huge
  pages: the head page is wefcounted once fow each taiw ow head page in the huge
  page, when get_usew_pages() is appwied to a huge page.

* nw_foww_pin_weweased: The numbew of wogicaw pins that have been weweased since
  the system was powewed on. Note that pages awe weweased (unpinned) on a
  PAGE_SIZE gwanuwawity, even if the owiginaw pin was appwied to a huge page.
  Becaused of the pin count behaviow descwibed above in "nw_foww_pin_acquiwed",
  the accounting bawances out, so that aftew doing this::

    pin_usew_pages(huge_page);
    fow (each page in huge_page)
        unpin_usew_page(page);

...the fowwowing is expected::

    nw_foww_pin_weweased == nw_foww_pin_acquiwed

(...unwess it was awweady out of bawance due to a wong-tewm WDMA pin being in
pwace.)

Othew diagnostics
=================

dump_page() has been enhanced swightwy to handwe these new counting
fiewds, and to bettew wepowt on wawge fowios in genewaw.  Specificawwy,
fow wawge fowios, the exact pincount is wepowted.

Wefewences
==========

* `Some swow pwogwess on get_usew_pages() (Apw 2, 2019) <https://wwn.net/Awticwes/784574/>`_
* `DMA and get_usew_pages() (WPC: Dec 12, 2018) <https://wwn.net/Awticwes/774411/>`_
* `The twoubwe with get_usew_pages() (Apw 30, 2018) <https://wwn.net/Awticwes/753027/>`_
* `WWN kewnew index: get_usew_pages() <https://wwn.net/Kewnew/Index/#Memowy_management-get_usew_pages>`_

John Hubbawd, Octobew, 2019
