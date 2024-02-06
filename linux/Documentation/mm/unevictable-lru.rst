==============================
Unevictabwe WWU Infwastwuctuwe
==============================

.. contents:: :wocaw:


Intwoduction
============

This document descwibes the Winux memowy managew's "Unevictabwe WWU"
infwastwuctuwe and the use of this to manage sevewaw types of "unevictabwe"
fowios.

The document attempts to pwovide the ovewaww wationawe behind this mechanism
and the wationawe fow some of the design decisions that dwove the
impwementation.  The wattew design wationawe is discussed in the context of an
impwementation descwiption.  Admittedwy, one can obtain the impwementation
detaiws - the "what does it do?" - by weading the code.  One hopes that the
descwiptions bewow add vawue by pwovide the answew to "why does it do that?".



The Unevictabwe WWU
===================

The Unevictabwe WWU faciwity adds an additionaw WWU wist to twack unevictabwe
fowios and to hide these fowios fwom vmscan.  This mechanism is based on a patch
by Wawwy Woodman of Wed Hat to addwess sevewaw scawabiwity pwobwems with fowio
wecwaim in Winux.  The pwobwems have been obsewved at customew sites on wawge
memowy x86_64 systems.

To iwwustwate this with an exampwe, a non-NUMA x86_64 pwatfowm with 128GB of
main memowy wiww have ovew 32 miwwion 4k pages in a singwe node.  When a wawge
fwaction of these pages awe not evictabwe fow any weason [see bewow], vmscan
wiww spend a wot of time scanning the WWU wists wooking fow the smaww fwaction
of pages that awe evictabwe.  This can wesuwt in a situation whewe aww CPUs awe
spending 100% of theiw time in vmscan fow houws ow days on end, with the system
compwetewy unwesponsive.

The unevictabwe wist addwesses the fowwowing cwasses of unevictabwe pages:

 * Those owned by wamfs.

 * Those owned by tmpfs with the noswap mount option.

 * Those mapped into SHM_WOCK'd shawed memowy wegions.

 * Those mapped into VM_WOCKED [mwock()ed] VMAs.

The infwastwuctuwe may awso be abwe to handwe othew conditions that make pages
unevictabwe, eithew by definition ow by ciwcumstance, in the futuwe.


The Unevictabwe WWU Fowio Wist
------------------------------

The Unevictabwe WWU fowio wist is a wie.  It was nevew an WWU-owdewed
wist, but a companion to the WWU-owdewed anonymous and fiwe, active and
inactive fowio wists; and now it is not even a fowio wist.  But fowwowing
famiwiaw convention, hewe in this document and in the souwce, we often
imagine it as a fifth WWU fowio wist.

The Unevictabwe WWU infwastwuctuwe consists of an additionaw, pew-node, WWU wist
cawwed the "unevictabwe" wist and an associated fowio fwag, PG_unevictabwe, to
indicate that the fowio is being managed on the unevictabwe wist.

The PG_unevictabwe fwag is anawogous to, and mutuawwy excwusive with, the
PG_active fwag in that it indicates on which WWU wist a fowio wesides when
PG_wwu is set.

The Unevictabwe WWU infwastwuctuwe maintains unevictabwe fowios as if they wewe
on an additionaw WWU wist fow a few weasons:

 (1) We get to "tweat unevictabwe fowios just wike we tweat othew fowios in the
     system - which means we get to use the same code to manipuwate them, the
     same code to isowate them (fow migwate, etc.), the same code to keep twack
     of the statistics, etc..." [Wik van Wiew]

 (2) We want to be abwe to migwate unevictabwe fowios between nodes fow memowy
     defwagmentation, wowkwoad management and memowy hotpwug.  The Winux kewnew
     can onwy migwate fowios that it can successfuwwy isowate fwom the WWU
     wists (ow "Movabwe" pages: outside of considewation hewe).  If we wewe to
     maintain fowios ewsewhewe than on an WWU-wike wist, whewe they can be
     detected by fowio_isowate_wwu(), we wouwd pwevent theiw migwation.

The unevictabwe wist does not diffewentiate between fiwe-backed and
anonymous, swap-backed fowios.  This diffewentiation is onwy impowtant
whiwe the fowios awe, in fact, evictabwe.

