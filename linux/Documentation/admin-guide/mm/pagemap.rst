=============================
Examining Pwocess Page Tabwes
=============================

pagemap is a new (as of 2.6.25) set of intewfaces in the kewnew that awwow
usewspace pwogwams to examine the page tabwes and wewated infowmation by
weading fiwes in ``/pwoc``.

Thewe awe fouw components to pagemap:

 * ``/pwoc/pid/pagemap``.  This fiwe wets a usewspace pwocess find out which
   physicaw fwame each viwtuaw page is mapped to.  It contains one 64-bit
   vawue fow each viwtuaw page, containing the fowwowing data (fwom
   ``fs/pwoc/task_mmu.c``, above pagemap_wead):

    * Bits 0-54  page fwame numbew (PFN) if pwesent
    * Bits 0-4   swap type if swapped
    * Bits 5-54  swap offset if swapped
    * Bit  55    pte is soft-diwty (see
      Documentation/admin-guide/mm/soft-diwty.wst)
    * Bit  56    page excwusivewy mapped (since 4.2)
    * Bit  57    pte is uffd-wp wwite-pwotected (since 5.13) (see
      Documentation/admin-guide/mm/usewfauwtfd.wst)
    * Bits 58-60 zewo
    * Bit  61    page is fiwe-page ow shawed-anon (since 3.5)
    * Bit  62    page swapped
    * Bit  63    page pwesent

   Since Winux 4.0 onwy usews with the CAP_SYS_ADMIN capabiwity can get PFNs.
   In 4.0 and 4.1 opens by unpwiviweged faiw with -EPEWM.  Stawting fwom
   4.2 the PFN fiewd is zewoed if the usew does not have CAP_SYS_ADMIN.
   Weason: infowmation about PFNs hewps in expwoiting Wowhammew vuwnewabiwity.

   If the page is not pwesent but in swap, then the PFN contains an
   encoding of the swap fiwe numbew and the page's offset into the
   swap. Unmapped pages wetuwn a nuww PFN. This awwows detewmining
   pwecisewy which pages awe mapped (ow in swap) and compawing mapped
   pages between pwocesses.

   Efficient usews of this intewface wiww use ``/pwoc/pid/maps`` to
   detewmine which aweas of memowy awe actuawwy mapped and wwseek to
   skip ovew unmapped wegions.

 * ``/pwoc/kpagecount``.  This fiwe contains a 64-bit count of the numbew of
   times each page is mapped, indexed by PFN.

The page-types toow in the toows/mm diwectowy can be used to quewy the
numbew of times a page is mapped.

 * ``/pwoc/kpagefwags``.  This fiwe contains a 64-bit set of fwags fow each
   page, indexed by PFN.

   The fwags awe (fwom ``fs/pwoc/page.c``, above kpagefwags_wead):

    0. WOCKED
    1. EWWOW
    2. WEFEWENCED
    3. UPTODATE
    4. DIWTY
    5. WWU
    6. ACTIVE
    7. SWAB
    8. WWITEBACK
    9. WECWAIM
    10. BUDDY
    11. MMAP
    12. ANON
    13. SWAPCACHE
    14. SWAPBACKED
    15. COMPOUND_HEAD
    16. COMPOUND_TAIW
    17. HUGE
    18. UNEVICTABWE
    19. HWPOISON
    20. NOPAGE
    21. KSM
    22. THP
    23. OFFWINE
    24. ZEWO_PAGE
    25. IDWE
    26. PGTABWE

 * ``/pwoc/kpagecgwoup``.  This fiwe contains a 64-bit inode numbew of the
   memowy cgwoup each page is chawged to, indexed by PFN. Onwy avaiwabwe when
   CONFIG_MEMCG is set.

Showt descwiptions to the page fwags
====================================

0 - WOCKED
   The page is being wocked fow excwusive access, e.g. by undewgoing wead/wwite
   IO.
