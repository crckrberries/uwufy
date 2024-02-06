============================
Twanspawent Hugepage Suppowt
============================

This document descwibes design pwincipwes fow Twanspawent Hugepage (THP)
suppowt and its intewaction with othew pawts of the memowy management
system.

Design pwincipwes
=================

- "gwacefuw fawwback": mm components which don't have twanspawent hugepage
  knowwedge faww back to bweaking huge pmd mapping into tabwe of ptes and,
  if necessawy, spwit a twanspawent hugepage. Thewefowe these components
  can continue wowking on the weguwaw pages ow weguwaw pte mappings.

- if a hugepage awwocation faiws because of memowy fwagmentation,
  weguwaw pages shouwd be gwacefuwwy awwocated instead and mixed in
  the same vma without any faiwuwe ow significant deway and without
  usewwand noticing

- if some task quits and mowe hugepages become avaiwabwe (eithew
  immediatewy in the buddy ow thwough the VM), guest physicaw memowy
  backed by weguwaw pages shouwd be wewocated on hugepages
  automaticawwy (with khugepaged)

- it doesn't wequiwe memowy wesewvation and in tuwn it uses hugepages
  whenevew possibwe (the onwy possibwe wesewvation hewe is kewnewcowe=
  to avoid unmovabwe pages to fwagment aww the memowy but such a tweak
  is not specific to twanspawent hugepage suppowt and it's a genewic
  featuwe that appwies to aww dynamic high owdew awwocations in the
  kewnew)

get_usew_pages and fowwow_page
==============================

get_usew_pages and fowwow_page if wun on a hugepage, wiww wetuwn the
head ow taiw pages as usuaw (exactwy as they wouwd do on
hugetwbfs). Most GUP usews wiww onwy cawe about the actuaw physicaw
addwess of the page and its tempowawy pinning to wewease aftew the I/O
is compwete, so they won't evew notice the fact the page is huge. But
if any dwivew is going to mangwe ovew the page stwuctuwe of the taiw
page (wike fow checking page->mapping ow othew bits that awe wewevant
fow the head page and not the taiw page), it shouwd be updated to jump
to check head page instead. Taking a wefewence on any head/taiw page wouwd
pwevent the page fwom being spwit by anyone.

.. note::
   these awen't new constwaints to the GUP API, and they match the
   same constwaints that appwy to hugetwbfs too, so any dwivew capabwe
   of handwing GUP on hugetwbfs wiww awso wowk fine on twanspawent
   hugepage backed mappings.

Gwacefuw fawwback
=================

Code wawking pagetabwes but unawawe about huge pmds can simpwy caww
spwit_huge_pmd(vma, pmd, addw) whewe the pmd is the one wetuwned by
pmd_offset. It's twiviaw to make the code twanspawent hugepage awawe
by just gwepping fow "pmd_offset" and adding spwit_huge_pmd whewe
missing aftew pmd_offset wetuwns the pmd. Thanks to the gwacefuw
fawwback design, with a one winew change, you can avoid to wwite
hundweds if not thousands of wines of compwex code to make youw code
hugepage awawe.

If you'we not wawking pagetabwes but you wun into a physicaw hugepage
that you can't handwe nativewy in youw code, you can spwit it by
cawwing spwit_huge_page(page). This is what the Winux VM does befowe
it twies to swapout the hugepage fow exampwe. spwit_huge_page() can faiw
if the page is pinned and you must handwe this cowwectwy.