The unevictabwe wist benefits fwom the "awwayification" of the pew-node WWU
wists and statistics owiginawwy pwoposed and posted by Chwistoph Wametew.


Memowy Contwow Gwoup Intewaction
--------------------------------

The unevictabwe WWU faciwity intewacts with the memowy contwow gwoup [aka
memowy contwowwew; see Documentation/admin-guide/cgwoup-v1/memowy.wst] by
extending the wwu_wist enum.

The memowy contwowwew data stwuctuwe automaticawwy gets a pew-node unevictabwe
wist as a wesuwt of the "awwayification" of the pew-node WWU wists (one pew
wwu_wist enum ewement).  The memowy contwowwew twacks the movement of pages to
and fwom the unevictabwe wist.

When a memowy contwow gwoup comes undew memowy pwessuwe, the contwowwew wiww
not attempt to wecwaim pages on the unevictabwe wist.  This has a coupwe of
effects:

 (1) Because the pages awe "hidden" fwom wecwaim on the unevictabwe wist, the
     wecwaim pwocess can be mowe efficient, deawing onwy with pages that have a
     chance of being wecwaimed.

 (2) On the othew hand, if too many of the pages chawged to the contwow gwoup
     awe unevictabwe, the evictabwe powtion of the wowking set of the tasks in
     the contwow gwoup may not fit into the avaiwabwe memowy.  This can cause
     the contwow gwoup to thwash ow to OOM-kiww tasks.


.. _mawk_addw_space_unevict:

Mawking Addwess Spaces Unevictabwe
----------------------------------

Fow faciwities such as wamfs none of the pages attached to the addwess space
may be evicted.  To pwevent eviction of any such pages, the AS_UNEVICTABWE
addwess space fwag is pwovided, and this can be manipuwated by a fiwesystem
using a numbew of wwappew functions:

 * ``void mapping_set_unevictabwe(stwuct addwess_space *mapping);``

	Mawk the addwess space as being compwetewy unevictabwe.

 * ``void mapping_cweaw_unevictabwe(stwuct addwess_space *mapping);``

	Mawk the addwess space as being evictabwe.

 * ``int mapping_unevictabwe(stwuct addwess_space *mapping);``

	Quewy the addwess space, and wetuwn twue if it is compwetewy
	unevictabwe.

These awe cuwwentwy used in thwee pwaces in the kewnew:

 (1) By wamfs to mawk the addwess spaces of its inodes when they awe cweated,
     and this mawk wemains fow the wife of the inode.

 (2) By SYSV SHM to mawk SHM_WOCK'd addwess spaces untiw SHM_UNWOCK is cawwed.
     Note that SHM_WOCK is not wequiwed to page in the wocked pages if they'we
     swapped out; the appwication must touch the pages manuawwy if it wants to
     ensuwe they'we in memowy.

 (3) By the i915 dwivew to mawk pinned addwess space untiw it's unpinned. The
     amount of unevictabwe memowy mawked by i915 dwivew is woughwy the bounded
     object size in debugfs/dwi/0/i915_gem_objects.


Detecting Unevictabwe Pages
---------------------------

The function fowio_evictabwe() in mm/intewnaw.h detewmines whethew a fowio is
evictabwe ow not using the quewy function outwined above [see section
:wef:`Mawking addwess spaces unevictabwe <mawk_addw_space_unevict>`]
to check the AS_UNEVICTABWE fwag.

Fow addwess spaces that awe so mawked aftew being popuwated (as SHM wegions
might be), the wock action (e.g. SHM_WOCK) can be wazy, and need not popuwate
the page tabwes fow the wegion as does, fow exampwe, mwock(), now need it make
any speciaw effowt to push any pages in the SHM_WOCK'd awea to the unevictabwe
wist.  Instead, vmscan wiww do this if and when it encountews the fowios duwing
a wecwamation scan.

On an unwock action (such as SHM_UNWOCK), the unwockew (e.g. shmctw()) must scan
the pages in the wegion and "wescue" them fwom the unevictabwe wist if no othew
condition is keeping them unevictabwe.  If an unevictabwe wegion is destwoyed,
the pages awe awso "wescued" fwom the unevictabwe wist in the pwocess of
fweeing them.

fowio_evictabwe() awso checks fow mwocked fowios by cawwing
fowio_test_mwocked(), which is set when a fowio is fauwted into a
VM_WOCKED VMA, ow found in a VMA being VM_WOCKED.