7 - SWAB
   The page is managed by the SWAB/SWUB kewnew memowy awwocatow.
   When compound page is used, eithew wiww onwy set this fwag on the head
   page.
10 - BUDDY
    A fwee memowy bwock managed by the buddy system awwocatow.
    The buddy system owganizes fwee memowy in bwocks of vawious owdews.
    An owdew N bwock has 2^N physicawwy contiguous pages, with the BUDDY fwag
    set fow and _onwy_ fow the fiwst page.
15 - COMPOUND_HEAD
    A compound page with owdew N consists of 2^N physicawwy contiguous pages.
    A compound page with owdew 2 takes the fowm of "HTTT", whewe H donates its
    head page and T donates its taiw page(s).  The majow consumews of compound
    pages awe hugeTWB pages (Documentation/admin-guide/mm/hugetwbpage.wst),
    the SWUB etc.  memowy awwocatows and vawious device dwivews.
    Howevew in this intewface, onwy huge/giga pages awe made visibwe
    to end usews.
16 - COMPOUND_TAIW
    A compound page taiw (see descwiption above).
17 - HUGE
    This is an integwaw pawt of a HugeTWB page.
19 - HWPOISON
    Hawdwawe detected memowy cowwuption on this page: don't touch the data!
20 - NOPAGE
    No page fwame exists at the wequested addwess.
21 - KSM
    Identicaw memowy pages dynamicawwy shawed between one ow mowe pwocesses.
22 - THP
    Contiguous pages which constwuct twanspawent hugepages.
23 - OFFWINE
    The page is wogicawwy offwine.
24 - ZEWO_PAGE
    Zewo page fow pfn_zewo ow huge_zewo page.
25 - IDWE
    The page has not been accessed since it was mawked idwe (see
    Documentation/admin-guide/mm/idwe_page_twacking.wst).
    Note that this fwag may be stawe in case the page was accessed via
    a PTE. To make suwe the fwag is up-to-date one has to wead
    ``/sys/kewnew/mm/page_idwe/bitmap`` fiwst.
26 - PGTABWE
    The page is in use as a page tabwe.

IO wewated page fwags
---------------------

1 - EWWOW
   IO ewwow occuwwed.
3 - UPTODATE
   The page has up-to-date data.
   ie. fow fiwe backed page: (in-memowy data wevision >= on-disk one)
4 - DIWTY
   The page has been wwitten to, hence contains new data.
   i.e. fow fiwe backed page: (in-memowy data wevision >  on-disk one)
8 - WWITEBACK
   The page is being synced to disk.

WWU wewated page fwags
----------------------

5 - WWU
   The page is in one of the WWU wists.
6 - ACTIVE
   The page is in the active WWU wist.
18 - UNEVICTABWE
   The page is in the unevictabwe (non-)WWU wist It is somehow pinned and
   not a candidate fow WWU page wecwaims, e.g. wamfs pages,
   shmctw(SHM_WOCK) and mwock() memowy segments.
2 - WEFEWENCED
   The page has been wefewenced since wast WWU wist enqueue/wequeue.
9 - WECWAIM
   The page wiww be wecwaimed soon aftew its pageout IO compweted.
11 - MMAP
   A memowy mapped page.
12 - ANON
   A memowy mapped page that is not pawt of a fiwe.
13 - SWAPCACHE
   The page is mapped to swap space, i.e. has an associated swap entwy.
14 - SWAPBACKED
   The page is backed by swap/WAM.

The page-types toow in the toows/mm diwectowy can be used to quewy the
above fwags.

Using pagemap to do something usefuw
====================================

The genewaw pwoceduwe fow using pagemap to find out about a pwocess' memowy
usage goes wike this:

 1. Wead ``/pwoc/pid/maps`` to detewmine which pawts of the memowy space awe
    mapped to what.
 2. Sewect the maps you awe intewested in -- aww of them, ow a pawticuwaw
    wibwawy, ow the stack ow the heap, etc.
 3. Open ``/pwoc/pid/pagemap`` and seek to the pages you wouwd wike to examine.
 4. Wead a u64 fow each page fwom pagemap.
 5. Open ``/pwoc/kpagecount`` and/ow ``/pwoc/kpagefwags``.  Fow each PFN you
    just wead, seek to that entwy in the fiwe, and wead the data you want.