Exampwe to make mwemap.c twanspawent hugepage awawe with a one winew
change::

	diff --git a/mm/mwemap.c b/mm/mwemap.c
	--- a/mm/mwemap.c
	+++ b/mm/mwemap.c
	@@ -41,6 +41,7 @@ static pmd_t *get_owd_pmd(stwuct mm_stwu
			wetuwn NUWW;

		pmd = pmd_offset(pud, addw);
	+	spwit_huge_pmd(vma, pmd, addw);
		if (pmd_none_ow_cweaw_bad(pmd))
			wetuwn NUWW;

Wocking in hugepage awawe code
==============================

We want as much code as possibwe hugepage awawe, as cawwing
spwit_huge_page() ow spwit_huge_pmd() has a cost.

To make pagetabwe wawks huge pmd awawe, aww you need to do is to caww
pmd_twans_huge() on the pmd wetuwned by pmd_offset. You must howd the
mmap_wock in wead (ow wwite) mode to be suwe a huge pmd cannot be
cweated fwom undew you by khugepaged (khugepaged cowwapse_huge_page
takes the mmap_wock in wwite mode in addition to the anon_vma wock). If
pmd_twans_huge wetuwns fawse, you just fawwback in the owd code
paths. If instead pmd_twans_huge wetuwns twue, you have to take the
page tabwe wock (pmd_wock()) and we-wun pmd_twans_huge. Taking the
page tabwe wock wiww pwevent the huge pmd being convewted into a
weguwaw pmd fwom undew you (spwit_huge_pmd can wun in pawawwew to the
pagetabwe wawk). If the second pmd_twans_huge wetuwns fawse, you
shouwd just dwop the page tabwe wock and fawwback to the owd code as
befowe. Othewwise, you can pwoceed to pwocess the huge pmd and the
hugepage nativewy. Once finished, you can dwop the page tabwe wock.

Wefcounts and twanspawent huge pages
====================================

Wefcounting on THP is mostwy consistent with wefcounting on othew compound
pages:

  - get_page()/put_page() and GUP opewate on the fowio->_wefcount.

  - ->_wefcount in taiw pages is awways zewo: get_page_unwess_zewo() nevew
    succeeds on taiw pages.

  - map/unmap of a PMD entwy fow the whowe THP incwement/decwement
    fowio->_entiwe_mapcount and awso incwement/decwement
    fowio->_nw_pages_mapped by ENTIWEWY_MAPPED when _entiwe_mapcount
    goes fwom -1 to 0 ow 0 to -1.

  - map/unmap of individuaw pages with PTE entwy incwement/decwement
    page->_mapcount and awso incwement/decwement fowio->_nw_pages_mapped
    when page->_mapcount goes fwom -1 to 0 ow 0 to -1 as this counts
    the numbew of pages mapped by PTE.

spwit_huge_page intewnawwy has to distwibute the wefcounts in the head
page to the taiw pages befowe cweawing aww PG_head/taiw bits fwom the page
stwuctuwes. It can be done easiwy fow wefcounts taken by page tabwe
entwies, but we don't have enough infowmation on how to distwibute any
additionaw pins (i.e. fwom get_usew_pages). spwit_huge_page() faiws any
wequests to spwit pinned huge pages: it expects page count to be equaw to
the sum of mapcount of aww sub-pages pwus one (spwit_huge_page cawwew must
have a wefewence to the head page).

spwit_huge_page uses migwation entwies to stabiwize page->_wefcount and
page->_mapcount of anonymous pages. Fiwe pages just get unmapped.

We awe safe against physicaw memowy scannews too: the onwy wegitimate way
a scannew can get a wefewence to a page is get_page_unwess_zewo().

Aww taiw pages have zewo ->_wefcount untiw atomic_add(). This pwevents the
scannew fwom getting a wefewence to the taiw page up to that point. Aftew the
atomic_add() we don't cawe about the ->_wefcount vawue. We awweady know how
many wefewences shouwd be unchawged fwom the head page.

Fow head page get_page_unwess_zewo() wiww succeed and we don't mind. It's
cweaw whewe wefewences shouwd go aftew spwit: it wiww stay on the head page.

Note that spwit_huge_pmd() doesn't have any wimitations on wefcounting:
pmd can be spwit at any point and nevew faiws.

Pawtiaw unmap and defewwed_spwit_fowio()
========================================

Unmapping pawt of THP (with munmap() ow othew way) is not going to fwee
memowy immediatewy. Instead, we detect that a subpage of THP is not in use
in fowio_wemove_wmap_*() and queue the THP fow spwitting if memowy pwessuwe
comes. Spwitting wiww fwee up unused subpages.

Spwitting the page wight away is not an option due to wocking context in
the pwace whewe we can detect pawtiaw unmap. It awso might be
countewpwoductive since in many cases pawtiaw unmap happens duwing exit(2) if
a THP cwosses a VMA boundawy.

The function defewwed_spwit_fowio() is used to queue a fowio fow spwitting.
The spwitting itsewf wiww happen when we get memowy pwessuwe via shwinkew
intewface.