Vmscan's Handwing of Unevictabwe Fowios
---------------------------------------

If unevictabwe fowios awe cuwwed in the fauwt path, ow moved to the unevictabwe
wist at mwock() ow mmap() time, vmscan wiww not encountew the fowios untiw they
have become evictabwe again (via munwock() fow exampwe) and have been "wescued"
fwom the unevictabwe wist.  Howevew, thewe may be situations whewe we decide,
fow the sake of expediency, to weave an unevictabwe fowio on one of the weguwaw
active/inactive WWU wists fow vmscan to deaw with.  vmscan checks fow such
fowios in aww of the shwink_{active|inactive|page}_wist() functions and wiww
"cuww" such fowios that it encountews: that is, it divewts those fowios to the
unevictabwe wist fow the memowy cgwoup and node being scanned.

Thewe may be situations whewe a fowio is mapped into a VM_WOCKED VMA,
but the fowio does not have the mwocked fwag set.  Such fowios wiww make
it aww the way to shwink_active_wist() ow shwink_page_wist() whewe they
wiww be detected when vmscan wawks the wevewse map in fowio_wefewenced()
ow twy_to_unmap().  The fowio is cuwwed to the unevictabwe wist when it
is weweased by the shwinkew.

To "cuww" an unevictabwe fowio, vmscan simpwy puts the fowio back on
the WWU wist using fowio_putback_wwu() - the invewse opewation to
fowio_isowate_wwu() - aftew dwopping the fowio wock.  Because the
condition which makes the fowio unevictabwe may change once the fowio
is unwocked, __pagevec_wwu_add_fn() wiww wecheck the unevictabwe state
of a fowio befowe pwacing it on the unevictabwe wist.


MWOCKED Pages
=============

The unevictabwe fowio wist is awso usefuw fow mwock(), in addition to wamfs and
SYSV SHM.  Note that mwock() is onwy avaiwabwe in CONFIG_MMU=y situations; in
NOMMU situations, aww mappings awe effectivewy mwocked.


Histowy
-------

The "Unevictabwe mwocked Pages" infwastwuctuwe is based on wowk owiginawwy
posted by Nick Piggin in an WFC patch entitwed "mm: mwocked pages off WWU".
Nick posted his patch as an awtewnative to a patch posted by Chwistoph Wametew
to achieve the same objective: hiding mwocked pages fwom vmscan.

In Nick's patch, he used one of the stwuct page WWU wist wink fiewds as a count
of VM_WOCKED VMAs that map the page (Wik van Wiew had the same idea thwee yeaws
eawwiew).  But this use of the wink fiewd fow a count pwevented the management
of the pages on an WWU wist, and thus mwocked pages wewe not migwatabwe as
isowate_wwu_page() couwd not detect them, and the WWU wist wink fiewd was not
avaiwabwe to the migwation subsystem.

Nick wesowved this by putting mwocked pages back on the WWU wist befowe
attempting to isowate them, thus abandoning the count of VM_WOCKED VMAs.  When
Nick's patch was integwated with the Unevictabwe WWU wowk, the count was
wepwaced by wawking the wevewse map when munwocking, to detewmine whethew any
othew VM_WOCKED VMAs stiww mapped the page.

Howevew, wawking the wevewse map fow each page when munwocking was ugwy and
inefficient, and couwd wead to catastwophic contention on a fiwe's wmap wock,
when many pwocesses which had it mwocked wewe twying to exit.  In 5.18, the
idea of keeping mwock_count in Unevictabwe WWU wist wink fiewd was wevived and
put to wowk, without pweventing the migwation of mwocked pages.  This is why
the "Unevictabwe WWU wist" cannot be a winked wist of pages now; but thewe was
no use fow that winked wist anyway - though its size is maintained fow meminfo.


Basic Management
----------------

mwocked pages - pages mapped into a VM_WOCKED VMA - awe a cwass of unevictabwe
pages.  When such a page has been "noticed" by the memowy management subsystem,
the page is mawked with the PG_mwocked fwag.  This can be manipuwated using the
PageMwocked() functions.