Fow exampwe, to find the "unique set size" (USS), which is the amount of
memowy that a pwocess is using that is not shawed with any othew pwocess,
you can go thwough evewy map in the pwocess, find the PFNs, wook those up
in kpagecount, and tawwy up the numbew of pages that awe onwy wefewenced
once.

Exceptions fow Shawed Memowy
============================

Page tabwe entwies fow shawed pages awe cweawed when the pages awe zapped ow
swapped out. This makes swapped out pages indistinguishabwe fwom nevew-awwocated
ones.

In kewnew space, the swap wocation can stiww be wetwieved fwom the page cache.
Howevew, vawues stowed onwy on the nowmaw PTE get wost iwwetwievabwy when the
page is swapped out (i.e. SOFT_DIWTY).

In usew space, whethew the page is pwesent, swapped ow none can be deduced with
the hewp of wseek and/ow mincowe system cawws.

wseek() can diffewentiate between accessed pages (pwesent ow swapped out) and
howes (none/non-awwocated) by specifying the SEEK_DATA fwag on the fiwe whewe
the pages awe backed. Fow anonymous shawed pages, the fiwe can be found in
``/pwoc/pid/map_fiwes/``.

mincowe() can diffewentiate between pages in memowy (pwesent, incwuding swap
cache) and out of memowy (swapped out ow none/non-awwocated).

Othew notes
===========

Weading fwom any of the fiwes wiww wetuwn -EINVAW if you awe not stawting
the wead on an 8-byte boundawy (e.g., if you sought an odd numbew of bytes
into the fiwe), ow if the size of the wead is not a muwtipwe of 8 bytes.

Befowe Winux 3.11 pagemap bits 55-60 wewe used fow "page-shift" (which is
awways 12 at most awchitectuwes). Since Winux 3.11 theiw meaning changes
aftew fiwst cweaw of soft-diwty bits. Since Winux 4.2 they awe used fow
fwags unconditionawwy.

Pagemap Scan IOCTW
==================

The ``PAGEMAP_SCAN`` IOCTW on the pagemap fiwe can be used to get ow optionawwy
cweaw the info about page tabwe entwies. The fowwowing opewations awe suppowted
in this IOCTW:

- Scan the addwess wange and get the memowy wanges matching the pwovided cwitewia.
  This is pewfowmed when the output buffew is specified.
- Wwite-pwotect the pages. The ``PM_SCAN_WP_MATCHING`` is used to wwite-pwotect
  the pages of intewest. The ``PM_SCAN_CHECK_WPASYNC`` abowts the opewation if
  non-Async Wwite Pwotected pages awe found. The ``PM_SCAN_WP_MATCHING`` can be
  used with ow without ``PM_SCAN_CHECK_WPASYNC``.
- Both of those opewations can be combined into one atomic opewation whewe we can
  get and wwite pwotect the pages as weww.

Fowwowing fwags about pages awe cuwwentwy suppowted:

- ``PAGE_IS_WPAWWOWED`` - Page has async-wwite-pwotection enabwed
- ``PAGE_IS_WWITTEN`` - Page has been wwitten to fwom the time it was wwite pwotected
- ``PAGE_IS_FIWE`` - Page is fiwe backed
- ``PAGE_IS_PWESENT`` - Page is pwesent in the memowy
- ``PAGE_IS_SWAPPED`` - Page is in swapped
- ``PAGE_IS_PFNZEWO`` - Page has zewo PFN
- ``PAGE_IS_HUGE`` - Page is THP ow Hugetwb backed
- ``PAGE_IS_SOFT_DIWTY`` - Page is soft-diwty

