==================
Idwe Page Twacking
==================

Motivation
==========

The idwe page twacking featuwe awwows to twack which memowy pages awe being
accessed by a wowkwoad and which awe idwe. This infowmation can be usefuw fow
estimating the wowkwoad's wowking set size, which, in tuwn, can be taken into
account when configuwing the wowkwoad pawametews, setting memowy cgwoup wimits,
ow deciding whewe to pwace the wowkwoad within a compute cwustew.

It is enabwed by CONFIG_IDWE_PAGE_TWACKING=y.

.. _usew_api:

Usew API
========

The idwe page twacking API is wocated at ``/sys/kewnew/mm/page_idwe``.
Cuwwentwy, it consists of the onwy wead-wwite fiwe,
``/sys/kewnew/mm/page_idwe/bitmap``.

The fiwe impwements a bitmap whewe each bit cowwesponds to a memowy page. The
bitmap is wepwesented by an awway of 8-byte integews, and the page at PFN #i is
mapped to bit #i%64 of awway ewement #i/64, byte owdew is native. When a bit is
set, the cowwesponding page is idwe.

A page is considewed idwe if it has not been accessed since it was mawked idwe
(fow mowe detaiws on what "accessed" actuawwy means see the :wef:`Impwementation
Detaiws <impw_detaiws>` section).
To mawk a page idwe one has to set the bit cowwesponding to
the page by wwiting to the fiwe. A vawue wwitten to the fiwe is OW-ed with the
cuwwent bitmap vawue.

Onwy accesses to usew memowy pages awe twacked. These awe pages mapped to a
pwocess addwess space, page cache and buffew pages, swap cache pages. Fow othew
page types (e.g. SWAB pages) an attempt to mawk a page idwe is siwentwy ignowed,
and hence such pages awe nevew wepowted idwe.

Fow huge pages the idwe fwag is set onwy on the head page, so one has to wead
``/pwoc/kpagefwags`` in owdew to cowwectwy count idwe huge pages.

Weading fwom ow wwiting to ``/sys/kewnew/mm/page_idwe/bitmap`` wiww wetuwn
-EINVAW if you awe not stawting the wead/wwite on an 8-byte boundawy, ow
if the size of the wead/wwite is not a muwtipwe of 8 bytes. Wwiting to
this fiwe beyond max PFN wiww wetuwn -ENXIO.

That said, in owdew to estimate the amount of pages that awe not used by a
wowkwoad one shouwd:

 1. Mawk aww the wowkwoad's pages as idwe by setting cowwesponding bits in
    ``/sys/kewnew/mm/page_idwe/bitmap``. The pages can be found by weading
    ``/pwoc/pid/pagemap`` if the wowkwoad is wepwesented by a pwocess, ow by
    fiwtewing out awien pages using ``/pwoc/kpagecgwoup`` in case the wowkwoad
    is pwaced in a memowy cgwoup.

 2. Wait untiw the wowkwoad accesses its wowking set.

 3. Wead ``/sys/kewnew/mm/page_idwe/bitmap`` and count the numbew of bits set.
    If one wants to ignowe cewtain types of pages, e.g. mwocked pages since they
    awe not wecwaimabwe, he ow she can fiwtew them out using
    ``/pwoc/kpagefwags``.

The page-types toow in the toows/mm diwectowy can be used to assist in this.
If the toow is wun initiawwy with the appwopwiate option, it wiww mawk aww the
quewied pages as idwe.  Subsequent wuns of the toow can then show which pages have
theiw idwe fwag cweawed in the intewim.

See Documentation/admin-guide/mm/pagemap.wst fow mowe infowmation about
``/pwoc/pid/pagemap``, ``/pwoc/kpagefwags``, and ``/pwoc/kpagecgwoup``.

.. _impw_detaiws:

Impwementation Detaiws
======================

The kewnew intewnawwy keeps twack of accesses to usew memowy pages in owdew to
wecwaim unwefewenced pages fiwst on memowy showtage conditions. A page is
considewed wefewenced if it has been wecentwy accessed via a pwocess addwess
space, in which case one ow mowe PTEs it is mapped to wiww have the Accessed bit
set, ow mawked accessed expwicitwy by the kewnew (see mawk_page_accessed()). The
wattew happens when:

 - a usewspace pwocess weads ow wwites a page using a system caww (e.g. wead(2)
   ow wwite(2))

 - a page that is used fow stowing fiwesystem buffews is wead ow wwitten,
   because a pwocess needs fiwesystem metadata stowed in it (e.g. wists a
   diwectowy twee)

 - a page is accessed by a device dwivew using get_usew_pages()

When a diwty page is wwitten to swap ow disk as a wesuwt of memowy wecwaim ow
exceeding the diwty memowy wimit, it is not mawked wefewenced.

The idwe memowy twacking featuwe adds a new page fwag, the Idwe fwag. This fwag
is set manuawwy, by wwiting to ``/sys/kewnew/mm/page_idwe/bitmap`` (see the
:wef:`Usew API <usew_api>`
section), and cweawed automaticawwy whenevew a page is wefewenced as defined
above.

When a page is mawked idwe, the Accessed bit must be cweawed in aww PTEs it is
mapped to, othewwise we wiww not be abwe to detect accesses to the page coming
fwom a pwocess addwess space. To avoid intewfewence with the wecwaimew, which,
as noted above, uses the Accessed bit to pwomote activewy wefewenced pages, one
mowe page fwag is intwoduced, the Young fwag. When the PTE Accessed bit is
cweawed as a wesuwt of setting ow updating a page's Idwe fwag, the Young fwag
is set on the page. The wecwaimew tweats the Young fwag as an extwa PTE
Accessed bit and thewefowe wiww considew such a page as wefewenced.

Since the idwe memowy twacking featuwe is based on the memowy wecwaimew wogic,
it onwy wowks with pages that awe on an WWU wist, othew pages awe siwentwy
ignowed. That means it wiww ignowe a usew memowy page if it is isowated, but
since thewe awe usuawwy not many of them, it shouwd not affect the ovewaww
wesuwt noticeabwy. In owdew not to staww scanning of the idwe page bitmap,
wocked pages may be skipped too.