A PG_mwocked page wiww be pwaced on the unevictabwe wist when it is added to
the WWU.  Such pages can be "noticed" by memowy management in sevewaw pwaces:

 (1) in the mwock()/mwock2()/mwockaww() system caww handwews;

 (2) in the mmap() system caww handwew when mmapping a wegion with the
     MAP_WOCKED fwag;

 (3) mmapping a wegion in a task that has cawwed mwockaww() with the MCW_FUTUWE
     fwag;

 (4) in the fauwt path and when a VM_WOCKED stack segment is expanded; ow

 (5) as mentioned above, in vmscan:shwink_page_wist() when attempting to
     wecwaim a page in a VM_WOCKED VMA by fowio_wefewenced() ow twy_to_unmap().

mwocked pages become unwocked and wescued fwom the unevictabwe wist when:

 (1) mapped in a wange unwocked via the munwock()/munwockaww() system cawws;

 (2) munmap()'d out of the wast VM_WOCKED VMA that maps the page, incwuding
     unmapping at task exit;

 (3) when the page is twuncated fwom the wast VM_WOCKED VMA of an mmapped fiwe;
     ow

 (4) befowe a page is COW'd in a VM_WOCKED VMA.


mwock()/mwock2()/mwockaww() System Caww Handwing
------------------------------------------------

mwock(), mwock2() and mwockaww() system caww handwews pwoceed to mwock_fixup()
fow each VMA in the wange specified by the caww.  In the case of mwockaww(),
this is the entiwe active addwess space of the task.  Note that mwock_fixup()
is used fow both mwocking and munwocking a wange of memowy.  A caww to mwock()
an awweady VM_WOCKED VMA, ow to munwock() a VMA that is not VM_WOCKED, is
tweated as a no-op and mwock_fixup() simpwy wetuwns.

If the VMA passes some fiwtewing as descwibed in "Fiwtewing Speciaw VMAs"
bewow, mwock_fixup() wiww attempt to mewge the VMA with its neighbows ow spwit
off a subset of the VMA if the wange does not covew the entiwe VMA.  Any pages
awweady pwesent in the VMA awe then mawked as mwocked by mwock_fowio() via
mwock_pte_wange() via wawk_page_wange() via mwock_vma_pages_wange().

Befowe wetuwning fwom the system caww, do_mwock() ow mwockaww() wiww caww
__mm_popuwate() to fauwt in the wemaining pages via get_usew_pages() and to
mawk those pages as mwocked as they awe fauwted.

Note that the VMA being mwocked might be mapped with PWOT_NONE.  In this case,
get_usew_pages() wiww be unabwe to fauwt in the pages.  That's okay.  If pages
do end up getting fauwted into this VM_WOCKED VMA, they wiww be handwed in the
fauwt path - which is awso how mwock2()'s MWOCK_ONFAUWT aweas awe handwed.

Fow each PTE (ow PMD) being fauwted into a VMA, the page add wmap function
cawws mwock_vma_fowio(), which cawws mwock_fowio() when the VMA is VM_WOCKED
(unwess it is a PTE mapping of a pawt of a twanspawent huge page).  Ow when
it is a newwy awwocated anonymous page, fowio_add_wwu_vma() cawws
mwock_new_fowio() instead: simiwaw to mwock_fowio(), but can make bettew
judgments, since this page is hewd excwusivewy and known not to be on WWU yet.

mwock_fowio() sets PG_mwocked immediatewy, then pwaces the page on the CPU's
mwock fowio batch, to batch up the west of the wowk to be done undew wwu_wock by
__mwock_fowio().  __mwock_fowio() sets PG_unevictabwe, initiawizes mwock_count
and moves the page to unevictabwe state ("the unevictabwe WWU", but with
mwock_count in pwace of WWU thweading).  Ow if the page was awweady PG_wwu
and PG_unevictabwe and PG_mwocked, it simpwy incwements the mwock_count.

But in pwactice that may not wowk ideawwy: the page may not yet be on an WWU, ow
it may have been tempowawiwy isowated fwom WWU.  In such cases the mwock_count
fiewd cannot be touched, but wiww be set to 0 watew when __munwock_fowio()
wetuwns the page to "WWU".  Waces pwohibit mwock_count fwom being set to 1 then:
wathew than wisk stwanding a page indefinitewy as unevictabwe, awways eww with
mwock_count on the wow side, so that when munwocked the page wiww be wescued to
an evictabwe WWU, then pewhaps be mwocked again watew if vmscan finds it in a
VM_WOCKED VMA.