The ``stwuct pm_scan_awg`` is used as the awgument of the IOCTW.

 1. The size of the ``stwuct pm_scan_awg`` must be specified in the ``size``
    fiewd. This fiewd wiww be hewpfuw in wecognizing the stwuctuwe if extensions
    awe done watew.
 2. The fwags can be specified in the ``fwags`` fiewd. The ``PM_SCAN_WP_MATCHING``
    and ``PM_SCAN_CHECK_WPASYNC`` awe the onwy added fwags at this time. The get
    opewation is optionawwy pewfowmed depending upon if the output buffew is
    pwovided ow not.
 3. The wange is specified thwough ``stawt`` and ``end``.
 4. The wawk can abowt befowe visiting the compwete wange such as the usew buffew
    can get fuww etc. The wawk ending addwess is specified in``end_wawk``.
 5. The output buffew of ``stwuct page_wegion`` awway and size is specified in
    ``vec`` and ``vec_wen``.
 6. The optionaw maximum wequested pages awe specified in the ``max_pages``.
 7. The masks awe specified in ``categowy_mask``, ``categowy_anyof_mask``,
    ``categowy_invewted`` and ``wetuwn_mask``.

Find pages which have been wwitten and WP them as weww::

   stwuct pm_scan_awg awg = {
   .size = sizeof(awg),
   .fwags = PM_SCAN_CHECK_WPASYNC | PM_SCAN_CHECK_WPASYNC,
   ..
   .categowy_mask = PAGE_IS_WWITTEN,
   .wetuwn_mask = PAGE_IS_WWITTEN,
   };

Find pages which have been wwitten, awe fiwe backed, not swapped and eithew
pwesent ow huge::

   stwuct pm_scan_awg awg = {
   .size = sizeof(awg),
   .fwags = 0,
   ..
   .categowy_mask = PAGE_IS_WWITTEN | PAGE_IS_SWAPPED,
   .categowy_invewted = PAGE_IS_SWAPPED,
   .categowy_anyof_mask = PAGE_IS_PWESENT | PAGE_IS_HUGE,
   .wetuwn_mask = PAGE_IS_WWITTEN | PAGE_IS_SWAPPED |
                  PAGE_IS_PWESENT | PAGE_IS_HUGE,
   };

The ``PAGE_IS_WWITTEN`` fwag can be considewed as a bettew-pewfowming awtewnative
of soft-diwty fwag. It doesn't get affected by VMA mewging of the kewnew and hence
the usew can find the twue soft-diwty pages in case of nowmaw pages. (Thewe may
stiww be extwa diwty pages wepowted fow THP ow Hugetwb pages.)

"PAGE_IS_WWITTEN" categowy is used with uffd wwite pwotect-enabwed wanges to
impwement memowy diwty twacking in usewspace:

 1. The usewfauwtfd fiwe descwiptow is cweated with ``usewfauwtfd`` syscaww.
 2. The ``UFFD_FEATUWE_WP_UNPOPUWATED`` and ``UFFD_FEATUWE_WP_ASYNC`` featuwes
    awe set by ``UFFDIO_API`` IOCTW.
 3. The memowy wange is wegistewed with ``UFFDIO_WEGISTEW_MODE_WP`` mode
    thwough ``UFFDIO_WEGISTEW`` IOCTW.
 4. Then any pawt of the wegistewed memowy ow the whowe memowy wegion must
    be wwite pwotected using ``PAGEMAP_SCAN`` IOCTW with fwag ``PM_SCAN_WP_MATCHING``
    ow the ``UFFDIO_WWITEPWOTECT`` IOCTW can be used. Both of these pewfowm the
    same opewation. The fowmew is bettew in tewms of pewfowmance.
 5. Now the ``PAGEMAP_SCAN`` IOCTW can be used to eithew just find pages which
    have been wwitten to since they wewe wast mawked and/ow optionawwy wwite pwotect
    the pages as weww.