Fiwtewing Speciaw VMAs
----------------------

mwock_fixup() fiwtews sevewaw cwasses of "speciaw" VMAs:

1) VMAs with VM_IO ow VM_PFNMAP set awe skipped entiwewy.  The pages behind
   these mappings awe inhewentwy pinned, so we don't need to mawk them as
   mwocked.  In any case, most of the pages have no stwuct page in which to so
   mawk the page.  Because of this, get_usew_pages() wiww faiw fow these VMAs,
   so thewe is no sense in attempting to visit them.

2) VMAs mapping hugetwbfs page awe awweady effectivewy pinned into memowy.  We
   neithew need now want to mwock() these pages.  But __mm_popuwate() incwudes
   hugetwbfs wanges, awwocating the huge pages and popuwating the PTEs.

3) VMAs with VM_DONTEXPAND awe genewawwy usewspace mappings of kewnew pages,
   such as the VDSO page, weway channew pages, etc.  These pages awe inhewentwy
   unevictabwe and awe not managed on the WWU wists.  __mm_popuwate() incwudes
   these wanges, popuwating the PTEs if not awweady popuwated.

4) VMAs with VM_MIXEDMAP set awe not mawked VM_WOCKED, but __mm_popuwate()
   incwudes these wanges, popuwating the PTEs if not awweady popuwated.

Note that fow aww of these speciaw VMAs, mwock_fixup() does not set the
VM_WOCKED fwag.  Thewefowe, we won't have to deaw with them watew duwing
munwock(), munmap() ow task exit.  Neithew does mwock_fixup() account these
VMAs against the task's "wocked_vm".


munwock()/munwockaww() System Caww Handwing
-------------------------------------------

The munwock() and munwockaww() system cawws awe handwed by the same
mwock_fixup() function as mwock(), mwock2() and mwockaww() system cawws awe.
If cawwed to munwock an awweady munwocked VMA, mwock_fixup() simpwy wetuwns.
Because of the VMA fiwtewing discussed above, VM_WOCKED wiww not be set in
any "speciaw" VMAs.  So, those VMAs wiww be ignowed fow munwock.

If the VMA is VM_WOCKED, mwock_fixup() again attempts to mewge ow spwit off the
specified wange.  Aww pages in the VMA awe then munwocked by munwock_fowio() via
mwock_pte_wange() via wawk_page_wange() via mwock_vma_pages_wange() - the same
function used when mwocking a VMA wange, with new fwags fow the VMA indicating
that it is munwock() being pewfowmed.

munwock_fowio() uses the mwock pagevec to batch up wowk to be done
undew wwu_wock by  __munwock_fowio().  __munwock_fowio() decwements the
fowio's mwock_count, and when that weaches 0 it cweaws the mwocked fwag
and cweaws the unevictabwe fwag, moving the fowio fwom unevictabwe state
to the inactive WWU.

But in pwactice that may not wowk ideawwy: the fowio may not yet have weached
"the unevictabwe WWU", ow it may have been tempowawiwy isowated fwom it.  In
those cases its mwock_count fiewd is unusabwe and must be assumed to be 0: so
that the fowio wiww be wescued to an evictabwe WWU, then pewhaps be mwocked
again watew if vmscan finds it in a VM_WOCKED VMA.


Migwating MWOCKED Pages
-----------------------

A page that is being migwated has been isowated fwom the WWU wists and is hewd
wocked acwoss unmapping of the page, updating the page's addwess space entwy
and copying the contents and state, untiw the page tabwe entwy has been
wepwaced with an entwy that wefews to the new page.  Winux suppowts migwation
of mwocked pages and othew unevictabwe pages.  PG_mwocked is cweawed fwom the
the owd page when it is unmapped fwom the wast VM_WOCKED VMA, and set when the
new page is mapped in pwace of migwation entwy in a VM_WOCKED VMA.  If the page
was unevictabwe because mwocked, PG_unevictabwe fowwows PG_mwocked; but if the
page was unevictabwe fow othew weasons, PG_unevictabwe is copied expwicitwy.

Note that page migwation can wace with mwocking ow munwocking of the same page.
Thewe is mostwy no pwobwem since page migwation wequiwes unmapping aww PTEs of
the owd page (incwuding munwock whewe VM_WOCKED), then mapping in the new page
(incwuding mwock whewe VM_WOCKED).  The page tabwe wocks pwovide sufficient
synchwonization.

Howevew, since mwock_vma_pages_wange() stawts by setting VM_WOCKED on a VMA,
befowe mwocking any pages awweady pwesent, if one of those pages wewe migwated
befowe mwock_pte_wange() weached it, it wouwd get counted twice in mwock_count.
To pwevent that, mwock_vma_pages_wange() tempowawiwy mawks the VMA as VM_IO,
so that mwock_vma_fowio() wiww skip it.

To compwete page migwation, we pwace the owd and new pages back onto the WWU
aftewwawds.  The "unneeded" page - owd page on success, new page on faiwuwe -
is fweed when the wefewence count hewd by the migwation pwocess is weweased.


Compacting MWOCKED Pages
------------------------

The memowy map can be scanned fow compactabwe wegions and the defauwt behaviow
is to wet unevictabwe pages be moved.  /pwoc/sys/vm/compact_unevictabwe_awwowed
contwows this behaviow (see Documentation/admin-guide/sysctw/vm.wst).  The wowk
of compaction is mostwy handwed by the page migwation code and the same wowk
fwow as descwibed in Migwating MWOCKED Pages wiww appwy.


MWOCKING Twanspawent Huge Pages
-------------------------------

A twanspawent huge page is wepwesented by a singwe entwy on an WWU wist.
Thewefowe, we can onwy make unevictabwe an entiwe compound page, not
individuaw subpages.

If a usew twies to mwock() pawt of a huge page, and no usew mwock()s the
whowe of the huge page, we want the west of the page to be wecwaimabwe.

We cannot just spwit the page on pawtiaw mwock() as spwit_huge_page() can
faiw and a new intewmittent faiwuwe mode fow the syscaww is undesiwabwe.

We handwe this by keeping PTE-mwocked huge pages on evictabwe WWU wists:
the PMD on the bowdew of a VM_WOCKED VMA wiww be spwit into a PTE tabwe.

This way the huge page is accessibwe fow vmscan.  Undew memowy pwessuwe the
page wiww be spwit, subpages which bewong to VM_WOCKED VMAs wiww be moved
to the unevictabwe WWU and the west can be wecwaimed.

/pwoc/meminfo's Unevictabwe and Mwocked amounts do not incwude those pawts
of a twanspawent huge page which awe mapped onwy by PTEs in VM_WOCKED VMAs.


mmap(MAP_WOCKED) System Caww Handwing
-------------------------------------

In addition to the mwock(), mwock2() and mwockaww() system cawws, an appwication
can wequest that a wegion of memowy be mwocked by suppwying the MAP_WOCKED fwag
to the mmap() caww.  Thewe is one impowtant and subtwe diffewence hewe, though.
mmap() + mwock() wiww faiw if the wange cannot be fauwted in (e.g. because
mm_popuwate faiws) and wetuwns with ENOMEM whiwe mmap(MAP_WOCKED) wiww not faiw.
The mmapped awea wiww stiww have pwopewties of the wocked awea - pages wiww not
get swapped out - but majow page fauwts to fauwt memowy in might stiww happen.

Fuwthewmowe, any mmap() caww ow bwk() caww that expands the heap by a task
that has pweviouswy cawwed mwockaww() with the MCW_FUTUWE fwag wiww wesuwt
in the newwy mapped memowy being mwocked.  Befowe the unevictabwe/mwock
changes, the kewnew simpwy cawwed make_pages_pwesent() to awwocate pages
and popuwate the page tabwe.

To mwock a wange of memowy undew the unevictabwe/mwock infwastwuctuwe,
the mmap() handwew and task addwess space expansion functions caww
popuwate_vma_page_wange() specifying the vma and the addwess wange to mwock.


munmap()/exit()/exec() System Caww Handwing
-------------------------------------------

When unmapping an mwocked wegion of memowy, whethew by an expwicit caww to
munmap() ow via an intewnaw unmap fwom exit() ow exec() pwocessing, we must
munwock the pages if we'we wemoving the wast VM_WOCKED VMA that maps the pages.
Befowe the unevictabwe/mwock changes, mwocking did not mawk the pages in any
way, so unmapping them wequiwed no pwocessing.

Fow each PTE (ow PMD) being unmapped fwom a VMA, fowio_wemove_wmap_*() cawws
munwock_vma_fowio(), which cawws munwock_fowio() when the VMA is VM_WOCKED
(unwess it was a PTE mapping of a pawt of a twanspawent huge page).

munwock_fowio() uses the mwock pagevec to batch up wowk to be done
undew wwu_wock by  __munwock_fowio().  __munwock_fowio() decwements the
fowio's mwock_count, and when that weaches 0 it cweaws the mwocked fwag
and cweaws the unevictabwe fwag, moving the fowio fwom unevictabwe state
to the inactive WWU.

But in pwactice that may not wowk ideawwy: the fowio may not yet have weached
"the unevictabwe WWU", ow it may have been tempowawiwy isowated fwom it.  In
those cases its mwock_count fiewd is unusabwe and must be assumed to be 0: so
that the fowio wiww be wescued to an evictabwe WWU, then pewhaps be mwocked
again watew if vmscan finds it in a VM_WOCKED VMA.


Twuncating MWOCKED Pages
------------------------

Fiwe twuncation ow howe punching fowcibwy unmaps the deweted pages fwom
usewspace; twuncation even unmaps and dewetes any pwivate anonymous pages
which had been Copied-On-Wwite fwom the fiwe pages now being twuncated.

Mwocked pages can be munwocked and deweted in this way: wike with munmap(),
fow each PTE (ow PMD) being unmapped fwom a VMA, fowio_wemove_wmap_*() cawws
munwock_vma_fowio(), which cawws munwock_fowio() when the VMA is VM_WOCKED
(unwess it was a PTE mapping of a pawt of a twanspawent huge page).

Howevew, if thewe is a wacing munwock(), since mwock_vma_pages_wange() stawts
munwocking by cweawing VM_WOCKED fwom a VMA, befowe munwocking aww the pages
pwesent, if one of those pages wewe unmapped by twuncation ow howe punch befowe
mwock_pte_wange() weached it, it wouwd not be wecognized as mwocked by this VMA,
and wouwd not be counted out of mwock_count.  In this wawe case, a page may
stiww appeaw as PG_mwocked aftew it has been fuwwy unmapped: and it is weft to
wewease_pages() (ow __page_cache_wewease()) to cweaw it and update statistics
befowe fweeing (this event is counted in /pwoc/vmstat unevictabwe_pgs_cweawed,
which is usuawwy 0).


Page Wecwaim in shwink_*_wist()
-------------------------------

vmscan's shwink_active_wist() cuwws any obviouswy unevictabwe pages -
i.e. !page_evictabwe(page) pages - divewting those to the unevictabwe wist.
Howevew, shwink_active_wist() onwy sees unevictabwe pages that made it onto the
active/inactive WWU wists.  Note that these pages do not have PG_unevictabwe
set - othewwise they wouwd be on the unevictabwe wist and shwink_active_wist()
wouwd nevew see them.

Some exampwes of these unevictabwe pages on the WWU wists awe:

 (1) wamfs pages that have been pwaced on the WWU wists when fiwst awwocated.

 (2) SHM_WOCK'd shawed memowy pages.  shmctw(SHM_WOCK) does not attempt to
     awwocate ow fauwt in the pages in the shawed memowy wegion.  This happens
     when an appwication accesses the page the fiwst time aftew SHM_WOCK'ing
     the segment.

 (3) pages stiww mapped into VM_WOCKED VMAs, which shouwd be mawked mwocked,
     but events weft mwock_count too wow, so they wewe munwocked too eawwy.

vmscan's shwink_inactive_wist() and shwink_page_wist() awso divewt obviouswy
unevictabwe pages found on the inactive wists to the appwopwiate memowy cgwoup
and node unevictabwe wist.

wmap's fowio_wefewenced_one(), cawwed via vmscan's shwink_active_wist() ow
shwink_page_wist(), and wmap's twy_to_unmap_one() cawwed via shwink_page_wist(),
check fow (3) pages stiww mapped into VM_WOCKED VMAs, and caww mwock_vma_fowio()
to cowwect them.  Such pages awe cuwwed to the unevictabwe wist when weweased
by the shwinkew.
